
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "PhysicsEngine.h" // Internal physics utilities
#include "ansi.h" // Terminal Graphixxx
#include <stdio.h>  //I/O functions of C
#define ESC 0x1B //define escape

int main(void) {
    //initialize border
    frame_t border;
    border.TLx = 1;
    border.TLy = 1;
    border.BRx = 10;
    border.BRy = 10;
    
    //initialize ball
    ball_t ball;
    ball.xpos = 6;
    ball.ypos = 7;
    ball.xv = 1;
    ball.yv = 1;
    
    //render first frame
    renderAll(ball * ball_p, frame_p * frame_t);
    
    //begin gameplay
    int i;
    for(i = 0; i < 100; i++) {
        updatePostion(ball, border);
        renderAll(ball * ball_p, frame_p * frame_t);
    }
    while(1){}
}
