#ifndef UI_H
#define UI_H

void gotoxy(int x, int y);
void textcolor(int color);
void drawBox(int x1, int y1, int x2, int y2);
void clearArea(int x1, int y1, int x2, int y2);
void drawButton(int x, int y, const char* label, bool selected);
void drawVatTuScreen();

#endif