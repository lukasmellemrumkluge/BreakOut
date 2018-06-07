#define ESC 0x1B

#include "stm32f30x_conf.h" // STM32 config
#include "PhysicsEngine.h"


void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
    int type = 22;             // normal text
    if (foreground > 7) {
        type = 1;                // bold text
        foreground -= 8;
    }
    printf("%c[%d;%dm", ESC, type, foreground + 30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
    printf("%c[%dm", ESC, background + 40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
    int type = 22;             // normal text
    if (foreground > 7) {
        type = 1;                // bold text
        foreground -= 8;
    }
    printf("%c[%d;%d;%dm", ESC, type, foreground + 30, background + 40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
    printf("%c[m", ESC);
}

void clrscr() {
    printf("%c[2J", ESC);
}

void clrrol() {
    printf("%c[K", ESC);
}

void gotoxy(int x, int y) {
    //printf("%c[H",ESC);
    printf("%c[%d;%df", ESC, y, x);
}

void underline(uint8_t on) {
    on ? printf("%c[4m", ESC) : printf("%c[24m", ESC);
}

void blink(uint8_t on) {
    on ? printf("%c[5m", ESC) : printf("%c[25m", ESC);
}

void inverse(uint8_t on) {
    on ? printf("%c[7m", ESC) : printf("%c[27m", ESC);
}

//Reset formatting.
void reset() {
    printf("%c[m", ESC);
}

// renders a window

void window(frame_t * frame_p, int style, char * title_p) {
    
    uint8_t db = 14; // number of decimal bits in the frame type fields
    
    //convert frame fields to uint8_t
    uint8_t TLx = (frame_p->TLx >> db);
    uint8_t TLy = (frame_p->TLy >> db);
    uint8_t BRx = (frame_p->BRx >> db);
    uint8_t BRy = (frame_p->BRy >> db);
    
    //Title_p == 0 means no title.

    //TODO : Should colors be supported?

    // Checks for bad input.
    if (TLx >= BRx) return;
    if (TLy >= BRy) return;

    //TODO : Test for <= 0 and >= terminal size.
    // Should out of range box placement be handled here as an input error, or rendered?

    uint8_t BG; // Background
    uint8_t VL; // Vertical Line
    uint8_t HL; // Horsizontal Line
    uint8_t TL; // Top Left corner
    uint8_t TR; // Top Right corner
    uint8_t BL; // Bottom Left corner
    uint8_t BR; // Bottom Right corner

    switch (style) {

        // STYLE 1
        // - Double line
        // - Title on border w. decoration
        case 1 :
            BG = 32;
            VL = 186;
            HL = 205;
            TL = 201;
            TR = 187;
            BL = 200;
            BR = 188;
            break;

            // DEFAULT STYLE
            // - single line
            // - title within border
            // Implicit style 0
        default :
            BG = 32;
            VL = 179;
            HL = 196;
            TL = 218;
            TR = 191;
            BL = 192;
            BR = 217;
    }
    /*
      RENDERING:
      Rendering happens top to bottom, line for line.
      A whole line is rendered  left-to-right, then
      gotoxy() is called to move the cursor to the
      beginning of the next line.
      The title is then rendered on top, if necessary.
    */

    //Top line
    gotoxy(TLx, TLy);
    printf("%c", TL);
    for (int i = TLx + 1; i < BRx; i++) {
        printf("%c", HL);
    }
    printf("%c", TR);

    //Middle lines
    for (int i = TLy + 1; i < BRy; i++) {
        gotoxy(TLx, i);
        printf("%c", VL);
        for (int j = TLx + 1; j < BRx; j++) {
            printf("%c", BG);
        }
        printf("%c", VL);
    }

    //Bottom line
    gotoxy(TLx, BRy);
    printf("%c", BL);
    for (int i = TLx + 1; i < BRx; i++) {
        printf("%c", HL);
    }
    printf("%c", BR);

    //Title rendering
    if (title_p != 0) {
        switch (style) {
            case 1 :
                gotoxy(TLx + 1, TLy);
                printf("%c", 185);
                printf("%s", title_p);
                printf("%c", 204);

            default :
                gotoxy(TLx + 1, TLy + 1);
                printf("%s", title_p);
        }
    }
}

// takes pointer to ball_struct and renders it according to the postion.
void renderBall(ball_t * ball_p) {
    //Rounds an 18.14 fixed point number down.
    int rendX = ball_p->xpos >> 14;
    int rendY = ball_p->ypos >> 14;
    
    gotoxy(rendX, rendY);
    printf("o");
}

void renderAll(ball_t * ball_p, frame_t * frame_p){
    //clrscr();
    // ^^ redundant, since window renders over everything as well.
    window(frame_p,0,0);
    renderBall(ball_p);
}
