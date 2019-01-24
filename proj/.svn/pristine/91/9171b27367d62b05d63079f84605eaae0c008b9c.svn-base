#include <lcom/lcf.h>
#include "asteroid.h"
#include "video_gr.h"
#include "Game.h"

int initialize_asteroids()
{
  get_game()->explosion[0] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[1] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[2] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[3] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[4] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[5] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[6] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[7] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[8] = (Bitmap *)malloc(sizeof(Bitmap *));
  get_game()->explosion[9] = (Bitmap *)malloc(sizeof(Bitmap *));

  get_game()->explosion[0] = load_bitmap_file(EXPLOSION1);
  get_game()->explosion[1] = load_bitmap_file(EXPLOSION2);
  get_game()->explosion[2] = load_bitmap_file(EXPLOSION3);
  get_game()->explosion[3] = load_bitmap_file(EXPLOSION4);
  get_game()->explosion[4] = load_bitmap_file(EXPLOSION5);
  get_game()->explosion[5] = load_bitmap_file(EXPLOSION6);
  get_game()->explosion[6] = load_bitmap_file(EXPLOSION7);
  get_game()->explosion[7] = load_bitmap_file(EXPLOSION8);
  get_game()->explosion[8] = load_bitmap_file(EXPLOSION9);
  get_game()->explosion[9] = load_bitmap_file(EXPLOSION10);

  for (int i = 0; i < ASTEROIDS_NUMBER; i++)
  {
    get_game()->asteroid[i] = malloc(sizeof(asteroid));
    get_game()->asteroid[i]->ptr = malloc(sizeof(Bitmap *));
    get_game()->asteroid[i]->ptr = load_bitmap_file(ASTEROID1);

    if (get_game()->asteroid[i]->ptr == NULL)
    {
      return 1;
    }
    Bitmap *asteroid = get_game()->asteroid[i]->ptr;
    asteroid->x = 0;
    asteroid->y = 0;
  }

  return 0;
}

void random_asteroid(asteroid * rock) {
   int random = rand() % 4;
   
   switch(random) {
      case 1: {
         rock->initial_x= rand()%get_hres();
         rock->initial_y= -100;
         if (rand() % 1 == 0) {
           rock->ptr->speed_x = 0;
         }
         else if (random > 1) {
            rock->ptr->speed_x = random + 1 * 2;
         }
         else {
            rock->ptr->speed_x = -(random + 1 * 2);
         }
         rock->ptr->speed_y = random + 1 * 2;
         break;
      }
      case 3: {
         rock->initial_x= get_hres() + 100;
         rock->initial_y= rand()%get_vres();
         if (rand() % 1 == 0) {
           rock->ptr->speed_y = 0;
         }
         else if (random > 1) {
            rock->ptr->speed_y = random + 1 * 2;
         }
         else {
            rock->ptr->speed_y = -(random + 1 * 2);
         }
         rock->ptr->speed_x = -(random + 1 * 2);         
         break;
      }
      case 4: {
         rock->initial_x= rand()%get_hres();
         rock->initial_y= get_vres() + 100;
         if (rand() % 2 == 0) {
           rock->ptr->speed_x = 0;
         }
         else if (random > 1) {
            rock->ptr->speed_x = random + 1 * 2;
         }
         else {
            rock->ptr->speed_x = -(random + 1 * 2);
         }
         rock->ptr->speed_y = -(random + 1 * 2);
         break;
      }
      case 2: {
         rock->initial_x= -100;
         rock->initial_y= rand()%get_vres();
         if (random % 2 == 0) {
          rock->ptr->speed_y = 0;
         }
        else if (rand() % 2 > 1) {
            rock->ptr->speed_y = random + 1 * 2;
         }
         else {
            rock->ptr->speed_y = -(random + 1 * 2);
         }
         rock->ptr->speed_x = random + 1 * 2;
         break;
      }
   }
   rock->ptr->x = rock->initial_x;
   rock->ptr->y = rock->initial_y;
}


void reset_asteroids() {
  for (int i = 0; i < 10; i++) {
    Bitmap *asteroid = get_game()->asteroid[i]->ptr;
    asteroid->x = 0;
    asteroid->y = 0;
  }
}

void terminate_asteroids() {
   
   free(get_game()->explosion[0]);
   free(get_game()->explosion[1]);
   free(get_game()->explosion[2]);
   free(get_game()->explosion[3]);
   free(get_game()->explosion[4]);
   free(get_game()->explosion[5]);
   free(get_game()->explosion[6]);
   free(get_game()->explosion[7]);
   free(get_game()->explosion[8]);
   free(get_game()->explosion[9]);
   
   for (int i = 0; i < ASTEROIDS_NUMBER; i++) {
   free(get_game()->asteroid[i]->ptr);
   free(get_game()->asteroid[i]);
  }

}
