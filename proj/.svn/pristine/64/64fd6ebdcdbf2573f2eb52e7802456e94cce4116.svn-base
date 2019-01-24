#ifndef _COLISION_H_
#define _COLISION_H_

#include "bitmap.h"

/** @defgroup Colision Colision
 * @{
 * Functions to detect colision between certain objects in the game
 */

/**
 * @brief Initializes our colision's map, allocating the necessary space
 * 
 * @return Returns 0 if everything was initialized correctly
 */
int initialize_map_colision();

/**
 * @brief Checks if there are collisions and maps one bitmap
 *
 * @param bmp - bitmap to be written on the map
 * @param x - position in the x of the bitmap
 * @param y - position in the y of the bitmap
 * @param id - number that identifies a certain object
 * 
 * @return Returns a different number accordingly to the colision that happens (0 if it does not happen)
 */
int map_colision(Bitmap * bmp, int x, int y, int id);

/**
 * @brief Clears the map of collisions
 */
void clear_colisions_map();

/**
 * @brief Gets us a pointer to the colisions map
 * @return Returns pointer to colisions map
 */
char *get_colisions_map() ;

/**
 * @brief Frees the space used by the map
 */
void terminate_map_colision();
 /** @} end of Colision */

#endif
