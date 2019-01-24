#ifndef _HEALTH_H_
#define _HEALTH_H_

#include "bitmap.h"
#include <stdbool.h>

#define NUMBER_OF_LIFES    5
#define HEALTH_ID        101 

#define ASTRONAUT_LIFE_PATH "/home/lcom/labs/proj/bitmaps/astronauta/heart.bmp"

/** @defgroup Health Health
 * @{
 * Functions to manipulate the health packs in the game
 */

/** @name health_point */
/** @{health_class struct that holds the information about health points */
typedef struct health_class {
    Bitmap * ptr; /**< @brief pointer to its bitmap */
    bool draw; /**< @brief boolean that indicates if the health point is on the screen*/
    Bitmap *life[NUMBER_OF_LIFES];  /**< @brief pointer to the healt points' bitmaps*/
    int actual_number_of_lifes; /** < @brief current number of health points on the astronaut*/
} health_point; /** @} end of the health_class struct*/

/**
 * @brief Allocates the necessary space for the health bitmaps
 * 
 * @return Return 0 if the bitmaps were successfully initialized
 */
int initialize_health_bitmaps();

/**
 * @brief Allocates the necessary space for the health_point struct
 * 
 * @return Return 0 if the struct was successfully initialized
 */
int initialize_health();

/**
 * @brief Draws on the screen the health points that the astronaut has currently
 */
void draw_health_bitmaps();

/**
 * @brief Erases healh bitmap caught by the astronaut and increases his health points
 */
void catch_one_life(Bitmap * bmp, int x, int y, int id);

/**
 * @brief Draws new health point
 * 
 * @param x - x position where the health point will be drawn
 * @param y - y position where the health point will be drawn
 */
void spawn_health_point(int x, int y);

/**
 * @brief Updates the health points' positions that spawned
 */
void update_health_point();

/**
 * @brief Decrements the astronaut's health points number
 * 
 * @return Returns the currently number of health points
 */
int lose_life();

/**
 * @brief Sets the astronaut's health points back to its maximum number
 */
void set_full_health();

/**
 * @brief Sets the astronaut's health points
 */
void reset_health();

/**
 * @brief Frees all the memory allocated
 */
void terminate_health_class();
 /** @} end of Health */


#endif 
