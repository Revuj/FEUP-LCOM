#ifndef _SCORE_H_
#define _SCORE_H_

#include "bitmap.h"
#include "stdint.h"

#define NUMBER0_PATH "/home/lcom/labs/proj/bitmaps/Score/number0.bmp"
#define NUMBER1_PATH "/home/lcom/labs/proj/bitmaps/Score/number1.bmp"
#define NUMBER2_PATH "/home/lcom/labs/proj/bitmaps/Score/number2.bmp"
#define NUMBER3_PATH "/home/lcom/labs/proj/bitmaps/Score/number3.bmp"
#define NUMBER4_PATH "/home/lcom/labs/proj/bitmaps/Score/number4.bmp"
#define NUMBER5_PATH "/home/lcom/labs/proj/bitmaps/Score/number5.bmp"
#define NUMBER6_PATH "/home/lcom/labs/proj/bitmaps/Score/number6.bmp"
#define NUMBER7_PATH "/home/lcom/labs/proj/bitmaps/Score/number7.bmp"
#define NUMBER8_PATH "/home/lcom/labs/proj/bitmaps/Score/number8.bmp"
#define NUMBER9_PATH "/home/lcom/labs/proj/bitmaps/Score/number9.bmp"
#define TWODOTS_PATH "/home/lcom/labs/proj/bitmaps/Score/twoDots.bmp"
#define BAR_PATH "/home/lcom/labs/proj/bitmaps/Score/bar.bmp"
#define LETTER_A_PATH "/home/lcom/labs/proj/bitmaps/Score/A.bmp"
#define LETTER_B_PATH "/home/lcom/labs/proj/bitmaps/Score/B.bmp"
#define LETTER_C_PATH "/home/lcom/labs/proj/bitmaps/Score/C.bmp"
#define LETTER_D_PATH "/home/lcom/labs/proj/bitmaps/Score/D.bmp"
#define LETTER_E_PATH "/home/lcom/labs/proj/bitmaps/Score/E.bmp"
#define LETTER_F_PATH "/home/lcom/labs/proj/bitmaps/Score/F.bmp"
#define LETTER_G_PATH "/home/lcom/labs/proj/bitmaps/Score/G.bmp"
#define LETTER_H_PATH "/home/lcom/labs/proj/bitmaps/Score/H.bmp"
#define LETTER_I_PATH "/home/lcom/labs/proj/bitmaps/Score/I.bmp"
#define LETTER_J_PATH "/home/lcom/labs/proj/bitmaps/Score/J.bmp"
#define LETTER_K_PATH "/home/lcom/labs/proj/bitmaps/Score/K.bmp"
#define LETTER_L_PATH "/home/lcom/labs/proj/bitmaps/Score/L.bmp"
#define LETTER_M_PATH "/home/lcom/labs/proj/bitmaps/Score/M.bmp"
#define LETTER_N_PATH "/home/lcom/labs/proj/bitmaps/Score/N.bmp"
#define LETTER_O_PATH "/home/lcom/labs/proj/bitmaps/Score/O.bmp"
#define LETTER_P_PATH "/home/lcom/labs/proj/bitmaps/Score/P.bmp"
#define LETTER_Q_PATH "/home/lcom/labs/proj/bitmaps/Score/Q.bmp"
#define LETTER_R_PATH "/home/lcom/labs/proj/bitmaps/Score/R.bmp"
#define LETTER_S_PATH "/home/lcom/labs/proj/bitmaps/Score/S.bmp"
#define LETTER_T_PATH "/home/lcom/labs/proj/bitmaps/Score/T.bmp"
#define LETTER_U_PATH "/home/lcom/labs/proj/bitmaps/Score/U.bmp"
#define LETTER_V_PATH "/home/lcom/labs/proj/bitmaps/Score/V.bmp"
#define LETTER_W_PATH "/home/lcom/labs/proj/bitmaps/Score/W.bmp"
#define LETTER_X_PATH "/home/lcom/labs/proj/bitmaps/Score/X.bmp"
#define LETTER_Y_PATH "/home/lcom/labs/proj/bitmaps/Score/Y.bmp"
#define LETTER_Z_PATH "/home/lcom/labs/proj/bitmaps/Score/Z.bmp"

#define BITMAP_NUMBER 10
#define SEPARATION_BETWEEN_BITMAPS 4
#define NUMBER_OF_LETTERS 26

