
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

int updatePostion(ball_t * ball_p, frame_t * frame_p) {
    //checking for collisions in the order left, right, top and bottom.
    //"if" is on purpose since multiple collions are possible.
    // result is L=1, R=2, T=4, B=8, TL=5, TR=6, BL=9, BR=10.
    int collisionType = 0;
    if (ball_p->xpos + ball_p->xv < ball_p->TLx) {
        collisionType += 1;
    }
    if (ball_p->xpos + ball_p->xv > ball_p->BRx) {
        collisionType += 2;
    }
    if (ball_p->ypos + ball_p->yv < ball_p -> TLy {
        collisionType += 4;
    }
    if (ball_p->ypos + ball_p->yv > ball_p -> BRy) {
        collisionType += 8;
    }

    //updating position
    switch (type) {
    case 0 :
        ball_p->xpos += ball_p->xv;
        ball_p->ypos += ball_p->yv;
    //side collisions
    case 1 :
        ball_p->xpos = 2*frame_p->TLx - ball_p->xv - ball_p->xpos;
        ball_p->ypos = ball_p->ypos + ball_p->yv;
        break;
    case 2 :
        ball_p->xpos = 2*frame_p->BRx - ball_p->xv - ball_p->xpos;
        ball_p->ypos = ball_p->ypos + ball_p->yv;
        break;
    case 4 :
        ball_p->xpos = ball_p->xpos + ball_p->xv;
        ball_p->ypos = 2 * frame_p -> TLy - ball_p->yv - ball_p->ypos;
        break;
    case 8 :
        ball_p->xpos = ball_p->xpos + ball_p->xv;
        ball_p->ypos = 2 * frame_p -> BRy - ball_p->yv - ball_p->ypos;
        break;
    //corner collisions
    case 5 :
        ball_p->xpos = 2*frame_p->TLx - xv - xpos;
        ball_p->ypos = 2*frame_p->TLy - yv - ypos;
        break;
    case 6 :
        ball_p->xpos = 2*frame_p->BRx - ball_p->xv - ball_p->xpos;
        ball_p->ypos = 2*frame_p->TLy - ball_p->yv - ball_p->ypos;
        break;
    case 9 :
        ball_p->xpos = 2*frame_p->TLx - ball_p->xv - ball_p->xpos;
        ball_p->ypos = 2*frame_p->BRy - ball_p->yv - ball_p->ypos;
        break;
    case 10 :
        ball_p->xpos = 2*frame_p->BRx - ball_p->xv - ball_p->xpos;
        ball_p->ypos = 2*frame_p->BRy - ball_p->yv - ball_p->ypos;
        break;
    }
}
