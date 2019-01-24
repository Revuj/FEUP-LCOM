#include <lcom/lcf.h>

  void vg_draw_matrix(uint8_t no_rectangles,
                      uint32_t first,
                      uint8_t step);

uint8_t set_mask(uint8_t component);

void set_pixel(uint16_t x,
               uint16_t y, uint32_t color);

uint32_t get_color_direct_mode(uint8_t red, uint8_t blue, uint8_t green, uint8_t row, uint8_t col, uint8_t step);

typedef struct
  __attribute__((packed)) {

  char VbeSignature[4];

  uint16_t VbeVersion;

  uint32_t OemStringPtr;

  uint32_t Capabilities;

  uint32_t VideoModePtr;

  uint16_t TotalMemory;

  uint16_t OemSoftwareRev;

  uint32_t OemVendorNamePtr;

  uint32_t OemProductNamePtr;

  uint32_t OemProductRevPtr;

  uint8_t Reserved[222];

  uint8_t OemData[256];

} VbeInfoBlock;
