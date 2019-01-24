#ifndef _SATELLITE_H_
#define _SATELLITE_H_

#include "bitmap.h"

#define SATELLITE "/home/lcom/labs/proj/bitmaps/satellite/satellite1.bmp"
#define SATELLITES_NUMBER 5

/** @defgroup Satellite
 * @{
 * Functions to manipulate the satellites of the game
 */

/** @name satellite */
/** @{satellite_class struct that holds the informations about a satellite */
typedef struct satellite_class {
  Bitmap * ptr; /**< @brief pointer to the asteroid's bitmap */
  int initial_x, initial_y; /**< @brief initial position of the asteroid */
  int last_x, last_y; /**< @brief final position of the asteroid */
  bool exploded; /**< @brief boolean that indicates if the asteroid is exploded */
} satellite; /** @} end of the satellite_class struct*/

int initialize_satellites();
/**
 * @brief Sets satellite's inicial position, randomly
 * 
 * @param sat - the satellite whose position is to be set
 */
void random_satellite(satellite * sat);

/**
 * @brief Resets the satellite's positions
 */
void reset_satellites();

/**
 * @brief Terminates the satellites
 */
void terminate_satellites();
 /** @} end of Satellite */
#endif

