#ifndef _BULLET_H_
#define _BULLET_H_

#include <stdbool.h> 
#include "bitmap.h"

#define ASTRONAUT_BULLET_PATH "/home/lcom/labs/proj/bitmaps/astronauta/bullet.bmp"
#define BULLET "/home/lcom/labs/proj/bitmaps/bullet.bmp"

#define NUMBER_OF_BULLETS 20

/** @defgroup Bullet Bullet
 * @{
 * Functions to manipulate the bullets shot by the astronaut
 */

/** @name bullet */
/**@{bullet_class struct that holds the informations about a bullet contained on a noded list */
typedef struct bullet_class {
    Bitmap * ptr; /**< @brief pointer to its bitmap*/
    struct bullet_class * next; /**< @brief pointer to the bitmap of the next bullet on the list*/
    bool draw; /**< @brief boolean that indicates if the bullets is on the screen */
} bullet; /** @} end of the bullet_class struct*/

/** @name Gun */
/** {gun_class struct that holds the information about the current astronaut weaponry*/
typedef struct gun_class {
     Bitmap * bullets[NUMBER_OF_BULLETS]; /**< @brief pointer do the current bullets*/
     unsigned int actual_number_of_bullets; /**< @brief number of the current bullets on the gun */
     bool reloading; /**< @brief boolean that indicates if the astronaut is reloading*/
     bullet * bullet; /**< @brief pointer to the noded list of bullets*/
} Gun; /** @} end of the gun_class struct*/

/**
 * @brief Initializes bullet bitmap that belongs to a noded list
 * 
 * @return Returns 0 if the bullet is correctly initialized
 */
int initialize_gun();

/**
 * @brief Initializes the noded list that holds the bullets
 * 
 * @return Returns 0 if bullets are correctly initialized
 */
int initialize_bullets_bitmap();


/**
 * @brief Draws the bullet bitmaps that represent how many bullets the astronaut still holds on his gun
 */
void draw_bullets();

/**
 * @brief Sets the "reloading" flag
 */
void set_reloading();

/**
 * @brief Unsets the "reloading" flag
 */
void unset_reloading();

/**
 * @brief Adds one bullet to the current ones that the astronaut is holding
 */
void reload_bullets() ;

/**
 * @brief Removes one bullet to the current ones that the astronaut is holding
 * 
 * @return Returns 0 if the astronaut it out of bullets
 */
int shoot_bullet() ;

/**
 * @brief Draws the bullets that were reloaded
 */
void draw_reload_bullets();

/**
 * @brief Updates the position of all the bullets that were shot
 */
void update_bullets();

/**
 * @brief Creates a new bullet, if one was shot
 * 
 * @param current - the bullet before this one on the noded list
 * @param x - initial bullet's x position
 * @param y - initial bullet's y position
 * 
 * @return Returns pointer that points to the bullet's bitmap
 */
Bitmap * new_bullet(bullet * current,int x, int y);

/**
 * @brief Gets us our "gun" struct wich contains the information about the gun and its bullets
 * 
 * @return Return the "gun" struct
 */
Gun * get_gun();

/**
 * @brief Resets the bullets, making them the same as initially
 */
void reset_bullets();

/**
 * @brief Destroys every bullet and frees the space used
 */
void terminate_bullet_class();
 /** @} end of Bullet */

#endif 

