#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"
#include <lcom/lab3.h>

static uint32_t data;
extern int count;
extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

//==================================================================================================
//==================================================================================================


int(kbd_test_scan)(bool assembly) {


  int ipc_status, r;
  message msg;
  uint8_t bit_no;
  uint8_t scancode_byte;
  uint8_t size;
  uint8_t two_byte_scancode = 0;
  uint8_t bytes[2];

  if (kbc_subscribe_int(&bit_no) != OK) {
    return 1;
  }

  while (data != KBC_ESC) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {                   /* received notification e retorna true caso o seja*/
      switch (_ENDPOINT_P(msg.m_source)) {             // verifica o tipo de notificacao
        case HARDWARE:                                 /* hardware interrupt notification */
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            if (assembly == false) {
              kbc_ih();
            }
            else {
              kbc_asm_ih();
            }

              if (get_error() == 1) {
                continue;
              }
              else {
                data = get_data();
              }


            scancode_byte = (uint8_t) data;

            if (!get_scancode(&two_byte_scancode, scancode_byte, bytes)) { //scan code tem 2 bytes
              continue;
            }
            else {
              size = scancode_size(bytes[0]);
              kbd_print_scancode(is_make(bytes, size), size, bytes);
            }
          }
      }
    }
  }

  if (kbc_unsubscribe_int() != OK) {
    return 1;
  }

  if ( assembly == false) {
    kbd_print_no_sysinb(count);
  }

  return OK;
}

//==================================================================================================
//==================================================================================================

int(kbd_test_poll)() {

  uint8_t scancode_byte;
  uint8_t size;
  uint8_t two_byte_scancode = 0;
  uint8_t bytes[2];
  
  while (data != KBC_ESC) {

    while (1) {
    if (read_obf() == true) {
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US));
    }

    if (get_error() == 1) {
      tickdelay(micros_to_ticks(DELAY_US));
      continue;
    }
    else {
      data = get_data();
    }

    scancode_byte = (uint8_t) data;

    if (!get_scancode(&two_byte_scancode, scancode_byte, bytes)) { //scan code tem 2 bytes
      continue;
    }
    else {
      size = scancode_size(bytes[0]);
      kbd_print_scancode(is_make(bytes, size), size, bytes);
    }
  }

  if (kbc_enable_interrupts() != OK) {
    return NOT_OK;
  }
  else {
    return OK;
  }
}
//==================================================================================================
//==================================================================================================

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status, r;
  message msg;
  uint8_t bit_no;
  uint8_t scancode_byte;
  uint8_t size;
  uint8_t two_byte_scancode = 0;
  uint8_t bytes[2];
  uint8_t bit_no_timer;

  if (timer_subscribe_int(&bit_no_timer) != OK) {
    return 1;
  }

  if (kbc_subscribe_int(&bit_no) != OK) {
    return 1;
  }

  while ((data != KBC_ESC) && (counter < n * 60)) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {       /* received notification e retorna true caso o seja*/
      switch (_ENDPOINT_P(msg.m_source)) { // verifica o tipo de notificacao
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(bit_no_timer)) { /* subscribed interrupt */
            timer_int_handler();
          }

          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            kbc_ih();

            if (get_error() == 1) {
              continue;
            }
            else {
              data = get_data();
            }

            counter = 0; // restart counter

            scancode_byte = (uint8_t) data;

            if (!get_scancode(&two_byte_scancode, scancode_byte, bytes)) { //scan code tem 2 bytes
              continue;
            }
            else {
              size = scancode_size(bytes[0]);
              kbd_print_scancode(is_make(bytes, size), size, bytes);
            }
          }
      }
    }
  }

  if (timer_unsubscribe_int() != OK) {
    return 1;
  }

  if (kbc_unsubscribe_int() != OK) {
    return 1;
  }

  kbd_print_no_sysinb(count);

  return OK;
}

//==================================================================================================
//================================================================================================== 
