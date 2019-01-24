
#include <lcom/lcf.h>
#include "keyboard.h"
#include <minix/sysutil.h>
#include "bitmap.h"
#include "video_gr.h"
#include "Game.h"
/* global variables */
static int kbc_hook_id = KBC_HOOK_BIT_SELECT;
uint32_t data;
int error_flag;


//================================================================================================
//================================================================================================
/* subsode_info_t structure to be initializedode_info_t structure to be initializedcribes keyboard interruptions */
int kbc_subscribe_int(uint8_t *bit_no)
{
  if (bit_no == NULL)
  {
    return 1;
  }
  else
  {
    // DD avisa o GIH que esta interessada numa interrupcao (DD,politica de interrupcao,*hook_id)
    kbc_hook_id = KBC_HOOK_BIT_SELECT;
    *bit_no = kbc_hook_id;
    if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_hook_id) != OK)
    {
      return 1;
    }
    return OK;
  }
}
//================================================================================================
//================================================================================================
/* unsubscribes keyboard interruptions */
int kbc_unsubscribe_int()
{
  if (sys_irqrmpolicy(&kbc_hook_id) != OK)
  {
    return 1;
  }
  return OK;
}
//================================================================================================
//================================================================================================
/*checks if the data in the status is valid */
bool kbc_is_valid_data(uint32_t stat)
{
  if ((stat & OBF) == 1)
  {
    if ((stat & PAR_ERR & TO_ERR) != OK)
    {
      return false;
    }
  }
  else
  {
    return false;
  }
  return true;
}
void(kbc_ih)(void)
{
  uint32_t stat;
  if (sys_inb(KBC_STAT_REG, &stat) != OK)
  { //read status register and stores it on stat
    error_flag = 1;
    return;
  }
  if (sys_inb(KBC_OUT_BUF, &data) != OK)
  { // reads OBF and stores it on data
    error_flag = 1;
    return;
  }
  if (kbc_is_valid_data(stat) == false)
  {
    error_flag = 1;
    return;
  }
  error_flag = 0;
  return;
}
//==================================================================================================
//==================================================================================================
/* returns the scancode size*/
uint scancode_size(uint8_t byte)
{
  if (byte == (COMMON_BYTE) || byte == (COMMON_BYTE2))
  { // checks if the byte is 0xE0 ou 0xE1
    return 2;
  }
  else
  {
    return 1;
  }
}
//==================================================================================================
//==================================================================================================
/* checks if the scancode is a makecode or a breakcode */
bool is_make(const uint8_t scancode[], const uint8_t size)
{
  if (size == 1)
  {
    if ((scancode[0] & MAKE_BIT) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if ((scancode[1] & MAKE_BIT) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
//==================================================================================================
//==================================================================================================
/* read scancode bytes*/
bool get_scancode(uint8_t *two_byte_scancode, uint8_t scancode_byte, uint8_t scancode[])
{
  if ((*two_byte_scancode) == 1)
  {
    scancode[1] = scancode_byte;
    (*two_byte_scancode) = 0;
    return true;
  }
  else if (scancode_size(scancode_byte) == 2 && (*two_byte_scancode) == 0)
  {
    (*two_byte_scancode) = 1;
    scancode[0] = scancode_byte;
    return false;
  }
  else
  {
    scancode[0] = scancode_byte;
    scancode[1] = 0;
    return true;
  }
}
//================================================================================================
//================================================================================================
/*reads output buffer*/
bool kbd_read_obf()
{
  uint32_t stat;
  if (sys_inb(KBC_STAT_REG, &stat) != OK)
  { //read status register and puts it on stat
    error_flag = 1;
    return false;
  }
  if (kbc_is_valid_data(stat))
  {
    if (sys_inb(KBC_OUT_BUF, &data) != OK)
    {
      error_flag = 1;
      return false;
    }
  }
  else
  {
    error_flag = 1;
    return false;
  }
  error_flag = 0;
  return true;
}
//================================================================================================
//================================================================================================
int kbc_write_command(uint16_t command)
{
  uint32_t stat;
  uint8_t retries = 10;
  while (retries > 0)
  { //loop to write argument
    if (sys_inb(KBC_STAT_REG, &stat) == OK)
    { //gets status byte
      if ((stat & IBF) == 0)
      { //Input buffer is not full
        if (sys_outb(KBC_CMD_REGISTER, command) == OK)
        { //write command
          return OK;
        }
        else
        {
          return NOT_OK;
        }
      }
    }
    else
    {
      return NOT_OK;
    }
    tickdelay(micros_to_ticks(DELAY_US));
    retries--;
  }
  return NOT_OK;
}
//================================================================================================
//================================================================================================
int kbc_write_command_with_argument(uint16_t command, uint16_t argument)
{
  uint32_t stat;
  uint8_t retries = 10;
  kbc_write_command(command);
  while (retries > 0)
  { //loop to write argument
    if (sys_inb(KBC_STAT_REG, &stat) == OK)
    { //gets status byte
      if ((stat & IBF) == 0)
      { //Input buffer is not full
        if (sys_outb(KBC_OUT_BUF, argument) == OK)
        { //write argument
          return OK;
        }
      }
    }
    tickdelay(micros_to_ticks(DELAY_US));
    retries--;
  }
  return NOT_OK;
}
//================================================================================================
//================================================================================================
uint32_t kbc_get_data()
{
  return data;
}

//================================================================================================
//================================================================================================
/*returns the global variable error_flag defined in the keyboard's scope*/
int kbc_get_error()
{
  return error_flag;
}
void keyboard_event_handler(uint8_t scancode_byte)
{
  
  Bitmap *astronaut = get_game()->astronaut[0];

  if (scancode_byte == W_MAKECODE) {
    astronaut->speed_y = -SPEED;
  }
  if (scancode_byte == W_BREAKCODE) {
    astronaut->speed_y = 0;
  }
  if (scancode_byte == A_MAKECODE) {
    astronaut->speed_x = -SPEED;
  }
  if (scancode_byte == A_BREAKCODE) {
    astronaut->speed_x = 0;
  }
  if (scancode_byte == S_MAKECODE) {
    astronaut->speed_y = SPEED;
  }
  if (scancode_byte == S_BREAKCODE) {
    astronaut->speed_y = 0;
  }
  if (scancode_byte == D_MAKECODE) {
    astronaut->speed_x = SPEED;
  }
  if (scancode_byte == D_BREAKCODE) {
    astronaut->speed_x = 0;
  }
  if (scancode_byte == R_MAKECODE) {
    set_reloading();
  }
}


void reset_keyboard() {
    Bitmap *astronaut = get_game()->astronaut[0];
    astronaut->speed_x= (astronaut->y =0);
    data = 0xff;
}

int game_kbc_ih()
{ 
  kbc_asm_ih();
  static uint8_t scancode_byte;
  static uint8_t size;
  static uint8_t two_byte_scancode = 0;
  static uint8_t bytes[2];
  if (kbc_get_error())
  {
    return 1;
  }
  else
  {
    data = kbc_get_data();
  }
  scancode_byte = (uint8_t)data;
  keyboard_event_handler(scancode_byte);

  if (!get_scancode(&two_byte_scancode, scancode_byte, bytes))
  {
    return 1;
  }
  else
  {
    size = scancode_size(bytes[0]);
  }
  return 0;
}
