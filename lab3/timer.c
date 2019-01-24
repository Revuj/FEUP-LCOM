#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include <math.h> //

// global variable,contador, do "timer.c"
 int counter = 0;
 static int tmr_hook_id = TIMER_HOOK_BIT_SELECT;



int(timer_set_frequency)(uint8_t timer, uint32_t freq) {

  //calculo das frequencias maxima e minima possiveis
  uint32_t freq_min = ceil((double)TIMER_FREQ/USHRT_MAX); // USHRT_MAX=0xffff
  
  if (freq > TIMER_FREQ || freq < freq_min ) {
    puts("invalid frequency\n");
    return 1;
  }

  if (timer < 0 || timer > 2) {
    return 1;
  }
  
  uint8_t timer_config;

  if ((timer_get_conf(timer, &timer_config)) != OK)
    return 1;

  uint8_t mask_half_word = BIT(3) | BIT(2) | BIT(1) | BIT(0);

  uint8_t bcd_and_programmed_mode = timer_config & mask_half_word;

  uint8_t control_word = TIMER_RB_SEL(timer) | TIMER_LSB_MSB | bcd_and_programmed_mode; // (type of access )

  if (sys_outb(TIMER_CTRL, control_word) != OK) {
    return 1;
  }
  //printf("freq=%d",freq);
  uint16_t divisor = TIMER_FREQ / freq; //calculates real frequency of the timer
  
  uint8_t timer_lsb;
  
  // see functions definitions return 1 or 0
  if (util_get_LSB(divisor, &timer_lsb) == 1) { 
    return 1;
  }
  uint8_t timer_msb;

 if (util_get_MSB(divisor, &timer_msb) == 1) {
   return 1;
 }

  if (sys_outb(TIMER_0 + timer, timer_lsb) != OK) { // importa a ordem
    return 1;
  }

  if (sys_outb(TIMER_0 + timer, timer_msb) != OK) {
    return 1;
  }

  return OK;
}

//==================================================================================================
//==================================================================================================

int(timer_subscribe_int)(uint8_t *bit_no) { 
 
  if (bit_no == NULL) {
    return 1;
  }
  else {
      // DD avisa o GIH que esta interessada numa interrupcao (DD,politica de interrupcao,*hook_id)
      *bit_no = tmr_hook_id;
     if(sys_irqsetpolicy( TIMER0_IRQ,IRQ_REENABLE,&tmr_hook_id) != OK) {
       return 1;
     }
    return OK;
  }
}

//==================================================================================================
//==================================================================================================

int(timer_unsubscribe_int)() { 
  // the bit is going to be zero
  if(sys_irqrmpolicy(&tmr_hook_id) != OK) {
      return 1;
  }
  return OK;
}

//==================================================================================================
//==================================================================================================

void(timer_int_handler)() {
  counter++;
}


//==================================================================================================
//==================================================================================================

int(timer_get_conf)(uint8_t timer, uint8_t *st) {

  if (timer < 0 || timer > 2 || st == NULL) {
    return 1;
  
  }
  else {
    uint8_t read_back_cmd;

    read_back_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

    if (sys_outb(TIMER_CTRL, read_back_cmd) != OK) { 
      return 1;
    }

    uint8_t timer_port = TIMER_0 + timer;
    u32_t status;

    if (sys_inb(timer_port, &status) != OK) {
      return 1;
    }
    else {
      *st = (uint8_t) status;
    }
  }

  return OK;
}

//===============================================================================================
//===============================================================================================

int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  if (timer < 0 || timer > 2) {
    return 1;
  }


  union timer_status_field_val status_field;

  switch (field) {
    case all:

      status_field.byte = st;
      break;

    case initial:;

      uint8_t mask_init_mode = BIT(4) | BIT(5);
      uint8_t init_mode = mask_init_mode & st;
      init_mode = init_mode >> 4;

      enum timer_init t_init;

      switch (init_mode) {
        case 0:
          return 1;

        case 1:
          t_init = LSB_only;
          break;

        case 2:
          t_init = MSB_only;
          break;

        case 3:
          t_init = MSB_after_LSB;
          break;

        default:
          return 1;
      }
      status_field.in_mode = t_init;
      break;
  
    case mode:;

      uint8_t mask_count_mode = BIT(1) | BIT(2) | BIT(3);
      uint8_t count_mode = mask_count_mode & st;
      count_mode = count_mode >> 1;
      status_field.count_mode = count_mode;
      break;

    case base:;

      uint8_t mask_base = BIT(0);
      uint8_t base_mode = mask_base & st;
      status_field.bcd = base_mode;
      break;

    default:

      return 1;
  }

  timer_print_config(timer, field, status_field);
 
  return OK;
}
