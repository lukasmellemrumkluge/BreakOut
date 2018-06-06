//.c file for all internal 'physics' functions and structs in the program
#include "PhysicsEngine.h"


//ball struct containing postion and velocity
//typedef struct {
//    int xpos;
//    int ypos;
//    int xv;
//    int yv;
//} ball_t;



// general one-dimensional reflect function taking moving object position and
// velocity plus statical object position.
void reflect(int * pos_p, int wall, int * v_p){
    //This function assumes good input.
    //All checks must be made before calling it.

    // TODO : Double check the math

    int out = *v_p + (*pos_p - wall);
    if(*v_p > 0){
        *pos_p = wall - out;
    } else{
        *pos_p = wall + out;
    }

    //Update vector
    *v_p *= -1;
    //TODO : Just flip the relevant bit (fixed point!?!)

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
