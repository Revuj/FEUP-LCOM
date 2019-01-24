#ifndef _BITMAP_H_
#define _BITMAP_H_

/* --------------------------------------------------------------------------------------------------------------------------------------------
    A large portion of this code was not written by us, but instead was a given of Henrique Ferrolho whose blog you can check here.
    http://difusal.blogspot.pt/2014/09/minixtutorial-8-loading-bmp-images.html.
 --------------------------------------------------------------------------------------------------------------------------------------------*/

#define BACKGROUND_COLOR 0x0000   // Black color is transparent!



/** @defgroup Bitmap Bitmap
 * @{
 * Functions to manipulate bitmaps
 */

typedef enum {
    ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT
} Alignment;

/** @name BitmapFileHeader */
/**@{struct that holds the information about a bitmap file*/
typedef struct {
    unsigned short type; /** < @brief specifies the file type*/
    unsigned int size; /** < @brief specifies the size in bytes of the bitmap file*/
    unsigned int reserved; /** < @brief reserved; must be 0*/
    unsigned int offset; /** < @brief specifies the offset in bytes from the bitmapfileheader to the bitmap bits*/
} BitmapFileHeader;/** @} end of the BitmapFIleHeader struct*/

/** @name BitmapInfoHeader */
/** @{struct that holds more especific information about the bitmap */
typedef struct {
    unsigned int size; /**< @brief specifies the number of bytes required by the struct*/
    int width; /**< @brief specifies width in pixels*/
    int height; /**< @brief specifies height in pixels*/
    unsigned short planes; /**< @brief specifies the number of color planes, must be 1*/
    unsigned short bits; /**< @brief specifies the number of bit per pixel*/
    unsigned int compression; /**< @brief specifies the type of compression*/
    unsigned int imageSize; /**< @brief size of image in bytes*/
    int xResolution; /**< @brief number of pixels per meter in x axis*/
    int yResolution; /**< @brief number of pixels per meter in y axis*/
    unsigned int nColors; /**< @brief number of colors used by the bitmap*/
    unsigned int importantColors; /**< @brief number of colors that are important*/
} BitmapInfoHeader; /** @} end of the BitmapInfoHeader struct*/

/** @name Bitmap */
/**@{struct that holds the information about a bitmap */
typedef struct {
    BitmapInfoHeader bitmapInfoHeader; /**< @brief bitmapInfoHeader of the bitmap*/
    unsigned char* bitmapData; /**< @brief bitmapData of the bitmap*/
    int x; /**< @brief bitmap x*/
    int y;  /**< @brief bitmap y*/
    int speed_x; /**< @brief bitmap speed on x axis*/
    int speed_y; /**< @brief bitmap speed on y axis*/
} Bitmap; /** @} end of the Bitmap struct*/


/**
 * @brief Loads a bmp image
 *
 * @param filename - Path of the image to load
 * 
 * @return Non NULL pointer to the image buffer
 */
Bitmap* load_bitmap_file(const char* filename);

/**
 * @brief Draws an unscaled, unrotated bitmap at the given position
 *
 * @param bitmap - bitmap to be drawn
 * @param x - destiny x coord
 * @param y - destiny y coord
 * @param buffer - buffer to draw in
 */
void draw_bitmap(Bitmap* bitmap, int x, int y, char* buffer);


/**
 * @brief Clear the memory of the buffer, setting everything to 0
 * 
 * @param buffer - buffer to be cleared
 */ 
void clear_buffer(char * buffer);


/**
 * @brief draws background image in the position (0,0)
 *
 * @param bmp - bitmap to be drawn
 */
void paint_background(Bitmap * bmp);

/**
 * @brief moves a bitmap vertically
 * 
 * @param bmp - bitmap to be moved
 * @param y - y position
 */ 
void vertical_movement_aux(Bitmap * bmp, int y);

/**
 * @brief updates the position of the background
 * 
 * @param bmp - background's bitmap
 * @param y - y position
 */
void update_background(Bitmap * bmp, int y);


/**
 * @brief Destroys the given bitmap, freeing all resources used by it.
 *
 * @param bitmap bitmap to be destroyed
 */
void deleteBitmap(Bitmap* bmp);

 /** @} end of Bitmap */

#endif /* _BITMAP_H_ */