/** @defgroup Score Score
 * @{
 * Functions to manipulate the game score
 */

/** @name Score */
/**@{score_class struct that holds the informations about the score of a player
 */
typedef struct score_class {
    unsigned int player_score;       /**< @brief current score of the game*/
    Bitmap * number[BITMAP_NUMBER];  /**< @brief number of bitmaps*/
    Bitmap * bar;
    Bitmap * two_dots;
    Bitmap * alphabet[26];
} Score; /** @} end of the score_class struct*/

/**
 * @brief Processes bitmaps with numbers
 * 
 * @return Returns 0 upon success or 1 otherwhise
 */
int initialize_score_bitmaps();

/**
 * @brief Allocates memory for the Score struct and initializes its field values
 *
 * @return Returns 0 upon success or 1 otherwhise
 */
Score* initialize_score();

/**
 * @brief actualizes the current score in the struct
 */
void atualize_score();

/**
 * @brief updates the game score by adding 1 to it
 */
void update_game_score();

/**
 * @brief Updates the game score by adding an extra value due to some reward
 *
 * @param Quantity of points to add to the current score
 */
void extra_score(unsigned int points);

/**
 * @brief Updates the game score by subtracting due to penalization
 *
 * @param Quantity of points to subtract from the current score
 */
void penalize_score(unsigned int points);

/**
 * @brief Calculates the number of digits that scores contains
 * 
 * @return the number of digits that score contains
 */
unsigned int calculate_number_size(); 


/**
 * @brief Draws the current score
 */
void draw_player_score();

/**
 * @brief Gets the current score
 * 
 * @return Returns the current score
 */ 
unsigned int get_score();


/**
 * @brief Draws a part of the current date on the screen
 * 
 * @param time - number to be drawn
 * @param x - x position where the number will be drawn
 * @param y - y position where the number will be drawn
 */
void draw_date_aux(uint32_t time, int x, int y);

/**
 * @brief Draws the date on the screen
 * 
 * @param date - date that will be drawn
 * @param x - x position where the date will be drawn
 * @param y - y position where the date will be drawn
 */
void draw_date(char *date,int x, int y);

/**
 * @brief Calculates de amount of digits in a number
 * 
 * @param number - number whose number of digits will be calculated
 * 
 * @return Returns the amount of digits in the number
 */
unsigned int calculate_size(int number);

/**
 * @brief Sets the current name
 * 
 * @param new_name - new name to be set
 */
void set_name(const char * new_name);

/**
 * @brief Gets the current name
 * 
 * @return Returns a pointer to the current name
 */
char * get_name();

/**
 * @brief Resets the name, setting it to all 0's
 */
void reset_name();

/**
 * @brief Calculates the size of the current name
 * 
 * @return Returns the size of the current name
 */
unsigned int get_name_size();

/**
 * @brief Draws a letter on the screen
 * 
 * @param letter - letter to be drawn
 * @param x - x position where the letter will be drawn
 * @param y - y position where the letter will be drawn
 */
void draw_char(char letter,int x, int y);

/**
 * @brief Draws the current name on the screen
 * 
 * @param x - x position where the name will be drawn
 * @param y - y position where the name will be drawn
 */
void draw_name(int x, int y);

/**
 * @brief Gets the score struct
 * 
 * @return Returns a pointer to the score struct
 */
Score * get_score_struct();

/**
 * @brief Draws a number on the screen
 * 
 * @param number - number to be drawn
 * @param x - x position where the number will be drawn
 * @param y - y position where the number will be drawn
 */
void draw_number(int number,int x, int y);

/**
 * @brief Adds letter, read by the keyboard handler, to the current name
 * 
 * @returns Returns 0 upon success or 1 otherwhise
 */
int process_letter();

/**
 * @brief Puts score back to 0
 */
void reset_score();

/**
 * @brief Deletes char on current name
 */
void delete_char();

/**
 * @brief Gives the player a default name if he didnt input any
 */
void default_name();

/**
 * @brief Frees all the memory allocated
 */
void terminate_score();

/**
 * @brief Saves leaderboard on the file "leaderboard.txt"
 */
void load_leaderboard();

/**
 * @brief Reads the leaderboard from the file "leaderboard.txt"
 */
void save_leaderboard();

/** @} end of Score */


#endif
