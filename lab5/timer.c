#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>
#include "i8254.h"

// global variable,contador, do "timer.c"
 int counter = 0;
 static int hook_id = TIMER_HOOK_BIT_SELECT;

//==================================================================================================
//==================================================================================================

int(timer_subscribe_int)(uint8_t *bit_no) { 
 
  if (bit_no == NULL) {
    return 1;
  }
  else {
      // DD avisa o GIH que esta interessada numa interrupcao (DD,politica de interrupcao,*hook_id)
      *bit_no = hook_id;
     if(sys_irqsetpolicy( TIMER0_IRQ,IRQ_REENABLE,&hook_id) != OK) {
       return 1;
     }
    return OK;
  }
}

//==================================================================================================
//==================================================================================================

int(timer_unsubscribe_int)() { 


  // the bit is going to be zero
  if(sys_irqrmpolicy(&hook_id) != OK) {
      return 1;
  }
  return OK;

}

//==================================================================================================
//==================================================================================================

void(timer_int_handler)() {
  counter++;
}




