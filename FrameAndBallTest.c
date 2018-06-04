
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdio.h>
#define ESC 0x1B

typedef struct {
    int TLx;
    int TLy;
    int BRx;
    int BRy;
} frame_t;



int main(void) {
    //initialize and draw border
    frame_t border;
    border.TLx = 1;
    border.TLy = 1;
    border.BRx = 10;
    border.BRy = 10;
    window(border.TLx,border.TLy,border.BRx,border.BRy,0,0);
    //initialize ball
    ball_t ball;
    ball.xpos = 6;
    ball.ypos = 7;
    ball.xv = 1;
    ball.yv = 1;
    //begin gameplay

    int i;
    for(i = 0; i < 1000; i++) {
        updatePostion(ball, border);
        drawBall(ball);
    }
    while(1){}
}
