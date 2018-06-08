//.c file for all internal 'physics' functions and structs in the program
#include "PhysicsEngine.h"

// Uses 18.14 fixed-point integers

// general one-dimensional reflect function taking moving object position and
// velocity plus statical object position.
void reflect(int * pos_p, int wall, int * v_p){
    //This function assumes good input.
    //All checks must be made before calling it.

    *pos_p = (wall << 1) - *v_p - *pos_p;

    *v_p *= -1;
}

//calculates next position and velocity of the ball
void updateBall(ball_t * ball_p, frame_t * frame_p) {

    //checking for collisions for x and y separately.

    // X
    if(ball_p->xpos + ball_p->xv < frame_p->TLx) {
        reflect(&ball_p->xpos, frame_p->TLx, &ball_p->xv);
    } else if (ball_p->xpos + ball_p->xv > frame_p->BRx) {
        reflect(&ball_p->xpos, frame_p->BRx, &ball_p->xv);
    } else{
        ball_p->xpos += ball_p->xv;
    }

    // Y
    if(ball_p->ypos + ball_p->yv < frame_p -> TLy) {
        reflect(&ball_p->ypos, frame_p->TLy, &ball_p->yv);
    } else if (ball_p->ypos + ball_p->yv > frame_p -> BRy) {
        reflect(&ball_p->ypos, frame_p->BRy, &ball_p->yv);
    } else{
        ball_p->ypos += ball_p->yv;
    }
}
