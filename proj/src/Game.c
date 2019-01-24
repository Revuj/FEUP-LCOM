#include <lcom/lcf.h>
#include "Game.h"

static Game *game;

Game *get_game()
{
  return game;
}

int initialize_mainmenu()
{
  game->the_menu.menu_background = (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.astro[0] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.astro[1]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.astro[2]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.play[1]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.play[0]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.scores[0]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.scores[1]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.exit_game[0]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.exit_game[1]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.title= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.gameover= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.menu[0]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.menu[1]= (Bitmap *)malloc(sizeof(Bitmap *));
  game->the_menu.background_leaderboard = (Bitmap *)malloc(sizeof(Bitmap *));

  game->the_menu.menu_background = load_bitmap_file(BACKGROUNDMENU_PATH);
  game->the_menu.astro[0]=load_bitmap_file(ASTRO_MENU1_PATH);
  game->the_menu.astro[1]=load_bitmap_file(ASTRO_MENU2_PATH);
  game->the_menu.astro[2]=load_bitmap_file(ASTRO_MENU3_PATH);
  game->the_menu.play[1]=load_bitmap_file(STARTGAME_BUTTON1_PATH);
  game->the_menu.play[0]=load_bitmap_file(STARTGAME_BUTTON2_PATH);
  game->the_menu.scores[0]=load_bitmap_file(LEADERBOARD1_PATH);
  game->the_menu.scores[1]=load_bitmap_file(LEADERBOARD2_PATH);
  game->the_menu.exit_game[0]=load_bitmap_file(EXIT_BUTTON1_PATH);
  game->the_menu.exit_game[1]=load_bitmap_file(EXIT_BUTTON2_PATH);
  game->the_menu.title=load_bitmap_file(TITLE_PATH);
  game->the_menu.gameover=load_bitmap_file(GAMEOVER_PATH);
  game->the_menu.menu[0]=load_bitmap_file(MENU_PATH);
  game->the_menu.menu[1]=load_bitmap_file(MENU_PATH2);
  game->the_menu.background_leaderboard = load_bitmap_file(LEADERBOARD_BACKGROUND_PATH);


  if (game->the_menu.menu_background == NULL || game->the_menu.astro[0] == NULL || game->the_menu.astro[1]==NULL|| game->the_menu.astro[2]==NULL || game->the_menu.play[1]==NULL 
  || game->the_menu.play[0]==NULL || game->the_menu.scores[0]==NULL || game->the_menu.scores[1] == NULL || game->the_menu.exit_game[0] == NULL || game->the_menu.exit_game[1]==NULL 
  || game->the_menu.title == NULL || game->the_menu.gameover == NULL || game->the_menu.menu[0] == NULL || game->the_menu.menu[1]==NULL ||  game->the_menu.background_leaderboard == NULL)  
  {
    return 1;
  }

  return OK;
}

int initialize_graphics_card()
{

  char *buffer;

  buffer = vg_init(0x117);
  initialize_map_colision();

  if (buffer == NULL)
  {
    return 1;
  }

  return OK;
}


int initialize_timer()
{
  if (timer_subscribe_int(&game->bit_no_selection.timer_bit_no) != OK)
  {
    return 1;
  }
  return OK;
}

int initialize_kbc()
{
  if (kbc_subscribe_int(&game->bit_no_selection.keyboard_bit_no) != OK)
  {
    return 1;
  }
  return OK;
}

int initialize_mouse()
{

  if (mouse_write_command(MOUSE_ENABLE_STREAM_MODE_COMMAND) != OK)
  {
    return 1;
  }
  if (mouse_write_command(MOUSE_ENABLE_DATA_REPORTING_COMMAND) != OK)
  {
    return 1;
  }
  if (mouse_subscribe_int(&game->bit_no_selection.mouse_bit_no) != OK)
  {
    return 1;
  }
  return OK;
}

int initialize_astronaut()
{
  game->astronaut[0] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[1] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[2] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[3] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[4] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[5] = (Bitmap *)malloc(sizeof(Bitmap *));
  game->astronaut[6] = (Bitmap *)malloc(sizeof(Bitmap *));

  game->astronaut[0] = load_bitmap_file(ASTRONAUT_PATH1);
  game->astronaut[1] = load_bitmap_file(ASTRONAUT_PATH2);
  game->astronaut[2] = load_bitmap_file(ASTRONAUT_PATH3);
  game->astronaut[3] = load_bitmap_file(ASTRONAUT_PATH4);
  game->astronaut[4] = load_bitmap_file(ASTRONAUT_PATH5);
  game->astronaut[5] = load_bitmap_file(ASTRONAUT_PATH6);
  game->astronaut[6] = load_bitmap_file(ASTRONAUT_ARM_PATH);

  for (uint8_t i = 0; i <= 6; i++)
  {
    if (game->astronaut[i] == NULL)
    {
      return 1;
    }
  }

  if (initialize_health() != OK) {
   return 1;
 }

  if(initialize_bullets_bitmap()!=OK) {
    return 1;
  }

  Bitmap *astronaut = get_game()->astronaut[0];
  astronaut->x = 500; 
  astronaut->y = 380; 
  draw_bitmap(get_game()->astronaut[6], astronaut->x + 75, astronaut->y - 85, get_second_buffer());
  draw_bitmap(astronaut, astronaut->x, astronaut->y, get_second_buffer());

  draw_health_bitmaps();

  draw_bullets();
  map_colision(astronaut, astronaut->x, astronaut->y, 1);

  return OK;
}

int initialize_background()
{
  game->background = (Bitmap *)malloc(sizeof(Bitmap *));
  game->background = load_bitmap_file(BACKGROUND_PATH);
  game->background->x = 0;
  game->background->y = get_vres() - game->background->bitmapInfoHeader.height;

  draw_bitmap(game->background, game->background->x, game->background->y, get_second_buffer());


  if (game->background == NULL)
  {
    return 1;
  }
  return 0;
}

int initialize_mouse_bitmap()
{
  game->mouse = (Bitmap *)malloc(sizeof(Bitmap *));
  game->mouse = load_bitmap_file(MOON_CURSOR_PATH);

  if (game->mouse == NULL)
  {
    return 1;
  }
  game->mouse->x = 512;
  game->mouse->y = 384;
  return 0;
}

int initialize_objects()
{

  if (initialize_background() == 1)
  {
    return 1;
  }

  if (initialize_astronaut() == 1)
  {
    return 1;
  }


  if (initialize_mouse_bitmap() == 1)
  {
    return 1;
  }

  if (initialize_satellites() == 1)
  {
    return 1;
  }

  if (initialize_asteroids() == 1)
  {
    return 1;
  }

  if (initialize_gun() == 1)
  {
    return 1;
  }



  return 0;
}

void *initialize_game()
{

  game = (Game *)malloc(sizeof(Game));

  if (initialize_mainmenu() != OK)
  {
    return NULL;
  }

  game->state = MENU;

  if (initialize_graphics_card() != OK)
  {
    return NULL;
  }

  if (initialize_timer() != OK)
  {
    return NULL;
  }


  if (initialize_mouse() != OK)
  {
    return NULL;
  }

  if (initialize_kbc() != OK)
  {
    return NULL;
  }

  if (initialize_objects() != OK)
  {
    return NULL;
  }

  game->score = (Score *)malloc(sizeof(Score *));
  game->score = initialize_score();

  game->leaderboard_size = 0;

  load_leaderboard();

  game->reading_name = false;
  game->gravity=INITIAL_GRAVITY;
  game->game_level= 1;
  game->end_game = 0;

  return game;
}

void update_astronaut_position() {
  Bitmap *astronaut = get_game()->astronaut[0];
  int astro_y = astronaut->y + astronaut->speed_y;
  int astro_x = astronaut->x + astronaut->speed_x;
  if (astro_y <= 0) {
    astro_y = 0;
  }
  else if (astro_y + astronaut->bitmapInfoHeader.height >= get_vres()) {
    astro_y = get_vres() - astronaut->bitmapInfoHeader.height;
  }
  if (astro_x <= 0) {
    astro_x = 0;
  }
  else if (astro_x + astronaut->bitmapInfoHeader.width >= get_hres()) {
    astro_x = get_hres() - astronaut->bitmapInfoHeader.width;
  }
  astronaut->x = astro_x;
  astronaut->y = astro_y;
}

void update_astronaut(int *damage)
{
  static int astronaut_no = 0;
  Bitmap *astronaut = get_game()->astronaut[astronaut_no];
  if (timer_get_counter() % 2 == 0)
  {
    if (++astronaut_no == 5)
    {
      astronaut_no = 0;
    }
  }
  Bitmap *astronaut_zero = get_game()->astronaut[0];
  update_astronaut_position();
  update_astronaut_position();

  draw_bitmap(get_game()->astronaut[6], astronaut_zero->x + 95, astronaut_zero->y + 20, get_second_buffer());
  if (*damage > 0)
  {
    if (*damage % 4 == 0 || *damage % 5 == 0)
    {
      draw_bitmap(get_game()->astronaut[5], astronaut_zero->x, astronaut_zero->y, get_second_buffer());
    }
    else
    {
      draw_bitmap(astronaut, astronaut_zero->x, astronaut_zero->y, get_second_buffer());
    }
    *damage = *damage - 1;
  }
  else
  {
    draw_bitmap(astronaut, astronaut_zero->x, astronaut_zero->y, get_second_buffer());
  }
 catch_one_life(astronaut, astronaut_zero->x, astronaut_zero->y, 1);
  
}

void update_mouse()
{
  Bitmap *mouse = get_game()->mouse;

  if (mouse->x > abs(get_hres()) && mouse->y > abs(get_vres())) {
    return;
  }
  draw_bitmap(mouse, mouse->x, mouse->y, get_second_buffer());
}

void gravity()
{
  static int counter = 0;
  if (counter % 5 == 0) { 
  Bitmap *astronaut = get_game()->astronaut[0];
  if (astronaut->y + 1 + astronaut->bitmapInfoHeader.height >= get_vres())
  {
    astronaut->y = get_vres() - astronaut->bitmapInfoHeader.height + game->gravity;
  }
  else
  {
    astronaut->y += game->gravity;
  }
  }
  counter++;
}

void explosion(asteroid * asteroid) {
  static int counter = 0;
  static int exp = 0;

  draw_bitmap(get_game()->explosion[exp], asteroid->last_x, asteroid->last_y, get_second_buffer());
  
  if (counter % 5 == 0) {
    exp++;
    if (exp == 10) {
      asteroid->exploded = false;
      exp = 0;
    }
  }
  counter++;
}

void satellite_explosion(satellite * satellite) {
  static int counter = 0;
  static int exp = 0;

  draw_bitmap(get_game()->explosion[exp], satellite->last_x, satellite->last_y, get_second_buffer());
  
  if (counter % 5 == 0) {
    exp++;
    if (exp == 10) {
      satellite->exploded = false;
      exp = 0;
    }
  }
  counter++;
}

void update_explosions() {
  for (int i = 0; i < 10; i++) {
    asteroid *asteroid = get_game()->asteroid[i];
    if (asteroid->exploded) {
      explosion(asteroid);
    }
  }

  for (int i = 0; i < 5; i++) {
  satellite * satellite = get_game()->satellite[i];
    if (satellite->exploded) {
      satellite_explosion(satellite);
    }
  }
}

void update_satellites()
{
  static int i = 0;

  if (timer_get_counter() % 240 == 0) 
  {
    random_satellite(get_game()->satellite[i % 5]);
    i++;
  }
}

void update_asteroids()
{
  static int i = 0;

  if (timer_get_counter() % 60 == 0) //este incremento tambem pode tar a gerar o crash
  {
    random_asteroid(get_game()->asteroid[i % 10]);
    i++;
  }
}

int damage_on_astronaut()
{
  for (int i = 0; i < 5; i++)
  {
    Bitmap * satellite = get_game()->satellite[i]->ptr;
    if (satellite->x != 0 || satellite->y != 0) {
      satellite->y = satellite->y + satellite->speed_y;
      satellite->x = satellite->x + satellite->speed_x;
      draw_bitmap(satellite, satellite->x, satellite->y, get_second_buffer());
      int colision = map_colision(satellite, satellite->x, satellite->y, 10 + i);
      if (colision == 1)
      {
        satellite->x = 0;
        satellite->y = 0;
        penalize_score(PENALTY);
        return 1;
      }
      else if (colision == 100)
      {
        get_game()->satellite[i]->last_x = satellite->x;
        get_game()->satellite[i]->last_y = satellite->y;
        get_game()->satellite[i]->exploded = true;
        penalize_score(PENALTY);
        satellite->x = 0;
        satellite->y = 0;
        return 0;
      }
    }
  }

  for (int j = 0; j < 10; j++)
  {
    Bitmap *asteroid = get_game()->asteroid[j]->ptr;
    if (asteroid->x != 0 || asteroid->y != 0)
    {
      asteroid->y += asteroid->speed_y ;
      asteroid->x += asteroid->speed_x;

      draw_bitmap(asteroid, asteroid->x, asteroid->y, get_second_buffer());
      int colision = map_colision(asteroid, asteroid->x, asteroid->y, 2 + j);
      if (colision == 1)
      {
        asteroid->x = 0;
        asteroid->y = 0;
        return 1;
      }
      else if (colision == 100)
      {
        get_game()->asteroid[j]->last_x = asteroid->x;
        get_game()->asteroid[j]->last_y = asteroid->y;
        get_game()->asteroid[j]->exploded = true;
        spawn_health_point(asteroid->x, asteroid->y);
        asteroid->x = 0;
        asteroid->y = 0;
        return 0;
      }
    }
  }
  return 0;
}

void update_level() {
  game->game_level += 1;
  game->gravity -= 1;
  print_level();
}

void print_level() {
  draw_bitmap(get_score_struct()->alphabet[11], 400, 300, get_second_buffer());
  draw_bitmap(get_score_struct()->alphabet[4], 424, 300, get_second_buffer());
  draw_bitmap(get_score_struct()->alphabet[21], 448, 300, get_second_buffer());
  draw_bitmap(get_score_struct()->alphabet[4], 472, 300, get_second_buffer());
  draw_bitmap(get_score_struct()->alphabet[11], 496, 300, get_second_buffer());
  draw_number(game->game_level, 544, 307);
}

void show_leaderboard() {
  unsigned int pos_x;
  unsigned int pos_y = 150;

  for(unsigned int i =0;i < 5;i++ ) {
    leaderboard lead =game->leaderboard[i];

    if(lead.score==0) {
       break;
    }
    set_name(lead.name);
    draw_bitmap(get_score_struct()->number[i+1], 50,pos_y + 5,get_second_buffer());
    draw_name(100, pos_y);
    draw_date(lead.date,450,pos_y);
    pos_x=950;
    draw_number(lead.score,pos_x,pos_y);
    pos_y += 70;
    }
}

event_type main_menu()
{ 
  static float i=0;
  paint_background(game->the_menu.menu_background);
  if(i==1000) {
    i=0;
  }

  if((uint8_t)kbc_get_data() == ESC_MAKECODE) {
    return EXIT_BUTTON;
  }

  draw_bitmap(game->the_menu.astro[(int)i%3], 20, 530, get_second_buffer());
  i+=0.1;

  int x_width_play = game->the_menu.play[0]->bitmapInfoHeader.width;
  int x_width_leaderboard = game->the_menu.scores[0]->bitmapInfoHeader.width;
  int x_width_exit = game->the_menu.exit_game[0]->bitmapInfoHeader.width;

  int y_width = game->the_menu.play[0]->bitmapInfoHeader.height;
  static int lb_pressed = 0;
  int mouse_click = !lb_pressed & get_mouse().lb;
  lb_pressed = get_mouse().lb;
  int mouse_x=game->mouse->x;
  int mouse_y=game->mouse->y;
  draw_bitmap(game->the_menu.title,265,100,get_second_buffer());
  

  if (mouse_x >= 300 && mouse_y >= 300 && mouse_x <= 300 +x_width_play && mouse_y <= 300+y_width )
  {
    draw_bitmap(game->the_menu.play[0],300,300,get_second_buffer());
    draw_bitmap(game->the_menu.scores[0],270,400,get_second_buffer());
   draw_bitmap(game->the_menu.exit_game[0],365,500,get_second_buffer());
    if(mouse_click) {
    return PLAY_BUTTON;
    }
  }
  else if (mouse_x >= 270 && mouse_y >= 400 && mouse_x <= 270 +x_width_leaderboard && mouse_y <= 400+y_width ) { 
      draw_bitmap(game->the_menu.play[1],300, 300,get_second_buffer());
      draw_bitmap(game->the_menu.scores[1],270,400,get_second_buffer());
      draw_bitmap(game->the_menu.exit_game[0],365,500,get_second_buffer());
      if(mouse_click) {
        return LEADERBOARD_BUTTON;
      }
  }
  else if(mouse_x >= 365 && mouse_y >= 500 && mouse_x <= 365 +x_width_exit && mouse_y <= 500+y_width) {
    draw_bitmap(game->the_menu.play[1],300, 300,get_second_buffer());
    draw_bitmap(game->the_menu.scores[0],270,400,get_second_buffer());
    draw_bitmap(game->the_menu.exit_game[1],365,500,get_second_buffer());
    if(mouse_click) {
      return EXIT_BUTTON;
    }
  }
  else {
  draw_bitmap(game->the_menu.play[1],300, 300,get_second_buffer());
  draw_bitmap(game->the_menu.scores[0],270,400,get_second_buffer());
  draw_bitmap(game->the_menu.exit_game[0],365,500,get_second_buffer());
  }
  
  return BACK_TO_MENU_BUTTON;

}

event_type lead_board() { 

  static int lb_pressed = 0;
  int x_width = game->the_menu.menu[0]->bitmapInfoHeader.width;
  int y_width = game->the_menu.menu[0]->bitmapInfoHeader.height;
  int mouse_x = game->mouse->x;
  int mouse_y = game->mouse->y;
  paint_background(game->the_menu.background_leaderboard);
  int clicked = (!lb_pressed &  get_mouse().lb);
  lb_pressed=get_mouse().lb;

  if (mouse_x >= 800 && mouse_x <= 800 + x_width && mouse_y >=700 && mouse_y <= 700 + y_width) {

    draw_bitmap(game->the_menu.menu[1],800,700,get_second_buffer());
    show_leaderboard();

    update_mouse();
    copy_buffer();
    clear_buffer(get_second_buffer());
    unset_clock_tick();

    if(clicked) {
      return BACK_TO_MENU_BUTTON;
    } 
    else {
      return LEADERBOARD_BUTTON;
    }

    } else {
    draw_bitmap(game->the_menu.menu[0],800,700,get_second_buffer());
    show_leaderboard();

    update_mouse();
    copy_buffer();
    clear_buffer(get_second_buffer());
    unset_clock_tick();
    return LEADERBOARD_BUTTON;
    }
}

event_type saving_score() {

  static int lb_pressed = 0;
  int x_width = game->the_menu.menu[0]->bitmapInfoHeader.width;
  int y_width = game->the_menu.menu[0]->bitmapInfoHeader.height;
  int mouse_x = game->mouse->x;
  int mouse_y = game->mouse->y;
  paint_background(game->the_menu.gameover);
  int clicked = (!lb_pressed &  get_mouse().lb);
  lb_pressed=get_mouse().lb;

  if (mouse_x >= 800 && mouse_x <= 800 + x_width && mouse_y >=700 && mouse_y <= 700 + y_width) {

    draw_bitmap(game->the_menu.menu[1],800,700,get_second_buffer());
    draw_name(GAMEOVER_X,GAMEOVER_Y);
    draw_number(get_score(),650,575);
    update_mouse();
    copy_buffer();
    clear_buffer(get_second_buffer());
    unset_clock_tick();

    if(clicked) {
      save_score(get_name(), get_date(), get_score());
      reset_name();
      reset_game();
      game->reading_name = false;
      return BACK_TO_MENU_BUTTON;
    } 
    else {
      return LOST_BUTTON;
    }

    } else {
    draw_bitmap(game->the_menu.menu[0],800,700,get_second_buffer());
    draw_name(GAMEOVER_X,GAMEOVER_Y);
    draw_number(get_score(),650,575);
    update_mouse();
    copy_buffer();
    clear_buffer(get_second_buffer());
    unset_clock_tick();
    return LOST_BUTTON;
    }
    
}

event_type update_game_state()
{
  
  static int bgy=0;
  update_background(game->background, bgy-=5);
  event_type event = PLAY_BUTTON;
  int *damage_ptr = malloc(sizeof(int));
  *damage_ptr = damage;
  update_health_point();
  update_astronaut(damage_ptr);
  damage = *damage_ptr;
  free(damage_ptr);
  update_asteroids();
  update_satellites();
  update_bullets();
  update_game_score();

    static int i=0;
    if (timer_get_counter() % UPDATE_LEVEL == 0 && get_score()!=0) {
            update_level();
            i = 0;
        }
    if(i != PRINT_LEVEL) {
      print_level();
      i++;
    }

  if (damage_on_astronaut() == 1)
  {
    damage = 20;
  
    if (lose_life() <= 0) {
      game->reading_name = true;
      event = LOST_BUTTON;
    }
  }

  update_explosions();
  update_mouse();
  draw_health_bitmaps();
  draw_reload_bullets();
  draw_date(get_date(), 325, 24);

  return event;
  
}

int process_events()
{

  switch (game->state)
  {
  case MENU:
  {
    event_type event = main_menu();
    if (event == PLAY_BUTTON)
    {
      reset_mouse(MOUSE_PATH);
      
      game->state = PLAYING;
    }
    else if (event == BACK_TO_MENU_BUTTON)
    {
      update_mouse();
      copy_buffer();
      clear_buffer(get_second_buffer());
      unset_clock_tick();
      break;
    }
    else if (event == LEADERBOARD_BUTTON) {
      game->state = LEADERBOARD;
    }
    else if (event == EXIT_BUTTON) {
      game->end_game = 1;
    }
    break;
  }
  case LEADERBOARD:
  {
    event_type event = lead_board();

    if (event == LEADERBOARD_BUTTON) {
      game->state = LEADERBOARD;
    }
    else if (event == BACK_TO_MENU_BUTTON) {
      reset_keyboard();
      game->state = MENU;
    }
     
    break;
  }
  case PLAYING:
  {

  event_type event =  update_game_state();

  if (event == PLAY_BUTTON) {
    copy_buffer();
    clear_buffer(get_second_buffer());
    clear_buffer(get_colisions_map());
    unset_clock_tick();
    game->state=PLAYING;

  }
  else if (event == LOST_BUTTON) {
    reset_mouse(MOON_CURSOR_PATH);
    game->state = SAVESCORE;
    }

    break;
  }

  case SAVESCORE: {
    event_type event = saving_score();
    if(event == LOST_BUTTON) {
      game->state = SAVESCORE;
    }
    else if (event == BACK_TO_MENU_BUTTON) {
      game->state = MENU;
    }
    break;
  }
  }
  return 0;
}


int play_game()
{

  int ipc_status, r;
  message msg;

  if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
  {
    return 0;
  }
  if (is_ipc_notify(ipc_status))
  {
    switch (_ENDPOINT_P(msg.m_source))
    {
    case HARDWARE:
      if (msg.m_notify.interrupts & BIT(game->bit_no_selection.timer_bit_no))
      {
        game_timer_ih();
      }

      if (msg.m_notify.interrupts & BIT(game->bit_no_selection.keyboard_bit_no))
      {
        game_kbc_ih();
        if (game->reading_name == true) 
        {
          if (kbc_get_data() != DELETE )
          {
             if (get_name_size() < 9) 
                process_letter();
          }
          else
          {
            delete_char();
          }
        }
      }
      else if (get_clock_tick())
      {
        gravity();
      }

      if (msg.m_notify.interrupts & BIT(game->bit_no_selection.mouse_bit_no))
      {
        game_mouse_ih();
      }
      
    }
  }
  return game->end_game;
}

void save_score(char * name, char * date, unsigned int score) {

  if(game->leaderboard_size < 5) {
    game->leaderboard_size++;
  }


  for (int i = 0; i < 5; i++) {
    if (game->leaderboard[i].score == 0) {
      if (name[0] == '0') {
        default_name();
      }
      strcpy(game->leaderboard[i].name, name);
      game->leaderboard[i].score = score;
      game->leaderboard[i].date = malloc( sizeof(char) * 17 );
      strcpy(game->leaderboard[i].date,  date);
      free(game->leaderboard[i].date);
      game->score = initialize_score();
      return;
    }
    else if (get_score() > game->leaderboard[i].score) {
      for (int j = 4; j > i; j--) {
        game->leaderboard[j] = game->leaderboard[j - 1]; 
      }
      if (name[0] == '0') {
        default_name();
      }
      strcpy(game->leaderboard[i].name, name);
      game->leaderboard[i].score = score;
      game->leaderboard[i].date = malloc( sizeof(char) * 17 );
      strcpy(game->leaderboard[i].date, date);
      game->score = initialize_score();
      return;
    }
  }
}

void reset_astronaut() {
  Bitmap *astronaut = get_game()->astronaut[0];
  astronaut->x = 500; 
  astronaut->y = 380;
  damage = 0;
  reset_bullets();
}

void reset_background() {
   game->background->x = 0;
  game->background->y = get_vres() - game->background->bitmapInfoHeader.height;


}


void reset_game() {
  game->game_level = 1;
  game->gravity = INITIAL_GRAVITY;
  reset_timer();
  reset_mouse(MOON_CURSOR_PATH);
  reset_keyboard();
  reset_background();
  reset_asteroids();
  reset_satellites();
  reset_astronaut();
  reset_score();
  reset_health();
 
}

void terminate_astronaut() {
  free(game->astronaut[0]);
  free(game->astronaut[1]);
  free(game->astronaut[2]);
  free(game->astronaut[3]);
  free(game->astronaut[4]);
  free(game->astronaut[5]);
  free(game->astronaut[6]);
}

void terminate_background() {
  free(game->background);
}

void terminate_game_score() {
  free(game->score);
}

void terminate_mouse_bitmap() {
  free(game->mouse);
}

void terminate_objects() {
  terminate_astronaut();
  terminate_asteroids();
  terminate_satellites();
  terminate_bullet_class();
  terminate_health_class();
  terminate_game_score();
  terminate_mouse_bitmap();
  terminate_map_colision();
  terminate_main_menu();
  terminate_background(); 
}

void terminate_main_menu() {
  free(game->the_menu.menu_background);
  free(game->the_menu.astro[0]);
  free(game->the_menu.astro[1]);
  free(game->the_menu.astro[2]);
  free(game->the_menu.play[1]);
  free(game->the_menu.play[0]);
  free(game->the_menu.scores[0]);
  free(game->the_menu.scores[1]);
  free(game->the_menu.exit_game[0]);
  free(game->the_menu.exit_game[1]);
  free(game->the_menu.title);
  free(game->the_menu.gameover);
  free(game->the_menu.menu[0]);
  free(game->the_menu.menu[1]);
  free(game->the_menu.background_leaderboard);

}

void terminate_game()
{
  save_leaderboard();
  terminate_objects();


  if (timer_unsubscribe_int() != OK)
  {
    return;
  }

  if (kbc_unsubscribe_int() != OK)
  {
    return;
  }

  if (mouse_unsubscribe_int() != OK)
  {
    return;
  }

  if (mouse_write_command(MOUSE_DISABLE_DATA_REPORTING_COMMAND) != OK)
  {
    return;
  }
  vg_exit();
}
