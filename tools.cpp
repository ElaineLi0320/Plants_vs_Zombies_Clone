#include "tools.h"

// Draw a PNG image while handling transparency
void _putimagePNG(int picture_x, int picture_y, IMAGE* picture) // picture_x is the X-coordinate where the image will be drawn, picture_y is the Y-coordinate
{
    DWORD* dst = GetImageBuffer();      // Retrieve pointer to the device's image buffer (provided by EasyX)
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); // Get pointer to the source image buffer
    int picture_width = picture->getwidth(); // Get width of the source image (EasyX provided)
    int picture_height = picture->getheight(); // Get height of the source image (EasyX provided)
    int graphWidth = getwidth();        // Get width of the target drawing area (EasyX provided)
    int graphHeight = getheight();      // Get height of the target drawing area (EasyX provided)
    int dstX = 0;    // Index for destination image buffer

    // Implement transparency blending: Cp = αp * FP + (1 - αp) * BP
    // This follows the Porter-Duff compositing rules for alpha blending
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; // Index for source image buffer
            int sa = ((src[srcX] & 0xff000000) >> 24); // Extract alpha channel (transparency)
            int sr = ((src[srcX] & 0xff0000) >> 16);   // Extract red component
            int sg = ((src[srcX] & 0xff00) >> 8);      // Extract green component
            int sb = src[srcX] & 0xff;                 // Extract blue component
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; // Index for destination image buffer
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
                    | (sb * sa / 255 + db * (255 - sa) / 255);
            }
        }
    }
}

// Draw PNG while handling cases where y < 0 or x < 0
void putimagePNG(int x, int y, IMAGE* picture) {

    IMAGE imgTmp, imgTmp2, imgTmp3;
    int winWidth = getwidth();
    int winHeight = getheight();
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }
    else if (y >= getheight() || x >= getwidth()) {
        return;
    }
    else if (y + picture->getheight() > winHeight) {
        SetWorkingImage(picture);
        getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
        SetWorkingImage();
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp2;
    }

    if (x > winWidth - picture->getwidth()) {
        SetWorkingImage(picture);
        getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
        SetWorkingImage();
        picture = &imgTmp3;
    }

    _putimagePNG(x, y, picture);
}

int getDelay() {
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount();
    if (lastTime == 0) {
        lastTime = currentTime;
        return 0;
    }
    else {
        int ret = currentTime - lastTime;
        lastTime = currentTime;
        return ret;
    }
}
