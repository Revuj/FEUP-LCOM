#include "mouse.h"
#include "keyboard.h"
#include "i8042.h"
#include "bitmap.h"
#include "Game.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <math.h>
static int mouse_hook_id = MOUSE_HOOK_BIT_SELECT;
static uint32_t data;
static int mouse_error_flag;
static uint8_t byte_counter = 0;
static struct packet pp;
int mouse_subscribe_int(uint8_t *bit_no)
{
  if (bit_no == NULL)
  {
    return 1;
  }
  else
  {
    // DD avisa o GIH que esta interessada numa interrupcao (DD,politica de interrupcao,*hook_id)
    *bit_no = mouse_hook_id;
    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK)
    {
      return 1;
    }
    return OK;
  }
}
//================================================================================================
//================================================================================================
/* unsubscribes mouse interruptions */
int mouse_unsubscribe_int()
{
  if (sys_irqrmpolicy(&mouse_hook_id) != OK)
  {
    return 1;
  }
  return OK;
}
//==================================================================================================
//==================================================================================================
/*checks if the data in the status is valid */
bool mouse_is_valid_data(uint32_t stat)
{
  if ((stat & (PAR_ERR | TO_ERR)) != OK)
  {
    return false;
  }
  return true;
}
//==================================================================================================
//==================================================================================================
/*mouse interrupt handler */
void(mouse_ih)(void)
{
  mouse_read_obf();
  return;
}
//==================================================================================================
//==================================================================================================
/* read packet bytes*/
bool get_packet(uint8_t packet_byte)
{
  if (byte_counter == 0)
  {
    if ((packet_byte & BIT(3)) == 0)
    {
      return false;
    }
    byte_counter = 1;
    pp.bytes[0] = packet_byte;
    pp.mb = (packet_byte & MB_BIT);
    pp.rb = (packet_byte & RB_BIT);
    pp.lb = (packet_byte & LB_BIT);
    pp.x_ov = (packet_byte & X_OVF);
    pp.y_ov = (packet_byte & Y_OVF);
    return false;
  }
  else if (byte_counter == 1)
  {
    byte_counter = 2;
    pp.bytes[1] = packet_byte;
    if (pp.bytes[0] & BIT(4))
    {
      pp.delta_x = packet_byte - 256;
    }
    else
    {
      pp.delta_x = packet_byte;
    }
    return false;
  }
  else
  {
    byte_counter = 0;
    pp.bytes[2] = packet_byte;
    if (pp.bytes[0] & BIT(5))
    {
      pp.delta_y = packet_byte - 256;
    }
    else
    {
      pp.delta_y = packet_byte;
    }
    return true;
  }
}
//==================================================================================================
//==================================================================================================
bool mouse_read_obf()
{
  uint32_t stat;
  uint8_t retries = 10;
  while (retries > 0)
  { //loop to write argument
    if (sys_inb(KBC_STAT_REG, &stat) == OK)
    { //gets status byte
      if ((stat & OBF) == 1)
      { //Output buffer is full
        if (sys_inb(KBC_OUT_BUF, &data) == OK)
        //printf("%04X\n", data);
        { //read command
          if (mouse_is_valid_data(stat) == true)
          {
            mouse_error_flag = 0;
            return true;
          }
        }
      }
    }
    mouse_error_flag = 1;
    retries--;
  }
  mouse_error_flag = 1;
  return false;
}
//==================================================================================================
//==================================================================================================
int mouse_write_command(uint16_t command)
{
  mouse_disable_interrupts();
  do
  {
    if (kbc_write_command_with_argument(KBC_WRITE_TO_MOUSE, command) == OK)
    {
      mouse_read_obf();
    }
  } while (mouse_get_data() != MOUSE_ACK);
  mouse_enable_interrupts();
  return OK;
}
//================================================================================================
//================================================================================================
/*returns the global variable data defined in the keyboard's scope*/
uint32_t mouse_get_data()
{
  return data;
}
//================================================================================================
//================================================================================================
/*returns the global variable mouse_error_flag defined in the keyboard's scope*/
int mouse_get_error()
{
  return mouse_error_flag;
}
//================================================================================================
//================================================================================================
int mouse_disable_interrupts()
{
  uint32_t command_byte;
  command_byte = minix_get_dflt_kbc_cmd_byte();
  command_byte = (command_byte & 0xFD); //changes command byte so that the interrupts on OBF are disabled
  if (kbc_write_command_with_argument(KBC_WRITE_COMMAND, command_byte) != OK)
  {
    return NOT_OK;
  }
  return OK;
}
//================================================================================================
//================================================================================================
int mouse_enable_interrupts()
{
  uint32_t command_byte;
  command_byte = minix_get_dflt_kbc_cmd_byte();
  command_byte = (command_byte | INT2); //changes command byte so that the interrupts on OBF are enabled
  if (kbc_write_command_with_argument(KBC_WRITE_COMMAND, command_byte) != OK)
  {
    return NOT_OK;
  }
  return OK;
}
//================================================================================================
//================================================================================================
void game_mouse_ih()
{
  mouse_ih();
  if (mouse_get_error())
  {
    return;
  }
  change_mouse();
}

void change_mouse() {
  Bitmap *mouse = get_game()->mouse;
  Bitmap *astronaut_zero = get_game()->astronaut[0];
 
  uint32_t data = mouse_get_data();
  uint8_t packet_byte = (uint8_t)data;
  bullet * current = get_gun()->bullet;
 
  if (get_packet(packet_byte) == true)
  {
    struct packet pp = get_mouse();
    if (pp.lb && get_game()->state == PLAYING && shoot_bullet()) {
        while (current->next != NULL) {
          current = current->next;
        }
     
      Bitmap * bullet =new_bullet(current, astronaut_zero->x +180, astronaut_zero->y+20);
      map_colision(bullet, bullet->x, bullet->y, 100);
      float delta_x = mouse->x + 45 - bullet->x - 16;
      float delta_y = mouse->y + 45 - bullet->y - 16;
      float angle = atan2(delta_y, delta_x);
      bullet->speed_x = 15 * cos(angle);
      bullet->speed_y = 15 * sin(angle);
    }
 
    if (!pp.x_ov)
    {
      if (mouse->x + pp.delta_x <= 0)
      {
        mouse->x = 0;
      }
      else if (mouse->x + pp.delta_x + mouse->bitmapInfoHeader.width >= get_hres())
      {
        mouse->x = get_hres() - mouse->bitmapInfoHeader.width;
      }
      else
      {
        mouse->x += pp.delta_x;
      }
    }
    if (!pp.y_ov)
    {
      if (mouse->y - pp.delta_y <= 0)
      {
        mouse->y = 0;
      }
      else if (mouse->y - pp.delta_y + mouse->bitmapInfoHeader.height >= get_vres())
      {
        mouse->y = get_vres() - mouse->bitmapInfoHeader.height;
      }
      else
      {
        mouse->y -= pp.delta_y;
      }
    }
  }
}

//================================================================================================
//================================================================================================
struct packet get_mouse() {
  return pp;
}
//================================================================================================
//================================================================================================
void reset_mouse(const char * path) {
  get_game()->mouse = load_bitmap_file(path);
  get_game()->mouse->x = 512;
  get_game()->mouse->y = 384;
  pp.delta_x = 0;
  pp.delta_y = 0;
  pp.lb = 0;
  pp.rb = 0;
  pp.mb = 0;
  pp.x_ov = 0;
  pp.y_ov = 0;
}
