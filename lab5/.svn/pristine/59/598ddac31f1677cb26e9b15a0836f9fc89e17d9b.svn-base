#include "i8042.h"
#include "lcom/lcf.h"
#include "macros.h"
#include "video.h"

static uint8_t *video_mem; /*pointer to where vram is mapped*/
uint16_t hres;
uint16_t vres;
uint8_t bbp;
uint8_t redSize;       /* size of direct color red mask in bits */
uint8_t redPosition;   /* bit position of lsb of red mask */
uint8_t greenSize;     /* size of direct color green mask in bits */
uint8_t greenPosition; /* bit position of lsb of green mask */
uint8_t blueSize;      /* size of direct color blue mask in bits */
uint8_t bluePosition;  /* bit position of lsb of blue mask */

void *(vg_init)(uint16_t mode) {

  if (lm_init(false) == NULL) {
    return NULL;
  }

  vbe_mode_info_t vmi_p;

  if (vbe_get_mode_info(mode, &vmi_p) != OK) {
    return NULL;
  }

  hres = vmi_p.XResolution;
  vres = vmi_p.YResolution;
  bbp = vmi_p.BitsPerPixel;
  redSize = vmi_p.RedMaskSize;
  redPosition = vmi_p.RedFieldPosition;
  greenSize = vmi_p.GreenMaskSize;
  greenPosition = vmi_p.GreenFieldPosition;
  blueSize = vmi_p.BlueMaskSize;
  bluePosition = vmi_p.BlueFieldPosition;

  unsigned int vram_size = hres * vres * (bbp / 8);

  int i;
  struct minix_mem_range mr;

  mr.mr_base = (phys_bytes) vmi_p.PhysBasePtr;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (i = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    return NULL;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    return NULL;
  }

  struct reg86u r;
  memset(&r, 0, sizeof(r));
  r.u.w.ax = SET_VBE_MODE;
  r.u.w.bx = mode | (1 << (14));
  r.u.b.intno = BIOS_VIDEO_SERVICE;

  if (sys_int86(&r) != OK) {
    return NULL;
  }

  if (r.u.b.al != CALL_SUPPORTED) {
    return NULL;
  }

  if (r.u.b.ah != CALL_SUCCESSED) {
    return NULL;
  }

  return video_mem;
}

void set_pixel(uint16_t x, uint16_t y, uint32_t color) {

  if (bbp <= BBP_INDEXED_COLOR_MODEL) {
    video_mem[x + hres * y] = color;
    return;
  }
  else if (bbp <= 16) {
    video_mem[x * 2 + y * hres * 2] = color;
    return;
  }
  else if (bbp <= 24) {
    video_mem[x * 3 + y * hres * 3] = color;
    return;
  }
  else if (bbp <= 32) {
    video_mem[x * 4 + y * hres * 4] = color;
    return;
  }
  else
    return;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

  if (x > hres || y > vres) {
    return NOT_OK;
  }

  uint16_t last_pixel = x + len - 1;
  for (; x <= last_pixel; x++) {
    set_pixel(x, y, color);
  }

  return OK;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  uint16_t last_line = y + height - 1;
  for (; y <= last_line; y++) {
    vg_draw_hline(x, y, width, color);
  }

  return OK;
}

void vg_draw_matrix(uint8_t no_rectangles, uint32_t first, uint8_t step) {

  uint16_t width = hres / no_rectangles;
  uint16_t height = vres / no_rectangles;

  uint8_t bits_per_pixel = bbp;
  uint32_t color = first;

  if (bits_per_pixel == BBP_INDEXED_COLOR_MODEL) {

    for (unsigned int row = 0; row < no_rectangles; row++) {
      for (unsigned int col = 0; col < no_rectangles; col++) {
        color = (first + (row * no_rectangles + col) * step) % (1 << bbp);
        vg_draw_rectangle(col * width, row * height, width, height, color);
      }
    }
  }
  else {
    uint8_t red = 0, blue = 0, green = 0;

    red = (color >> redPosition) & 0xFF;
    red = red << (8 - redSize);
    red = red >> (8 - redSize);

    blue = (color >> bluePosition) & 0xFF;
    blue = blue << (8 - blueSize);
    blue = blue >> (8 - blueSize);

    green = (color >> greenPosition) & 0xFF;
    green = green << (8 - greenSize);
    green = green >> (8 - greenSize);

    for (unsigned int row = 0; row < no_rectangles; row++) {
      for (unsigned int col = 0; col < no_rectangles; col++) {
        color = get_color_direct_mode(red, blue, green, row, col, step);
        vg_draw_rectangle(col * width, row * height, width, height, color);
      }
    }
  }
}

