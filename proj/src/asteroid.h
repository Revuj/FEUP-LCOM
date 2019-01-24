#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "bitmap.h"

#define ASTEROID1 "/home/lcom/labs/proj/bitmaps/asteroid/asteroid1.bmp"
#define ASTEROIDS_NUMBER  10

/** @defgroup Asteroid Asteroid
 * @{
 * Functions to manipulate the asteroids of the game
 */

/** @name Asteroid */
/**@{asteroid_class struct that holds the informations about an asteroid object
 */
typedef struct asteroid_class {
  Bitmap * ptr; /**< @brief pointer to asteroid's bitmap*/
  bool draw;  /**< @brief boolean that indicates if the asteroid is on the scren */
  int initial_x, initial_y; /**< @brief initial position of the asteroid */
  int last_x, last_y; /**< @brief last position of the asteroid */
  bool exploded; /**< @brief boolean that indicates if the asteroid is exploding */
} asteroid; /** @} endo of the asteoird_class struct */

int initialize_asteroids();
/**
 * @brief Sets asteroid's inicial position, randomly
 * 
 * @param ast - the asteroid whose position is to be set
 */
void random_asteroid(asteroid * ast);


/**
 * @brief Resets the asteroid's positions
 */
void reset_asteroids();

/**
 * @brief Terminates the asteroids
 */
void terminate_asteroids();
 /** @} end of Asteroid */

#endif
