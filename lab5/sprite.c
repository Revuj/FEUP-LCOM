#include <lcom/lcf.h>
#include "sprite.h"
#include "video.h"
#include "macros.h"

Sprite * create_sprite(const char *pic[], int x, int y, int xspeed, int yspeed) {
  //allocate space for the "object"
Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
if( sp == NULL )
return NULL;
// read the sprite pixmap
sp->map = read_xpm(pic, &(sp->width), &(sp->height));
if( sp->map == NULL ) {
free(sp);
return NULL;
}
sp->x = x;
sp->y = y;
sp->xspeed = xspeed;
sp->yspeed = yspeed;
return sp;
}

void draw_sprite(Sprite * sp) {

  unsigned int pix = 0;
  for (int y = sp->y; y < sp->y + sp->height; y++) {
    for (int x = sp->x; x < sp->x + sp->width; x++) {
      set_pixel(x, y, sp->map[pix]);
      pix++;
    }
  }
}

void destroy_sprite(Sprite *sp) {
if( sp == NULL )
return;
if( sp ->map ) {
  free(sp->map);
}
free(sp);
sp = NULL; 
}

void clear_sprite(Sprite *sp) {
  destroy_sprite(sp);

    unsigned int pix = 0;
  for (int y = sp->y; y < sp->y + sp->height; y++) {
    for (int x = sp->x; x < sp->x + sp->width; x++) {
      set_pixel(x, y, BLACK_PIXEL_COLOR);
      pix++;
    }
  }

}
