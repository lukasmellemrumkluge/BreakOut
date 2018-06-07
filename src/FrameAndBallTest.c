
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "PhysicsEngine.h" // Internal physics utilities
#include "ansi.h" // Terminal Graphixxx
#include <stdio.h>  //I/O functions of C
#define ESC 0x1B //define escape

int main(void) {
    //initialize border
    frame_t border;
    border.TLx = (1 << 14);
    border.TLy = (1 << 14);
    border.BRx = (10 << 14);
    border.BRy = (10 << 14);

    //initialize ball
    ball_t ball;
    ball.xpos = (6 << 14);
    ball.ypos = (7 << 14);
    ball.xv = (1 << 14);
    ball.yv = (1 << 14);

    int n;

    init_usb_uart( 115200 );
    //render first frame
    hideCursor();
    renderAll(&ball, &border);

    //begin gameplay
    while(1) {
        if (n > 100000) {
            updateBall(&ball, &border);
            renderAll(&ball, &border);
            n = 0;
        }
        else {
           n++;
        }
    }
    while(1){}
}
