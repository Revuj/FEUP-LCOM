#ifndef _GAME_H_
#define _GAME_H_
#include "asteroid.h"
#include "menu.h"
#include "bullet.h"
#include "health.h"
#include "Score.h"
#include "satellite.h"
#include "timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "video_gr.h"
#include "Colision.h"
#include "rtc.h"

#define INITIAL_GRAVITY     6
#define FPS                60
#define PENALTY           500
#define GAMEOVER_X        375
#define GAMEOVER_Y        410
#define UPDATE_LEVEL     1800
#define PRINT_LEVEL       100

#define ASTRONAUT_PATH1 "/home/lcom/labs/proj/bitmaps/astronauta/astro_fogo1.bmp"
#define ASTRONAUT_PATH2 "/home/lcom/labs/proj/bitmaps/astronauta/astro_fogo2.bmp"
#define ASTRONAUT_PATH3 "/home/lcom/labs/proj/bitmaps/astronauta/astro_fogo3.bmp"
#define ASTRONAUT_PATH4 "/home/lcom/labs/proj/bitmaps/astronauta/astro_fogo4.bmp"
#define ASTRONAUT_PATH5 "/home/lcom/labs/proj/bitmaps/astronauta/astro_fogo5.bmp"
#define ASTRONAUT_PATH6 "/home/lcom/labs/proj/bitmaps/astronauta/astro_perder_vida.bmp"
#define ASTRONAUT_ARM_PATH "/home/lcom/labs/proj/bitmaps/astronauta/braco_astro.bmp"
#define ASTRONAUT_LIFE_PATH "/home/lcom/labs/proj/bitmaps/astronauta/heart.bmp"


#define BACKGROUND_PATH "/home/lcom/labs/proj/bitmaps/background"
#define MOUSE_PATH "/home/lcom/labs/proj/bitmaps/oi.bmp"
#define EXPLOSION1 "/home/lcom/labs/proj/bitmaps/asteroid/explosion1.bmp"
#define EXPLOSION2 "/home/lcom/labs/proj/bitmaps/asteroid/explosion2.bmp"
#define EXPLOSION3 "/home/lcom/labs/proj/bitmaps/asteroid/explosion3.bmp"
#define EXPLOSION4 "/home/lcom/labs/proj/bitmaps/asteroid/explosion4.bmp"
#define EXPLOSION5 "/home/lcom/labs/proj/bitmaps/asteroid/explosion5.bmp"
#define EXPLOSION6 "/home/lcom/labs/proj/bitmaps/asteroid/explosion6.bmp"
#define EXPLOSION7 "/home/lcom/labs/proj/bitmaps/asteroid/explosion7.bmp"
#define EXPLOSION8 "/home/lcom/labs/proj/bitmaps/asteroid/explosion8.bmp"
#define EXPLOSION9 "/home/lcom/labs/proj/bitmaps/asteroid/explosion9.bmp"
#define EXPLOSION10 "/home/lcom/labs/proj/bitmaps/asteroid/explosion10.bmp"

static int damage = 0;

typedef struct hook_bit_class{
    uint8_t timer_bit_no;
    uint8_t mouse_bit_no;
    uint8_t keyboard_bit_no;
   
} hook_bit;

/** @name leaderboard */
/** @{struct that holds the information about a play, of a player */
typedef struct {
    char name[11]; /**< @brief player's name*/
    unsigned int score; /**< @brief player's score*/
    char* date; /**< @brief player's play date*/
} leaderboard; /** @} end of the leaderboard struct*/


/** @name Game */
/** @{struct that holds the information about the game */
typedef struct {
    state_machine state; /**< @brief state machine that represents the game */
    struct main_menu the_menu; /**< @brief menu of the game */
    hook_bit bit_no_selection; /**< @brief bit_no's of the game */
    Bitmap *astronaut[7]; /**< @brief astronaut bitmaps */
    Bitmap *mouse ; /**< @brief mouse's bitmap */
    Score * score; /**< @brief current score of the game */
    asteroid *asteroid[10]; /**< @brief asteroids in the game*/
    satellite *satellite[5]; /**< @brief satellites in the game*/
    Bitmap * explosion[10]; /**< @brief explosions bitmaps*/
    Bitmap * background; /**< @brief background bitmap*/
    leaderboard leaderboard[5]; /**< @brief leaderboard of the game (top 5) */
    unsigned int leaderboard_size; /**< @brief size of the leaderboard*/
    bool reading_name; /**< @brief boolean that indicates if a name is being read, to be saved */
    int gravity; /**< @brief gravity of the game*/
    int game_level; /**< @brief level of the game*/
    int end_game; /**< @brief indicates if the game is over */

} Game; /** @} end of the Game struct*/

