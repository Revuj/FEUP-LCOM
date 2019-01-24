#include <lcom/lcf.h>
#include "satellite.h"
#include "video_gr.h"
#include "Game.h"

int initialize_satellites()
{

  for (int i = 0; i < SATELLITES_NUMBER; i++)
  {
    get_game()->satellite[i] = malloc(sizeof(satellite));
    get_game()->satellite[i]->ptr = malloc(sizeof(Bitmap *));
    get_game()->satellite[i]->ptr = load_bitmap_file(SATELLITE);

    if (get_game()->satellite[i]->ptr == NULL)
    {
      return 1;
    }
    Bitmap *satellite = get_game()->satellite[i]->ptr;
    satellite->x = 0;
    satellite->y = 0;
  }

  return 0;
}

void random_satellite(satellite * sat) {

   int random = rand() % 4;
   
   switch(random) {
      case 0: {
         sat->initial_x= rand()%get_hres();
         sat->initial_y= -100;
         if (random > 1) {
            sat->ptr->speed_x = random + 1 * 2;
         }
         else {
            sat->ptr->speed_x = -(random + 1 * 2);
         }
         sat->ptr->speed_y = random + 1 * 2;
         break;
      }
      case 1: {
         sat->initial_x= get_hres() + 100;
         sat->initial_y= rand()%get_vres();
         if (random > 1) {
            sat->ptr->speed_y = random + 1 * 2;
         }
         else {
            sat->ptr->speed_y = -(random + 1 * 2);
         }
         sat->ptr->speed_x = -(random + 1 * 2);         
         break;
      }
      case 2: {
         sat->initial_x= rand()%get_hres();
         sat->initial_y= get_vres() + 100;
         if (random > 1) {
            sat->ptr->speed_x = random + 1 * 2;
         }
         else {
            sat->ptr->speed_x = -(random + 1 * 2);
         }
         sat->ptr->speed_y = -(random + 1 * 2);
         break;
      }
      case 3: {
         sat->initial_x= -100;
         sat->initial_y= rand()%get_vres();
         if (random > 1) {
            sat->ptr->speed_y = random + 1 * 2;
         }
         else {
            sat->ptr->speed_y = -(random + 1 * 2);
         }
         sat->ptr->speed_x = random + 1 * 2;
         break;
      }
   }
   sat->ptr->x = sat->initial_x;
   sat->ptr->y = sat->initial_y;
}

void reset_satellites() {
   for (int i = 0; i < SATELLITES_NUMBER; i++) {
      Bitmap *satellite = get_game()->satellite[i]->ptr;
      satellite->x = 0;
      satellite->y = 0;
   }
}


void terminate_satellites() {
   
   for (int i = 0; i < SATELLITES_NUMBER; i++) {
   free(get_game()->satellite[i]->ptr);
   free(get_game()->satellite[i]);
  }

}
