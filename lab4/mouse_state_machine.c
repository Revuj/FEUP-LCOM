#include <lcom/lcf.h>
#include "mouse_state_machine.h"
#include <minix/sysutil.h>

struct mouse_ev mouse_event;

enum state_t mouse_state;

enum state_t get_mouse_state() {
  return mouse_state;
}

struct mouse_ev * mouse_check_event(struct packet *pp) {
  
  mouse_event.delta_x = pp->delta_x;
  mouse_event.delta_y = pp->delta_y;

  if (mouse_event.delta_x != 0 || mouse_event.delta_y != 0) {
    mouse_event.type =  MOUSE_MOV;
  }

  else if (pp->lb && mouse_state == DRAW1) {
  }

  else if (pp->lb) {
    mouse_event.type = LB_PRESSED;
  }

  else if (!pp->lb && mouse_state == DRAW1) {
    mouse_event.type = LB_RELEASED;
  }

  else if (pp->rb && mouse_state == DRAW2) {
  }

  else if (pp->rb) {
    mouse_event.type = RB_PRESSED;
  }

  else if (!pp->rb && mouse_state == DRAW2) {
    mouse_event.type = RB_RELEASED;
  }

  else if (pp->mb) {
    mouse_event.type = BUTTON_EV;
  }

  else if (!pp->mb) {
    mouse_event.type = BUTTON_EV;
  }
  return &mouse_event;
}

void mouse_event_handler(struct packet *pp, uint8_t x_len, uint8_t tolerance) {
  static int length_x = 0;
  static int length_y = 0;

  if (tolerance == 0) {
    return;
  }
  switch(mouse_state) {
    case INIT1:;
      if (mouse_event.type == LB_PRESSED) {
        mouse_state = DRAW1;
      }
      break;
    
    case DRAW1:;
      if (mouse_event.type == MOUSE_MOV) {
        if (pp->delta_x < 0 && (abs(pp->delta_x) > tolerance)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        if (pp->delta_y < 0 && (abs(pp->delta_y) > tolerance)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }

        if (((double)pp->delta_y <= (double)pp->delta_x)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        if (pp->x_ov || pp->y_ov) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }

        length_x += pp->delta_x;
        length_y += pp->delta_y;

        break;
      }
      else if (mouse_event.type == LB_RELEASED) {
        if (length_x >= x_len) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT2;
          break;
        }
        else {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
        }
        break;
      }
      else {
        length_x = 0;
        length_y = 0;
        mouse_state = INIT1;
      }
      break;

    case INIT2:;
      if (mouse_event.type == MOUSE_MOV) {
        if ((abs(pp->delta_x) > tolerance) | (abs(pp->delta_y) > tolerance)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        else {
          length_x += pp->delta_x;
          length_y += pp->delta_y;
        }
      }
      else if (mouse_event.type == LB_PRESSED) {
        length_x = 0;
        length_y = 0;
        mouse_state = DRAW1;
        break;
      }
      else if (mouse_event.type == RB_PRESSED) {
        mouse_state = DRAW2;
        break;
      }
      break;

    case DRAW2:
      if (mouse_event.type == MOUSE_MOV) {
        if (pp->delta_x < 0 && (abs(pp->delta_x) > tolerance)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        if (pp->delta_y > 0 && (abs(pp->delta_y) > tolerance)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        if (((double)pp->delta_y > -(double)pp->delta_x)) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }
        if (pp->x_ov || pp->y_ov) {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
          break;
        }

        length_x += pp->delta_x;
        length_y += pp->delta_y;

        break;
      }
      else if (mouse_event.type == RB_RELEASED) {
        if (length_x >= x_len) {
          length_x = 0;
          length_y = 0;
          mouse_state = FINAL;
          break;
        }
        else {
          length_x = 0;
          length_y = 0;
          mouse_state = INIT1;
        }
        break;
      }
      
      else if (mouse_event.type == LB_PRESSED) {
        mouse_state = DRAW1;
        break;
      }
      break;

    case FINAL:
      break;
  }
}


