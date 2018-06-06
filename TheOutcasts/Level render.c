/*
 *
 * PUT THIS INTO BALL
 *
 *
 */

void render(/* ... */){

// TODO : hits behavior
int hits = 0; // < 100

int hx = sizeX >> 1; // half x
int hy = sizeY >> 1; // half y

char[] hitCnt = "Hits:   ";
hitCnt[6] = (hits/10) + '0';
hitCnt[7] = (hits%10) + '0';

clrscr();

// Frame:
window(1, 1, sizeX, sizeY, 1, 0);

// Hit count window
window((hx-5), (hy-1), (hx+5), (hy+1), 0, &hitCnt);
// Size: 11x3
// ┌---------┐
// |Hits: xx |
// └---------┘

// Render ball
// 18.14 fixed point, rounded down.
int rendX = posX >> 14;
int rendY = posY >> 14;
gotoxy(rendX, rendY);
printf("o");
}

/* 
 * Vinduer tegnes fra (1,1) til (sizeX,sizeY)
 * Koordinater rundes ned ved rendering
 * Koordinat 1 er venstre side af venstre væg
 *  - Ergo er 2 højre side
 * sizeX er venstre side af højre væg
 * Tilsvarende for y-aksen
*/
