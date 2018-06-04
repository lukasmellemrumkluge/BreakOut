
//int willitcollide(ball_t * ball_p, frame_t * frame_p) {
//    int collisionType = 0;
//    //checking for collisions in the order left, right, top and bottom.
//    //"if" is on purpose since multiple collions are possible.
//    // result is L=1, R=2, T=4, B=8, TL=5, TR=6, BL=9, BR=10.
//    if (ball_p->xpos + ball_p->xv < ball_p->TLx) {
//        collisionType += 1;
//    }
//    if (ball_p->xpos + ball_p->xv > ball_p->BRx) {
//        collisionType += 2;
//    }
//    if (ball_p->ypos + ball_p->yv < ball_p -> TLy {
//        collisionType += 4;
//    }
//    if (ball_p->ypos + ball_p->yv > ball_p -> BRy) {
//        collisionType += 8;
//    }
//}

void reflect(int * pos_p, int wall, int * v_p){
    // TODO : test for weird cases? Or assume good input.


    // TODO : Double check the math
    int out = *v_p + (*pos_p - wall);
    if(*v_p > 0){
        *pos_p = wall - out;
    } else{
        *pos_p = wall + out;
    }

    //Update vector
    *v_p *= -1; //TODO : Just flip the relevant bit (fixed point!?!)

}

void updatePosition(ball_t * ball_p, frame_t * frame_p) {

    //checking for collisions for x and y separately.

    // X
    int collisionType = 0;
    if(ball_p->xpos + ball_p->xv < ball_p->TLx) {
        reflect(&ball_p->xpos, ball_p->TLx, &ball_p->xv);
    } else if (ball_p->xpos + ball_p->xv > ball_p->BRx) {
        reflect(&ball_p->xpos, ball_p->BRx, &ball_p->xv);
    } else{
        ball_p->xpos += ball_p->xv;
    }

    // Y
    if(ball_p->ypos + ball_p->yv < ball_p -> TLy) {
        reflect(&ball_p->ypos, ball_p->TLy, &ball_p->yv);
    } else if (ball_p->ypos + ball_p->yv > ball_p -> BRy) {
        reflect(&ball_p->ypos, ball_p->BRy, &ball_p->yv);
    } else{
        ball_p->ypos += ball_p->yv;
    }
}
