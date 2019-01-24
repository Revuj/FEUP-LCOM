#include "lcom/lcf.h"
#include "vbe.h"

static char *video_mem; /*pointer to where vram is mapped*/
static char *second_buffer;
static uint16_t hres;
static uint16_t vres;
static uint8_t bbp;


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

  unsigned int vram_size = hres * vres * (bbp / 8);

  struct minix_mem_range mr;

  mr.mr_base = (phys_bytes) vmi_p.PhysBasePtr;
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
    return NULL;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    return NULL;
  }

  struct reg86u r;
  memset(&r, 0, sizeof(r));
  r.u.w.ax = BIOS_VBE_SET_MODE;
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

  second_buffer = (char *) malloc(vram_size);

  
  if(second_buffer == NULL) {
    return NULL;
  }

  return video_mem;
}

uint16_t get_hres() {
  return hres;
}

uint16_t get_vres() {
  return vres;
}

uint8_t get_bbp() {
  return bbp;
}

char * get_video_mem() {
  return video_mem;
}

char * get_second_buffer() {
  return second_buffer;
}

void copy_buffer() {
  memcpy(video_mem, second_buffer, hres * vres * (bbp/8));
}




