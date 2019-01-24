#include "Score.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"
#include "Game.h"

static Score *score;
static char name[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
static int cap = 0;
static unsigned int score_points;

int initialize_score_bitmaps()
{
    for (uint8_t i = 0; i < BITMAP_NUMBER; i++)
    {
        score->number[i] = (Bitmap *)malloc(sizeof(Bitmap *));
    }
    score->number[0] = load_bitmap_file(NUMBER0_PATH);
    score->number[1] = load_bitmap_file(NUMBER1_PATH);
    score->number[2] = load_bitmap_file(NUMBER2_PATH);
    score->number[3] = load_bitmap_file(NUMBER3_PATH);
    score->number[4] = load_bitmap_file(NUMBER4_PATH);
    score->number[5] = load_bitmap_file(NUMBER5_PATH);
    score->number[6] = load_bitmap_file(NUMBER6_PATH);
    score->number[7] = load_bitmap_file(NUMBER7_PATH);
    score->number[8] = load_bitmap_file(NUMBER8_PATH);
    score->number[9] = load_bitmap_file(NUMBER9_PATH);

    score->bar = (Bitmap *)malloc(sizeof(Bitmap *));
    score->two_dots = (Bitmap *)malloc(sizeof(Bitmap *));
    score->bar = load_bitmap_file(BAR_PATH);
    score->two_dots = load_bitmap_file(TWODOTS_PATH);

    for (uint8_t i = 0; i < NUMBER_OF_LETTERS; i++) {
        score->alphabet[i] = (Bitmap *)malloc(sizeof(Bitmap *));
    }

    score->alphabet[0] = load_bitmap_file(LETTER_A_PATH);
    score->alphabet[1] = load_bitmap_file(LETTER_B_PATH);
    score->alphabet[2] = load_bitmap_file(LETTER_C_PATH);
    score->alphabet[3] = load_bitmap_file(LETTER_D_PATH);
    score->alphabet[4] = load_bitmap_file(LETTER_E_PATH);
    score->alphabet[5] = load_bitmap_file(LETTER_F_PATH);
    score->alphabet[6] = load_bitmap_file(LETTER_G_PATH);
    score->alphabet[7] = load_bitmap_file(LETTER_H_PATH);
    score->alphabet[8] = load_bitmap_file(LETTER_I_PATH);
    score->alphabet[9] = load_bitmap_file(LETTER_J_PATH);
    score->alphabet[10] = load_bitmap_file(LETTER_K_PATH);
    score->alphabet[11] = load_bitmap_file(LETTER_L_PATH);
    score->alphabet[12] = load_bitmap_file(LETTER_M_PATH);
    score->alphabet[13] = load_bitmap_file(LETTER_N_PATH);
    score->alphabet[14] = load_bitmap_file(LETTER_O_PATH);
    score->alphabet[15] = load_bitmap_file(LETTER_P_PATH);
    score->alphabet[16] = load_bitmap_file(LETTER_Q_PATH);
    score->alphabet[17] = load_bitmap_file(LETTER_R_PATH);
    score->alphabet[18] = load_bitmap_file(LETTER_S_PATH);
    score->alphabet[19] = load_bitmap_file(LETTER_T_PATH);
    score->alphabet[20] = load_bitmap_file(LETTER_U_PATH);
    score->alphabet[21] = load_bitmap_file(LETTER_V_PATH);
    score->alphabet[22] = load_bitmap_file(LETTER_W_PATH);
    score->alphabet[23] = load_bitmap_file(LETTER_X_PATH);
    score->alphabet[24] = load_bitmap_file(LETTER_Y_PATH);
    score->alphabet[25] = load_bitmap_file(LETTER_Z_PATH);

    if (score->bar == NULL || score->two_dots == NULL)
    {
        return 1;
    }

    for (uint8_t i = 0; i < BITMAP_NUMBER; i++)
    {
        if (score->number[i] == NULL)
        {
            return 1;
        }
    }
    return OK;
}

Score *initialize_score()
{
    score = (Score *)malloc(sizeof(Score *));
    score_points = 0;
    score->player_score = 0;
    initialize_score_bitmaps();

    return score;
}

void atualize_score()
{
    score->player_score = score_points;
}

void update_game_score()
{
    score_points++;
    atualize_score();
    draw_player_score();
}

void extra_score(unsigned int points)
{
    score_points += points;
    atualize_score();
}

void penalize_score(unsigned int points)
{
    if ((int)(score_points - points) <= 0)
    {
        score_points = 0;
    }
    else
    {
        score_points -= points;
    }

    atualize_score();
}

unsigned int calculate_number_size()
{

    unsigned int score_temp = score->player_score;
    unsigned int counter = 0;
    while (score_temp != 0)
    {
        score_temp /= 10;
        counter++;
    }
    if (counter == 0)
    {
        return 1;
    }
    return counter;
}

unsigned int get_score()
{
    return score_points;
}

void draw_player_score()
{
    uint16_t space_between_numbers = score->number[0]->bitmapInfoHeader.width + SEPARATION_BETWEEN_BITMAPS;
    uint16_t x = get_hres() - 2 * space_between_numbers;
    unsigned int number_size = calculate_number_size();
    for (uint8_t i = 0; i < number_size; i++)
    {
        draw_bitmap(score->number[score->player_score % 10], x, space_between_numbers, get_second_buffer());
        (score->player_score) /= 10;
        x -= space_between_numbers;
    }
}

void draw_date_auxiliar(uint32_t time, int x, int y)
{
    uint16_t space_between_numbers = score->number[0]->bitmapInfoHeader.width + SEPARATION_BETWEEN_BITMAPS;
    for (uint8_t i = 0; i < 2; i++)
    {
        draw_bitmap(score->number[time % 10], x, y, get_second_buffer());
        time /= 10;
        x -= space_between_numbers;
    }
}

void draw_date(char *date, int x, int y)
{
    uint32_t second, minute, hour, day, month, year;
    sscanf(date, "%d %d %d %d %d %d", &hour, &minute, &second, &day, &month, &year);

    int delta = score->number[0]->bitmapInfoHeader.width + 4;

    draw_date_auxiliar(hour, x, y);
    x += delta;
    draw_bitmap(score->two_dots, x, y, get_second_buffer());
    x += 2 * delta;
    draw_date_auxiliar(minute, x, y);
    x += delta;
    draw_bitmap(score->two_dots, x, y, get_second_buffer());
    x += 2 * delta;
    draw_date_auxiliar(second, x, y);
    x += 4 * delta;


    draw_date_auxiliar(day, x, y);
    x += delta;
    draw_bitmap(score->bar, x, y, get_second_buffer());
    x += 2 * delta;

    draw_date_auxiliar(month, x, y);
    x += delta;
    draw_bitmap(score->bar, x, y, get_second_buffer());
    x += 2 * delta;

    draw_date_auxiliar(year, x, y);
}

Score * get_score_struct() {
    return score;
}

unsigned int  calculate_size(int number) {
    unsigned int counter = 0;
    while (number != 0)
    {
        number /= 10;
        counter++;
    }
    if (counter == 0)
    {
        return 1;
    }
    return counter;
}

void draw_number(int number,int x, int y) {

    uint16_t space_between_numbers = score->number[0]->bitmapInfoHeader.width + SEPARATION_BETWEEN_BITMAPS;

    unsigned int size = calculate_size(number);

    for(unsigned int i=0; i < size;i++) {
         draw_bitmap(score->number[number % 10], x, y, get_second_buffer());
        number /= 10;
        x -= space_between_numbers;
    }
}

int process_letter()
{
    char *string1;
    string1 = malloc(11);
    strcpy(string1, name);
    if (cap <= 9)
        switch (kbc_get_data())
        {
        case A_MAKECODE:
            string1[cap] = 'A';
            break;
        case B_MAKECODE:
            string1[cap] = 'B'; 
            break;
        case C_MAKECODE:
            string1[cap] = 'C';
            break;
        case D_MAKECODE:
            string1[cap] = 'D';
            break;
        case E_MAKECODE:
            string1[cap] = 'E';           
            break;
        case F_MAKECODE:
            string1[cap] = 'F';          
            break;
        case G_MAKECODE:
            string1[cap] = 'G';           
            break;
        case H_MAKECODE:
            string1[cap] = 'H';           
            break;
        case I_MAKECODE:
            string1[cap] = 'I';            
            break;
        case J_MAKECODE:
            string1[cap] = 'J';            
            break;
        case K_MAKECODE:
            string1[cap] = 'K';            
            break;
        case L_MAKECODE:
            string1[cap] = 'L';           
            break;
        case M_MAKECODE:
            string1[cap] = 'M';            
            break;
        case N_MAKECODE:
            string1[cap] = 'N';            
            break;
        case O_MAKECODE:
            string1[cap] = 'O';            
            break;
        case P_MAKECODE:
            string1[cap] = 'P';            
            break;
        case Q_MAKECODE:
            string1[cap] = 'Q';            
            break;
        case R_MAKECODE:
            string1[cap] = 'R';           
            break;
        case S_MAKECODE:
            string1[cap] = 'S';            
            break;
        case T_MAKECODE:
            string1[cap] = 'T';            
            break;
        case U_MAKECODE:
            string1[cap] = 'U';           
            break;
        case V_MAKECODE:
            string1[cap] = 'V';
            break;
        case W_MAKECODE:
            string1[cap] = 'W';            
            break;
        case X_MAKECODE:
            string1[cap] = 'X';            
            break;
        case Y_MAKECODE:
            string1[cap] = 'Y';            
            break;
        case Z_MAKECODE:
            string1[cap] = 'Z';           
            break;
        default:
            return 0;
            break;
        }
    else {
        return 0;
    }
    strcpy(name, string1);
    free(string1);
    cap++;
    return 0;
}

void set_name(const char * new_name) {
    strcpy(name, new_name);
}

void reset_name() {
    cap = 0;
    for (int i = 0; i < 9; i++){
        name[i] = '0';
    }
    name[9] = '\0';
}

char * get_name() {
    return name;
}

unsigned int get_name_size()
{
    unsigned int index = 0;
    while (name[index] != '0')
    {
        index++;
        if (index == 9)
        {
            break;
        }
    }

    return index;
}

void draw_char(char letter, int x, int y)
{

    switch (letter)
    {
    case 'A':
        draw_bitmap(score->alphabet[0], x, y, get_second_buffer());
        break;
    case 'B':
        draw_bitmap(score->alphabet[1], x, y, get_second_buffer());
        break;
    case 'C':
        draw_bitmap(score->alphabet[2], x, y, get_second_buffer());
        break;
    case 'D':
        draw_bitmap(score->alphabet[3], x, y, get_second_buffer());
        break;
    case 'E':
        draw_bitmap(score->alphabet[4], x, y, get_second_buffer());
        break;
    case 'F':
        draw_bitmap(score->alphabet[5], x, y, get_second_buffer());
        break;
    case 'G':
        draw_bitmap(score->alphabet[6], x, y, get_second_buffer());
        break;
    case 'H':
        draw_bitmap(score->alphabet[7], x, y, get_second_buffer());
        break;
    case 'I':
        draw_bitmap(score->alphabet[8], x, y, get_second_buffer());
        break;
    case 'J':
        draw_bitmap(score->alphabet[9], x, y, get_second_buffer());
        break;
    case 'k':
        draw_bitmap(score->alphabet[10], x, y, get_second_buffer());
        break;
    case 'L':
        draw_bitmap(score->alphabet[11], x, y, get_second_buffer());
        break;
    case 'M':
        draw_bitmap(score->alphabet[12], x, y, get_second_buffer());
        break;
    case 'N':
        draw_bitmap(score->alphabet[13], x, y, get_second_buffer());
        break;
    case 'O':
        draw_bitmap(score->alphabet[14], x, y, get_second_buffer());
        break;
    case 'P':
        draw_bitmap(score->alphabet[15], x, y, get_second_buffer());
        break;
    case 'Q':
        draw_bitmap(score->alphabet[16], x, y, get_second_buffer());
        break;
    case 'R':
        draw_bitmap(score->alphabet[17], x, y, get_second_buffer());
        break;
    case 'S':
        draw_bitmap(score->alphabet[18], x, y, get_second_buffer());
        break;
    case 'T':
        draw_bitmap(score->alphabet[19], x, y, get_second_buffer());
        break;
    case 'U':
        draw_bitmap(score->alphabet[20], x, y, get_second_buffer());
        break;
    case 'V':
        draw_bitmap(score->alphabet[21], x, y, get_second_buffer());
        break;
    case 'W':
        draw_bitmap(score->alphabet[22], x, y, get_second_buffer());
        break;
    case 'X':
        draw_bitmap(score->alphabet[23], x, y, get_second_buffer());
        break;
    case 'Y':
        draw_bitmap(score->alphabet[24], x, y, get_second_buffer());
        break;
    case 'Z':
        draw_bitmap(score->alphabet[25], x, y, get_second_buffer());
        break;
    }
}

void draw_name(int x, int y)
{

    int size = get_name_size();
    unsigned int space = score->alphabet[0]->bitmapInfoHeader.width + SEPARATION_BETWEEN_BITMAPS;
     int letter =0;
    while (letter < size)
    {
        x += space;
        draw_char(name[letter], x, y);
        letter++;
    }
}

void reset_score()
{
    score_points = 0;
    atualize_score();
}

void delete_char() {
    unsigned int size = get_name_size();
    if(size > 0) {
     cap--;
     name[size-1] = '0';
    }
}


void default_name() {
    char name_default[] = {'P','L','A','Y','E','R','0','0','0','\0'};
    strcpy(name,name_default);
}


void terminate_score()
{
    for (uint8_t i = 0; i < BITMAP_NUMBER; i++)
    {
        deleteBitmap(score->number[i]);
    }
    deleteBitmap(score->bar);
    deleteBitmap(score->two_dots);

    for (uint8_t i = 0; i < NUMBER_OF_LETTERS; i++)
    {
        deleteBitmap(score->alphabet[i]);
    }

    if (score != NULL)
    {
        free(score);
    }
}

void save_leaderboard() {
    FILE *f;
    f = fopen("/home/lcom/labs/proj/src/leaderboard.txt", "w");
    uint32_t second, minute, hour, day, month, year;
 
    unsigned int loop_counter = get_game()->leaderboard_size;
    for (unsigned int i = 0; i < loop_counter; i++) {

        char * date = get_game()->leaderboard[i].date;
        sscanf(date, "%d %d %d %d %d %d", &hour, &minute, &second, &day, &month, &year);
        fprintf(f,"%d %d %d %d %d %d %d %s \n", hour, minute, second, day, month, year, get_game()->leaderboard[i].score, get_game()->leaderboard[i].name);

        free(get_game()->leaderboard[i].date); 
    }
    
    fclose(f);
}

void load_leaderboard() {
    FILE *f;
    f = fopen("/home/lcom/labs/proj/src/leaderboard.txt", "r");

    int second = 0, minute = 0, hour = 0, day = 0, month = 0, year = 0, score = 0;
    char second_str[12], minute_str[12], hour_str[12], day_str[12], month_str[12], year_str[12];

    char buffer[40];
    char name[10];
    char date[17] = "";

    
    while (fgets(buffer, 40, f) != NULL) {
    sscanf(buffer, "%d %d %d %d %d %d %d %s ", &hour, &minute, &second, &day, &month, &year, &score, name);

        sprintf(hour_str, "%d", hour);
        sprintf(minute_str, "%d", minute);
        sprintf(second_str, "%d", second);
        sprintf(day_str, "%d", day);
        sprintf(month_str,"%d", month);
        sprintf(year_str,"%d", year);

        strcat(date, hour_str);
        strcat(date, " ");
        strcat(date, minute_str);
        strcat(date, " ");
        strcat(date, second_str);
        strcat(date, " ");
        strcat(date, day_str);
        strcat(date, " ");
        strcat(date, month_str);
        strcat(date, " ");
        strcat(date, year_str);

        save_score(name, date, score);
        reset_name();
        strcpy(date, "");
      
    }


    fclose(f);
}
