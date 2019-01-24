#ifndef _LCOM_MOUSE_STATE_MACHINE_H_
#define _LCOM_MOUSE_STATE_MACHINE_H_

/**
 * enum with the state machine states 
*/
enum state_t {
  INIT1,
  DRAW1,
  INIT2,
  DRAW2,
  FINAL
};


enum state_t get_mouse_state();


/**
 * @brief returns a struct mouse_ev updated by the mouse packet
 *
 */
struct mouse_ev * mouse_check_event(struct packet *pp);


/**
 * @brief mouse state machine that checks 'upside down V' movement by the mouse
 *
 */
void mouse_event_handler(struct packet *pp,uint8_t x_len, uint8_t tolerance);


#endif 

