#include "Colision.h"
#include <lcom/lcf.h>

#include "video_gr.h"

static char *colision_map;

int initialize_map_colision() {
    unsigned int vram_size = get_hres() * get_vres() * (get_bbp() / 8);
    colision_map = (char *) malloc(vram_size);
     if(colision_map == NULL) {
        return 1;
  }
  memset(colision_map, 0, (get_bbp() * get_hres() * get_vres())/ 8);
  return OK;
}

int map_colision(Bitmap *bmp, int x, int y, int id)
{
  if (bmp == NULL)
    return 0;
  int width = bmp->bitmapInfoHeader.width;
  int drawWidth = width;
  int height = bmp->bitmapInfoHeader.height;
  if (x + width < 0 || x > get_hres() || y + height < 0 || y > get_vres())
    return 0;
  int xCorrection = 0;
  if (x < 0)
  {
    xCorrection = -x;
    drawWidth -= xCorrection;
    x = 0;
    if (drawWidth > get_hres())
      drawWidth = get_hres();
  }
  else if (x + drawWidth >= get_hres())
  {
    drawWidth = get_hres() - x;
  }
  char *bufferStartPos;
  unsigned char *imgStartPos;
  int i;
  for (i = 0; i < height; i++)
  {
    int pos = y + height - 1 - i;
    if (pos < 0 || pos >= get_vres())
      continue;
    bufferStartPos = get_colisions_map();
    bufferStartPos += x * 2 + pos * get_hres() * 2;
    imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;
    for (uint16_t j = 0; j < drawWidth * 2; j = j + 2)
    {
      if (*(imgStartPos + j) != 255 && *(imgStartPos + 1 + j) != 255)
      {
        if (id != 100)
        {
          if (*(bufferStartPos + j) == 1 && *(bufferStartPos + 1 + j) == 1)
          {
            return 1;
          }
          else if (*(bufferStartPos + j) == 100 && *(bufferStartPos + 1 + j) == 100)
          {
            return 100;
          }
          else if (id == 1 && (*(bufferStartPos + j) == 101 && *(bufferStartPos + 1 + j) == 101))
          {
            return 101;
          }
        }
        memset(bufferStartPos + j, id, 2);
      }
    }
  }
  return 0;
}
void clear_map_colision()
{
  memset(get_colisions_map(), 0, (get_bbp() * get_hres() * get_vres()) / 8);
}

char * get_colisions_map() {
    return colision_map;
}

void terminate_map_colision() {
    if (colision_map!=NULL) {
      free(colision_map);
    }
}


