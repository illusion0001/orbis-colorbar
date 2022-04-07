#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "common/graphics.h"
#include "common/log.h"

// Dimensions
#define FRAME_WIDTH     1920
#define FRAME_HEIGHT    1080
#define FRAME_DEPTH        4

// Logging
std::stringstream debugLogStream;

int frameID = 0;

int main()
{
    int rc;
    int video;
    int curFrame = 0;
    void *surfaceBuff = 0;

    // No buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    
    // Create a 2D scene
    DEBUGLOG << "Creating a scene";
    
    auto scene = new Scene2D(FRAME_WIDTH, FRAME_HEIGHT, FRAME_DEPTH);
    
    if(!scene->Init(0xC000000, 2))
    {
    	DEBUGLOG << "Failed to initialize 2D scene";
    	for(;;);
    }
   
    DEBUGLOG << "Entering draw loop...";

    // Draw loop
    for (;;)
    {
        int bar_width  =   32;
        int bar_height = 1080;
        // Color spec according to docs:
        // https://international.download.nvidia.com/geforce-com/international/pdfs/FCAT+4K_Reviewer's_Guide.pdf
        Color color0 = { 255, 255, 255 };  // 1.  White
        Color color1 = { 000, 255, 000 };  // 2.  Lime
        Color color2 = { 000, 102, 255 };  // 3.  Blue
        Color color3 = { 255, 000, 000 };  // 4.  Red
        Color color4 = { 051, 204, 204 };  // 5.  Teal
        Color color5 = { 000, 051, 204 };  // 6.  Navy
        Color color6 = { 000, 176, 000 };  // 7.  Green
        Color color7 = { 000, 255, 255 };  // 8.  Aqua
        Color color8 = { 138, 135, 000 };  // 9.  Dark Green (Dk Green)
        Color color9 = { 221, 221, 221 };  // 10. Silver
        Color color10 = { 153, 000, 204 }; // 11. Purple
        Color color11 = { 185, 172, 003 }; // 12. Olive
        Color color12 = { 119, 119, 119 }; // 13. Gray
        Color color13 = { 128, 000, 128 }; // 14. Fuchsia
        Color color14 = { 255, 255, 000 }; // 15. Yellow
        Color color15 = { 255, 153, 000 }; // 16. Orange

        const int num_colors = 16;
        Color color_array[num_colors] = { color0, color1, color2, color3, color4, color5, color6, color7,
                                          color8, color9, color10, color11, color12, color13, color14, color15 };

        for (int i = 0; i < num_colors; i++) {
            // printf("color_array[i]: %d\n", color_array[i]);
            // draw our colors
            scene->DrawRectangle(0, 0, bar_width, bar_height, color_array[i]);
            // Submit the frame buffer
            scene->SubmitFlip(frameID);
            scene->FrameWait(frameID);
            // Swap to the next buffer
            scene->FrameBufferSwap();
            frameID++;
        }
    }
    return 0;
}
