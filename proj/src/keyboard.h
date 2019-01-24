#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_
#include <stdint.h>
#include "i8042.h"


#include <stdint.h>

/** @defgroup Keyboard Keyboard
 * @{
 * Functions to manipulate the keyboard and it's interruptions
 */

/**
 * @brief Subscribes and enables Keyboard interrupts
 *
 * @param bit_no - address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * @return Returns 0 upon success and non-zero otherwise
 */
int kbc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes Keyboard interrupts
 *
 * @return Returns 0 upon success and non-zero otherwise
 */
int kbc_unsubscribe_int();

/**
 * @brief Checks if the data is valid
 * @param stat - contains the value of the status keyboard
 * @return Returns true upon success and false otherwise
 */
bool is_valid_data(uint32_t stat);

/**
 * @brief Checks if the scancode is a makecode or breakcode
 *
 * @param scancode - contains the scancode
 * @param size - contains the size of the scancode
 * 
 * @return Returns True if is a makecode or false if is a breakcode
 */
bool is_make(const uint8_t scancode[],const uint8_t size);

/**
 * @brief Reads scancode bytes
 * 
 * @param *second_byte - acts like a flag if there is one or two bytes to read
 * @param scancode_byte - contains the scancode byte
 * @param scancode - where all the bytes of the scancode (1 or 2) are stored
 * 
 * @return Returns true if there is just one byte scancode to read or false if there are two
 */
bool get_scancode(uint8_t * second_byte,uint8_t scancode_byte, uint8_t scancode[]);

/**
 * @brief Checks the scancode size
 *
 * @return Returns 1 or 2 depending on the scancode
 */
uint scancode_size(uint8_t byte);

/**
 * @brief Reads the output buffer
 *
 * @return True upon success or false otherwise
 */
bool kbd_read_obf();


/**
 * @brief Writes byte on command register
 *
 * @param command - command to be written on the command register
 * 
 * @return Returns 0 upon success or 1 otherwise
 */
int kbc_write_command(uint16_t command);


/**
 * @brief Writes byte on command register and its argument on output buffer
 *
 * @param command - command to be written on the command register
 * @param argument - argument of the respective command
 * 
 * @return Returns 0 upon success or 1 otherwise
 */
int kbc_write_command_with_argument(uint16_t command, uint16_t argument);


/**
 * @brief Acts as the interrupt handler in the game
 *
 * @return 0 upon success or 1 otherwise
 */
 int game_kbc_ih();

/**
 * @brief Gets data
 *
 * @return Returns the global variable data defined in the keyboard's scope
 */
uint32_t kbc_get_data();

/**
 * @brief Gets error_flag
 *
 * @return Returns the global variable error_flag defined in the keyboard's scope
 */
int kbc_get_error();

/**
 * @brief Processes the events accordingly
 *  
 * @param scancode_byte - current data read on the kbc output buffer
 * 
 */
void keyboard_event_handler(uint8_t scancode_byte);


/**
 * @brief Resets the keyboard back to its initial state
 */
void reset_keyboard();
 /** @} end of Keyboard */


#endif 

