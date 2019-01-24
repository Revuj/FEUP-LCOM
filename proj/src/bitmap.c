#include <lcom/lcf.h>
#include "bitmap.h"
#include "video_gr.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

Bitmap* load_bitmap_file(const char* filename) {
    // allocating necessary size
    Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

    // open filename in read binary mode
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, 2, 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.type != 0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    int rd;
    do {
        if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
            break;
    } while (0);

    if (rd != 1) {
        fprintf(stderr, "Error reading file\n");
        exit(-1);
    }

    // read the bitmap info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

    // move file pointer to the begining of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // allocate enough memory for the bitmap image data
    unsigned char* bitmapImage = (unsigned char*) malloc(
            bitmapInfoHeader.imageSize);

    // verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    // close file and return bitmap image data
    fclose(filePtr);

    bmp->bitmapData = bitmapImage;
    bmp->bitmapInfoHeader = bitmapInfoHeader;

    return bmp;
}

void draw_bitmap(Bitmap* bmp, int x, int y, char* buffer) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;


    if (x + width < 0 || x > get_hres() || y + height < 0
            || y > get_vres())
        return;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > get_hres())
            drawWidth = get_hres();
    } else if (x + drawWidth >= get_hres()) {
        drawWidth = get_hres() - x;
    }

    char* bufferStartPos;
    unsigned char* imgStartPos;

    int i;
    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= get_vres())
            continue;

        bufferStartPos = buffer;
        
        bufferStartPos += x * 2 + pos * get_hres() * 2;

        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

    for(uint16_t j =0; j <drawWidth*2;j=j+2) {
        if(*(imgStartPos+j)!=255 || *(imgStartPos+1+j)!=255 ) {
        memcpy(bufferStartPos+j, imgStartPos+j, 2);
        }
    }
    }
}

void clear_buffer(char * buffer) {

    memset(buffer, 0, (get_bbp() * get_hres() * get_vres())/ 8);
}

void paint_background (Bitmap * bmp){
    if(bmp==NULL) {
        return;
    }
	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;
	int drawWidth = width;

	char* bufferStartPos;
	unsigned char* imgStartPos;

	int i;
	for (i = 0; i < height; i++) {

		int pos =  height - 1 - i;

		if (pos < 0 || pos >= get_vres())
			continue;

		bufferStartPos = get_second_buffer();
		bufferStartPos +=   pos * get_hres() * 2;

        imgStartPos = bmp->bitmapData + 0 * 2 + i * width * 2;

		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
	}

}

void vertical_movement_aux(Bitmap * bmp, int y){

    if(bmp==NULL) {
        return;
    }
	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;
	int drawWidth = width;

	char* bufferStartPos;
	unsigned char* imgStartPos;

	int i;
	for (i = 0; i < height; i++) {

		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= get_vres())
			continue;

		bufferStartPos = get_second_buffer();
		bufferStartPos +=+ pos * get_hres()* 2;

		imgStartPos = bmp->bitmapData  + i * width * 2;

		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
	}

}

void update_background(Bitmap * bmp, int y){
    if(bmp== NULL) {
        return;
    }
	int new_y = y % bmp->bitmapInfoHeader.height;
	
    if (new_y < 0) {
		new_y += bmp->bitmapInfoHeader.height; 
    }

	vertical_movement_aux(bmp, -new_y);

	vertical_movement_aux(bmp,-new_y + bmp->bitmapInfoHeader.height);
}



void deleteBitmap(Bitmap* bmp) {
    if (bmp == NULL)
        return;

    free(bmp->bitmapData);
    free(bmp);
}