/**
 * @brief Get the game object
 * 
 * @return Returns pointer to game 
 */
Game * get_game();

/**
 * @brief Initializes the mouse bitmaps
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_mouse_bitmap();

/**
 * @brief Initialize main menu
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_mainmenu();

/**
 * @brief Initializes graphics card
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_graphics_card();

/**
 * @brief Initializes the timer, subscribing to its interrupts
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_timer();

/**
 * @brief Initializes the keyboard, subscribing to its interrupts
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_kbc();

/**
 * @brief Initializes the mouse, subscribing to its interrupts
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_mouse();

/**
 * @brief Initializes the astronaut and its bitmaps
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_astronaut();

/**
 * @brief Initializes the objects of the game
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_objects();

/**
 * @brief Initializes the game's background 
 * 
 * @return Returns 0 upon success, 1 otherwhise
 */
int initialize_background();

/**
 * @brief Initializes the game
 * 
 * @return Returns pointer to the game
 */
void *initialize_game();

/**
 * @brief Updated the astronaut position
 */
void update_astronaut_position();

/**
 * @brief Updates the astronaut
 * 
 * @param damage - pointer to the damage that the astronaut takes
 */
void update_astronaut(int * damage);

/**
 * @brief Updates the position of the mouse
 */
void update_mouse();

/**
 * @brief Aplies "gravity" force on the astronaut
 * 
 */
void gravity();

/**
 * @brief Explodes an asteroid
 * 
 * @param asteroid - asteroid to be exploded
 */
void explosion(asteroid * asteroid);

/**
 * @brief Explodes a satellite
 * 
 * @param satellite - satellite to be exploded
 */
void satellite_explosion(satellite * satellite);

/**
 * @brief Updates the explosions currently happening on the scren
 */
void update_explosions();

/**
 * @brief Updates the satellites
 */
void update_satellites();

/**
 * @brief Updates the asteroids
 */
void update_asteroids();

/**
 * @brief Updates the damage taken by the astronaut
 * 
 * @return Returns a different number depending on the colision
 */
int damage_on_astronaut();

/**
 * @brief Updates the level of the game
 */
void update_level();

/**
 * @brief Prints the level when it changes
 */
void print_level();

/**
 * @brief Displays on the screen, information about the leaderboard
 */
void show_leaderboard();

/**
 * @brief Displays the main_menu on the screen and returns different events that depend where the user clicks
 * 
 * @return Returns an event for the game state machine to process
 */
event_type main_menu();

/**
 * @brief Displays the leaderboard on the screen and returns different events that depend where the user clicks
 * 
 * @return Returns an event for the game state machine to process
 */
event_type lead_board();

/**
 * @brief Displays the saving score menu n the screen and returns different events that depend where the user clicks
 * 
 * @return Returns an event for the game state machine to process
 */
event_type saving_score();

/**
 * @brief Displays on the screen, the state of the game
 * 
 * @return Returns an event for the game state machine to process
 */
event_type update_game_state();

/**
 * @brief Processes the events of the game
 * 
 * @return Returns 0 upon success or 1 otherwhise
 */
int process_events();

/**
 * @brief Functions where the handlers are called, to process their respective interrupts
 * 
 * @return Returns 0 upon success or 1 otherwhise
 */
int play_game();

/**
 * @brief Saves the information of a player on the score if it has a top 5 score
 * 
 * @param name - name of the player
 * @param date - date when the player played the game
 * @param score - score obtained by the player
 */
void save_score(char * name, char * date, unsigned int score);

/**
 * @brief Resets the astronaut puting it back on its initial position and also resets its objects
 */
void reset_astronaut();

/**
 * @brief Resets the background, puting in on its initial position
 */
void reset_background();

/**
 * @brief Resets the game by calling the necessary functions to do so
 */
void reset_game();

/**
 * @brief Frees the space allocated for the background
 */
void terminate_background();

/**
 * @brief Frees the space allocated for the 
 */
void terminate_game_score();

/**
 * @brief Frees the space allocated for the mouse
 * 
 */
void terminate_mouse_bitmap();

/**
 * @brief Terminates the bitmaps by freeing the space allocated initially
 */
void terminate_bitmaps();

/**
 * @brief Terminates the main menu by freeing the space allocated to it
 */
void terminate_main_menu();

/**
 * @brief Frees the space allocated for the astronaut, initially
 */
void terminate_astronaut();

/**
 * @brief Frees the space allocated for the objects of the game, initially
 */
void terminate_objects();

/**
 * @brief Calls the necessary functions to terminate the game
 */
void terminate_game();




#endif /*_GAME_H_*/
