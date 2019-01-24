#ifndef _MENU_H_
#define _MENU_H_
#include "bitmap.h"

#define BACKGROUNDMENU_PATH "/home/lcom/labs/proj/bitmaps/menu/menu_background.bmp"
#define MOON_CURSOR_PATH "/home/lcom/labs/proj/bitmaps/menu/moon_cursor.bmp"
#define ASTRO_MENU1_PATH  "/home/lcom/labs/proj/bitmaps/menu/Astronauta1.bmp"
#define ASTRO_MENU2_PATH   "/home/lcom/labs/proj/bitmaps/menu/Astronauta2.bmp"
#define ASTRO_MENU3_PATH "/home/lcom/labs/proj/bitmaps/menu/Astronauta3.bmp"
#define STARTGAME_BUTTON1_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_newgame.bmp"
#define STARTGAME_BUTTON2_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_newgame_1.bmp"
#define EXIT_BUTTON1_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_exit.bmp"
#define EXIT_BUTTON2_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_exit_1.bmp"
#define LEADERBOARD1_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_leaderboard.bmp"
#define LEADERBOARD2_PATH "/home/lcom/labs/proj/bitmaps/menu/rsz_leaderboard_1.bmp"
#define TITLE_PATH "/home/lcom/labs/proj/bitmaps/menu/titulo.bmp"    
#define GAMEOVER_PATH "/home/lcom/labs/proj/bitmaps/menu/GameOver.bmp"   
#define MENU_PATH "/home/lcom/labs/proj/bitmaps/menu/Menu.bmp"
#define MENU_PATH2 "/home/lcom/labs/proj/bitmaps/menu/Menu1.bmp"
#define LEADERBOARD_BACKGROUND_PATH "/home/lcom/labs/proj/bitmaps/menu/leaderboard.bmp"


/** @name main_menu */
/** @{struct that holds the information about the menu of the game*/
struct main_menu {
    Bitmap * menu_background; /**< @brief pointer to the menu's background */
    Bitmap * astro [3]; /**< @brief pointer to the menu's astronaut's bitmaps */
    Bitmap * play [2]; /**< @brief pointer to the menu's play button's bitmaps */
    Bitmap * scores [2]; /**< @brief pointer to the menu's score button's bitmaps */
    Bitmap * exit_game [2]; /**< @brief pointer to the menu's exit button's bitmaps */
    Bitmap * title ; /**< @brief pointer to the menu's title bitmap*/
    Bitmap *gameover; /**< @brief pointer to the menu's gameover bitmap*/
    Bitmap *menu[2]; /**< @brief pointer to the menu's button*/
    Bitmap * background_leaderboard; /**< @brief pointer to the leaderboard's button*/
}; /** @} end of the main_menu struct*/

typedef enum
{
    MENU,
    LEADERBOARD,
    PLAYING,
    SAVESCORE,
} state_machine;

typedef enum
{
    PLAY_BUTTON, // no menu principal
    EXIT_BUTTON, // no menu principal
    BACK_TO_MENU_BUTTON, // durante jogo
    LEADERBOARD_BUTTON, // no menu principal
    RESET_GAME_BUTTON, // durante jogo
    LOST_BUTTON // durante o jogo e serve para retornar para o menu principal
} event_type;






#endif
