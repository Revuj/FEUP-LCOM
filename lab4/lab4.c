#include "keyboard.h"
#include "mouse.h"
#include "mouse_state_machine.h"
#include "timer.h"
#include <i8042.h>
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

extern int counter;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt) {
  uint8_t bit_no;
  int ipc_status, r;
  message msg;
  struct packet pp;
  uint32_t data;
  int8_t packet_byte;
  uint8_t byte_counter = 0;

  if (mouse_write_command(MOUSE_ENABLE_STREAM_MODE_COMMAND) != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_ENABLE_DATA_REPORTING_COMMAND) != OK) {
    return NOT_OK;
  }


  if (mouse_subscribe_int(&bit_no) != OK) {
    return NOT_OK;
  }

  while (cnt > 0) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {                   /* received notification e retorna true caso o seja*/
      switch (_ENDPOINT_P(msg.m_source)) {             // verifica o tipo de notificacao
        case HARDWARE:                                 /* hardware interrupt notification */
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            mouse_ih();
            if (mouse_get_error() != 1) {
              data = mouse_get_data();
              packet_byte = (uint8_t) data;
              if (get_packet(packet_byte, &pp, &byte_counter) == true) {
                mouse_print_packet(&pp);
                cnt--;
              }
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_unsubscribe_int() != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_DISABLE_DATA_REPORTING_COMMAND) != OK) { 
    return NOT_OK;
  }

  return OK;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt) {

  struct packet pp;
  uint32_t data;
  uint8_t packet_byte;
  uint8_t byte_counter = 0;

  while (cnt > 0) {
    if (byte_counter == 0) { //são recebidos 4 bytes e o primeiro deles é o acknowledgment
      do {
        if (kbc_write_command_with_argument(KBC_WRITE_TO_MOUSE, MOUSE_READ_DATA_COMMAND) == OK) {
          mouse_read_obf();
        }
      } while (mouse_get_data() != MOUSE_ACK);
    }

    if (mouse_read_obf() == true) {
      if (mouse_get_error() != 1) {

        data = mouse_get_data();

        packet_byte = (uint8_t) data;

        if (get_packet(packet_byte, &pp, &byte_counter) == true) {
          mouse_print_packet(&pp);
          cnt--;
          tickdelay(micros_to_ticks(period * 1000));
        }
      }
    }
  }

  if (kbc_write_command_with_argument(KBC_WRITE_COMMAND, minix_get_dflt_kbc_cmd_byte()) != OK) {
    return NOT_OK;
  }

  if (kbc_write_command_with_argument(KBC_WRITE_TO_MOUSE, MOUSE_ENABLE_STREAM_MODE_COMMAND) != OK) {
    return NOT_OK;
  }
  mouse_read_obf(); //clear output buffer;

  if (kbc_write_command_with_argument(KBC_WRITE_TO_MOUSE, MOUSE_DISABLE_DATA_REPORTING_COMMAND) != OK) {
    return NOT_OK; 
  }
  mouse_read_obf(); //clear output buffer;

  return OK;
}

int(mouse_test_async)(uint8_t idle_time) {
  uint8_t mouse_bit_no;
  uint8_t timer_bit_no;

  int ipc_status, r;
  message msg;
  struct packet pp;
  uint32_t data;
  int8_t packet_byte;
  uint8_t byte_counter = 0;

  if (mouse_write_command(MOUSE_ENABLE_STREAM_MODE_COMMAND) != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_ENABLE_DATA_REPORTING_COMMAND) != OK) {
    return NOT_OK;
  }

  if (mouse_subscribe_int(&mouse_bit_no) != OK) {
    return NOT_OK;
  }

  if (timer_subscribe_int(&timer_bit_no) != OK) {
    return NOT_OK;
  }

  while (counter < idle_time * 60) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {       /* received notification e retorna true caso o seja*/
      switch (_ENDPOINT_P(msg.m_source)) { // verifica o tipo de notificacao
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_bit_no)) { /* subscribed interrupt */
            timer_int_handler();
          }

          if (msg.m_notify.interrupts & BIT(mouse_bit_no)) { /* subscribed interrupt */
            mouse_ih();
            counter = 0;

            if (mouse_get_error() != 1) {
              data = mouse_get_data();

              packet_byte = (uint8_t) data;
              if (get_packet(packet_byte, &pp, &byte_counter) == true) {
                mouse_print_packet(&pp);
              }
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_unsubscribe_int() != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_DISABLE_DATA_REPORTING_COMMAND) != OK) { //disable data reporting
    return NOT_OK;
  }

  if (timer_unsubscribe_int() != OK) {
    return NOT_OK;
  }

  return OK;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  uint8_t bit_no;
  int ipc_status, r;
  message msg;
  struct packet pp;
  uint32_t data;
  int8_t packet_byte;
  uint8_t byte_counter = 0;
  struct mouse_ev mouse_event;

  if (mouse_write_command(MOUSE_ENABLE_STREAM_MODE_COMMAND) != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_ENABLE_DATA_REPORTING_COMMAND) != OK) {
    return NOT_OK;
  }

  if (mouse_subscribe_int(&bit_no) != OK) {
    return NOT_OK;
  }

  while (get_mouse_state() != FINAL) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {                   /* received notification e retorna true caso o seja*/
      switch (_ENDPOINT_P(msg.m_source)) {             // verifica o tipo de notificacao
        case HARDWARE:                                 /* hardware interrupt notification */
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            mouse_ih();

            if (mouse_get_error() != 1) {

              data = mouse_get_data();

              packet_byte = (uint8_t) data;

              if (get_packet(packet_byte, &pp, &byte_counter) == true) {
                mouse_event = *mouse_check_event(&pp);
                mouse_event_handler(&pp, x_len, tolerance);
                mouse_print_packet(&pp);
              }
            }
          }

          break;

        default:
          break;
      }
    }
  }

  if (mouse_unsubscribe_int() != OK) {
    return NOT_OK;
  }

  if (mouse_write_command(MOUSE_DISABLE_DATA_REPORTING_COMMAND) != OK) {
    return NOT_OK;
  }

  return OK;
}
