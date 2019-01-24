#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_
#include <lcom/lcf.h>
#include "i8042.h"


#include <stdint.h>

/*
 * @brief Subscribes and enables Keyboard interrupts
 *
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_subscribe_int(uint8_t *bit_no);


/**
 * @brief Unsubscribes Keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_unsubscribe_int();


/**
 * @brief checks if the scancode is a makecode or breakcode
 *
 * @param scancode contains the scancode
 * @param size contains the size of the scancode
 * 
 * @return true if is a makecode or false if is a breakcode
 */
bool is_make(const uint8_t scancode[],const uint8_t size);


/**
 * @brief reads scancode bytes
 * 
 * @param *second_byte acts like a flag if there is one or two bytes to read
 * @param scancode_byte contains the scancode byte
 * @param scancode[] where all the bytes of the scancode (1 or 2) are stored
 * 
 * @return Return true if there is just one byte scancode to read or false if there are two
 */
bool get_scancode(uint8_t * second_byte,uint8_t scancode_byte, uint8_t scancode[]);


/**
 * @brief checks the scancode size
 *
 * @return Returns 1 or 2 depending on the scancode
 */
uint scancode_size(uint8_t byte);


/**
 * @brief reads the output buffer
 *
 * @return true upon success or false otherwise
 */
bool kbd_read_obf();


/**
 * @brief writes byte on command register
 *
 * @return true upon success or false otherwise
 */
int kbc_write_command(uint16_t command);


/**
 * @brief writes byte on command register and its argument on output buffer
 *
 * @return true upon success or false otherwise
 */
int kbc_write_command_with_argument(uint16_t command, uint16_t argument);


/**
 * @brief get data
 *
 * @return Returns the global variable data defined in the keyboard's scope
 */
uint32_t get_data();


/**
 * @brief get error_flag
 *
 * @return Returns the global variable error_flag defined in the keyboard's scope*/
int get_error();




#endif 

