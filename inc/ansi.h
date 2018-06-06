

#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void clrscr();
void clrrol();
void gotoxy(int x, int y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void reset();
void window(frame_t * frame_p, int style, char * title);
void renderBall(ball_t * ball_p);
void renderAll(ball_t * ball_p, frame_t * frame_p);

#endif /* _ANSI_H_ */
