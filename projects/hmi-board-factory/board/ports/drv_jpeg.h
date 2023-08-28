#ifndef __DRVJPEG_H__
#define __DRVJPEG_H__

#include <rtthread.h>
#include "hal_data.h"

#define DCODE_BUFFER_SIZE           (30 * 1024)
#define JPEG_TIMEOUT                (100)

typedef struct _decode_drv_t
{
    void *jpeg_out_buf;
    void (*decode_read)(int32_t x, int32_t y, const void *pInBuffer, int32_t xSize, int32_t ySize);
}decode_drv_t;

int JPEG_X_Draw(void *p, int x0, int y0);
void _DrawBitmap(int32_t x, int32_t y, void const *p, int32_t xSize, int32_t ySize);

void LCDCONF_DrawJPEG(int32_t      x,
                      int32_t      y,
                      const void *p,
                      int32_t      xSize,
                      int32_t      ySize);
#endif