uint32_t get_color_direct_mode(uint8_t red, uint8_t blue, uint8_t green, uint8_t row, uint8_t col, uint8_t step) {
  uint32_t new_color;
  uint8_t red_byte, blue_byte, green_byte;

  red_byte = (red + col * step) % (1 << redSize);
  green_byte = (green + row * step) % (1 << greenSize);
  blue_byte = (blue + (col + row) * step) % (1 << blueSize);

  uint32_t red32 = (red_byte << redPosition);
  uint32_t blue32 = (blue_byte << bluePosition);
  uint32_t green32 = (green_byte << greenPosition);

  new_color = red32 | blue32 | green32;

  printf("%04X\n", new_color);

  return new_color;
}

int(video_test_controller)() {

  void *init =
    NULL;

  init = lm_init(true);

  if (init ==
      NULL) {

    return NOT_OK;
  }

  mmap_t mmap;

  if (lm_alloc(sizeof(VbeInfoBlock), &mmap) ==
      NULL) {

    return 1;
  }

  char *sig =
    "VBE2";

  memcpy(mmap.virt, sig,
         4);

  struct reg86u r;

  memset(&r,
         0, sizeof(r));

  r.u.w.ax =
    0x4F00;

  r.u.w.es =
    PB2BASE(mmap.phys);

  r.u.w.di =
    PB2OFF(mmap.phys);

  r.u.b.intno =
    0x10;

  if (sys_int86(&r) != OK) {

    return NOT_OK;
  }

  if (r.u.b.al != CALL_SUPPORTED) {

    return NOT_OK;
  }

  if (r.u.b.ah != CALL_SUCCESSED) {

    return NOT_OK;
  }

  vg_vbe_contr_info_t inf;

  VbeInfoBlock *ib = mmap.virt;

  memcpy(&inf.VBESignature, &ib->VbeSignature,
         4);

  memcpy(&inf.VBEVersion, &ib->VbeVersion,
         2);

  inf.OEMString = (char *) (((((uint32_t)(ib->OemStringPtr) & 0xFFFF0000) >> 12) + (uint32_t)((uint32_t)(ib->OemStringPtr) & 0x0000FFFF)) + (uint32_t) init);

  inf.VideoModeList = (uint16_t *) (((((uint32_t)(ib->VideoModePtr) & 0xFFFF0000) >> 12) + (uint32_t)((uint32_t)(ib->VideoModePtr) & 0x0000FFFF)) + (uint32_t) init);

  inf.TotalMemory = ib->TotalMemory *
                    64;

  inf.OEMVendorNamePtr = (char *) (((((uint32_t)(ib->OemVendorNamePtr) & 0xFFFF0000) >> 12) + (uint32_t)((uint32_t)(ib->OemVendorNamePtr) & 0x0000FFFF)) + (uint32_t) init);

  inf.OEMProductRevPtr = (char *) (((((uint32_t)(ib->OemProductRevPtr) & 0xFFFF0000) >> 12) + (uint32_t)((uint32_t)(ib->OemProductRevPtr) & 0x0000FFFF)) + (uint32_t) init);

  lm_free(&mmap);

  if (vg_display_vbe_contr_info(&inf) != OK) {

    return NOT_OK;
  }

  return OK;
}
