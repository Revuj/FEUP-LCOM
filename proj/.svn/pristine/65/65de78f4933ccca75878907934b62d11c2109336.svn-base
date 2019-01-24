#include <lcom/lcf.h>

#include "bullet.h"
#include "video_gr.h"
#include "Colision.h"

static Gun *gun;

int initialize_gun()
{
  gun->bullet = NULL;
  gun->bullet = malloc(sizeof(bullet));
  if (gun->bullet == NULL)
  {
    return 1;
  }
  gun->bullet->next = malloc(sizeof(Bitmap));
  gun->bullet->next = NULL;

  return OK;
}

int initialize_bullets_bitmap()
{
  gun = (Gun *)malloc(sizeof(Gun *));
  for (uint8_t i = 0; i < NUMBER_OF_BULLETS; i++)
  {
    gun->bullets[i] = (Bitmap *)malloc(sizeof(Bitmap));
    gun->bullets[i] = load_bitmap_file(ASTRONAUT_BULLET_PATH);
    if (gun->bullets[i] == NULL)
    {
      return 1;
    }
  }
  gun->actual_number_of_bullets = NUMBER_OF_BULLETS;
  return OK;
}

void draw_bullets()
{
  for (uint8_t i = 0; i < NUMBER_OF_BULLETS; i++)
  {
    draw_bitmap(gun->bullets[i], 950 - i * 40, 100, get_second_buffer());
  }
}

void set_reloading()
{
  gun->reloading = true;
}

void unset_reloading()
{
  gun->reloading = false;
}

int shoot_bullet()
{
  unset_reloading();
  if (gun->actual_number_of_bullets > 0)
  {
    gun->actual_number_of_bullets--;
    return 1;
  }
  return 0;
}

void reload_bullets()
{
  static int i = 0;

  if ((gun->actual_number_of_bullets < 20) && (i % 20 == 0))
  {
    gun->actual_number_of_bullets++;
  }
  i++;
}

void update_bullets()
{
  bullet *current = gun->bullet;

  while (current->next != NULL)
  {
    if (current->next->draw)
    {
      Bitmap *shot = current->next->ptr;
      shot->x = (shot->x + shot->speed_x);
      shot->y = (shot->y + shot->speed_y);
      if (shot->x >= get_hres() || shot->x + shot->bitmapInfoHeader.width <= 0 || shot->y - shot->bitmapInfoHeader.width >= get_vres() || shot->y <= 0)
      {
        bullet *temp = current->next;
        if (temp->next == NULL)
        {
          deleteBitmap(temp->ptr);
          break;
        }
        current->next = temp->next;
        deleteBitmap(temp->ptr);
        free(temp);
      }
      else
      {
        draw_bitmap(shot, shot->x, shot->y, get_second_buffer());
        map_colision(shot, shot->x, shot->y, 100);
      }
      current = current->next;
    }
  }

  if (gun->reloading)
  {
    reload_bullets();
  }
}

void draw_reload_bullets()
{
  for (uint8_t i = 0; i < gun->actual_number_of_bullets; i++)
  {
    draw_bitmap(gun->bullets[i], 10, 700 - 20 * i, get_second_buffer());
  }
}

Bitmap *new_bullet(bullet *current, int x, int y)
{
  current->next = malloc(sizeof(bullet));
  current->next->ptr = malloc(sizeof(Bitmap));
  current->next->ptr = load_bitmap_file(BULLET);
  current->next->draw = true;
  current->next->next = NULL;

  Bitmap *bullet = current->next->ptr;

  bullet->x = x;
  bullet->y = y;
  draw_bitmap(bullet, bullet->x, bullet->y, get_second_buffer());

  return bullet;
}

Gun *get_gun()
{
  return gun;
}

void reset_bullets() {
  gun->actual_number_of_bullets = NUMBER_OF_BULLETS;

  bullet *tmp;
  while (gun->bullet != NULL)
  {
    tmp = gun->bullet;
    gun->bullet = gun->bullet->next;
    free(tmp->ptr);
    free(tmp);
  }

  initialize_gun();
}

void terminate_bullet_class()
{
  bullet *tmp;
  while (gun->bullet != NULL)
  {
    tmp = gun->bullet;
    gun->bullet = gun->bullet->next;
    free(tmp->ptr);
    free(tmp);
  }

  for (uint8_t i = 0; i < NUMBER_OF_BULLETS; i++)
  {
    deleteBitmap(gun->bullets[i]);
  }

  if (gun != NULL)
  {
    free(gun);
  }
}
