#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_
#include <lcom/lcf.h>

/**
 * @brief subscribes mouse interrupts
 *
 * @return true upon success or false otherwise
 */
int mouse_subscribe_int(uint8_t *bit_no);


/**
 * @brief unsubscribes mouse interrupts
 *
 * @return true upon success or false otherwise
 */
int mouse_unsubscribe_int();


/**
 * @brief checks is read data is valid
 *
 * @return true upon success or false otherwise
 */
bool mouse_is_valid_data(uint32_t stat);


/**
 * @brief returns data variable
 *
 */
uint32_t mouse_get_data();


/**
 * @brief returns mouse_error_flag variable
 *
 */
int mouse_get_error();


/**
 * @brief reads kbc output buffer
 *
 * @return true upon success or false otherwise
 */
bool mouse_read_obf();


/**
 * @brief inserts mouse byte into packet
 *
 * @return true upon success or false otherwise
 */
bool get_packet(uint8_t packet_byte, struct packet * pp, uint8_t * byte_counter);


/**
 * @brief writes command directed to the mouse
 *
 * @return true upon success or false otherwise
 */
int mouse_write_command(uint16_t command);


/**
 * @brief disables mouse interrupts to output buffer
 *
 * @return true upon success or false otherwise
 */
int mouse_disable_interrupts();


/**
 * @brief enables mouse interrupts to output buffer
 *
 * @return true upon success or false otherwise
 */
int mouse_enable_interrupts();



#endif
