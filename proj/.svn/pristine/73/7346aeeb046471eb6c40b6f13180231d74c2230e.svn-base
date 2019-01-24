#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_
#include <lcom/lcf.h>


/** @defgroup Mouse Mouse
 * @{
 * Functions to manipulate the mouse and it's interruptions
 */

/**
 * @brief Subscribes mouse interrupts
 *
 * @return Returns 0 upon sucess or 1 otherwhise
 */
int mouse_subscribe_int(uint8_t *bit_no);


/**
 * @brief Unsubscribes mouse interrupts
 *
 * @return Returns 0 upon sucess or 1 otherwhise
 */
int mouse_unsubscribe_int();


/**
 * @brief Checks is read data is valid
 *
 * @return Returns true upon success or false otherwise
 */
bool mouse_is_valid_data(uint32_t stat);


/**
 * @brief returns data variable
 *
 */
uint32_t mouse_get_data();


/**
 * @brief Returns mouse_error_flag variable
 *
 */
int mouse_get_error();


/**
 * @brief Reads kbc output buffer
 *
 * @return Returns true upon success or false otherwise
 */
bool mouse_read_obf();


/**
 * @brief Inserts mouse byte into packet
 *
 * @param packet_byte - byte that will be filled with the info
 * 
 * @return Returns true upon success or false otherwise
 */
bool get_packet(uint8_t packet_byte);

/**
 * @brief Get the mouse object
 * 
 * @return struct packet 
 */
struct packet get_mouse();

/**
 * @brief Writes command directed to the mouse
 *
 * @param command - command to be written
 * 
 * @return Returns 0 upon success or 1 otherwise
 */
int mouse_write_command(uint16_t command);


/**
 * @brief Disables mouse interrupts to output buffer
 *
 * @return Returns 1 upon success or 0 otherwise
 */
int mouse_disable_interrupts();


/**
 * @brief Enables mouse interrupts to output buffer
 *
 * @return Returns 0 upon success or 1 otherwise
 */
int mouse_enable_interrupts();

/**
 * @brief Calls the mouse interrupt handler and updates its status
 *
 */
void game_mouse_ih();

/**
 * @brief Updates cursor's position and creates new bullets if the left button is being pressed
 * 
 */
void change_mouse();

/**
 * @brief Resets the keyboard back to its initial state and loads a new bitmaps that represents the cursor
 * 
 * @param path - string that represents the path of the bitmap to be loaded
 */
void reset_mouse(const char * path);
/** @} end of Keyboard */



#endif
