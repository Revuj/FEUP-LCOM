#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#include <stdint.h>

/** @defgroup Vbe Vbe
 * @{
 * Functions the return values related to the graphics
 */

/**
 * @brief Returns horizontal resolution
 */
uint16_t get_hres();

/**
 * @brief Returns vertical resolution
 */
uint16_t get_vres();

/**
 * @brief Returns bits per pixel
 */
uint8_t get_bbp();

/**
 * @brief Returns pointer to video memory
 */
char * get_video_mem();

/**
 * @brief Returns pointer to the second buffer
 */
char * get_second_buffer();

/**
 * @brief Copies second buffer to video memory
 */
void copy_buffer();

/**
 * @brief Clears second buffer
 */
void clear_second_buffer();

/** @} end of Video_gr */

#endif /*__VIDEO_GR_H */
