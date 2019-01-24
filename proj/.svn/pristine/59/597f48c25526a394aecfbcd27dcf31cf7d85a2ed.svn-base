#include "health.h"
#include <lcom/lcf.h>
#include "Colision.h"
#include "video_gr.h"

static health_point * health;

int initialize_health_bitmaps() {
    for(uint8_t i = 0; i < NUMBER_OF_LIFES; i++) {
         health->life[i]=(Bitmap *)malloc(sizeof(Bitmap *));
         health->life[i] = load_bitmap_file(ASTRONAUT_LIFE_PATH);
         if (health->life[i] == NULL)  {
             return 1;
       }   
    }
    return OK;
}

int initialize_health() {
  health= (health_point * )malloc(sizeof(health_point*));
   if(initialize_health_bitmaps()!= OK) {
      return 1;
  }

  health->ptr = malloc(sizeof(Bitmap *));
  health->ptr = load_bitmap_file(ASTRONAUT_LIFE_PATH);
  health->draw = false;
  health->actual_number_of_lifes=NUMBER_OF_LIFES;

  if (health->ptr == NULL) {
    return 1;
  }

    return OK;
}

void draw_health_bitmaps() {
    for (uint8_t i = 0; i < health->actual_number_of_lifes; i++) {
         draw_bitmap(health->life[i], 950 - i * 40, 700, get_second_buffer());
    }
}

void catch_one_life(Bitmap * bmp, int x, int y, int id) {
    if (map_colision(bmp, x,y, id) == HEALTH_ID) {
    health->draw = false;
    if (health->actual_number_of_lifes < NUMBER_OF_LIFES) {
      health->actual_number_of_lifes++;
    }
  }
}

void spawn_health_point(int x, int y) {

  int random = rand() % 10;

  if (random % 7 == 0) {
  health->draw = true;
  health->ptr->x = x;
  health->ptr->y = y;
  draw_bitmap(health->ptr, x, y, get_second_buffer());
  map_colision(health->ptr, x, y, HEALTH_ID);
  }
}

void update_health_point() {
  Bitmap * health_bitmap = health->ptr;
  if (health->draw) {
    health_bitmap->y += 1;
    if (health_bitmap->y >= get_vres()) {
      health->draw = false;
    }
    else {
      draw_bitmap(health_bitmap, health_bitmap->x, health_bitmap->y, get_second_buffer());
      map_colision(health_bitmap, health_bitmap->x, health_bitmap->y, HEALTH_ID);
    }
  }
}

int lose_life() {
    health->actual_number_of_lifes--;
    return health->actual_number_of_lifes;
}

void set_full_health() {
  health->actual_number_of_lifes = 5;
}

void reset_health() {
  set_full_health();
}

void terminate_health_class() {
    if(health->ptr !=NULL) {
        free(health->ptr);
    }
     for (uint8_t i = 0; i < NUMBER_OF_LIFES; i++) {
        deleteBitmap(health->life[i]);
    }
    if(health!= NULL) {
        free(health);
    }
}
