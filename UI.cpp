#include <iostream>
#include <windows.h>
#include "ui.h"
using namespace std;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBox(int x1, int y1, int x2, int y2) {
    for (int x = x1; x <= x2; x++) {
        gotoxy(x, y1); cout << char(196);
        gotoxy(x, y2); cout << char(196);
    }
    for (int y = y1; y <= y2; y++) {
        gotoxy(x1, y); cout << char(179);
        gotoxy(x2, y); cout << char(179);
    }
    gotoxy(x1, y1); cout << char(218);
    gotoxy(x2, y1); cout << char(191);
    gotoxy(x1, y2); cout << char(192);
    gotoxy(x2, y2); cout << char(217);
}

void clearArea(int x1, int y1, int x2, int y2) {
    for (int y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        for (int x = x1; x <= x2; x++) cout << ' ';
    }
}

void drawButton(int x, int y, const char* label, bool selected) {
    if (selected) textcolor(10);
    else textcolor(12);

    gotoxy(x, y);     cout << char(218);
    for (int i = 0; label[i] != '\0'; i++) cout << char(196);
    cout << char(191);

    gotoxy(x, y + 1); cout << char(179) << label << char(179);

    gotoxy(x, y + 2); cout << char(192);
    for (int i = 0; label[i] != '\0'; i++) cout << char(196);
    cout << char(217);

    textcolor(15);
}

void drawVatTuScreen() {
    drawBox(2, 2, 55, 28);
    drawBox(60, 2, 110, 14);
    drawBox(60, 16, 110, 20);
    drawBox(60, 22, 110, 30);

    gotoxy(20, 1); cout << "CAP NHAT VAT TU";
    gotoxy(78, 3); cout << "CAP NHAT VAT TU";
    gotoxy(62, 17); cout << "NOTIFICATIONS:";
    gotoxy(78, 23); cout << "GUIDES";

    drawButton(15, 32, "MENU VAT TU", true);
    drawButton(40, 32, "THEM VAT TU F2", false);
    drawButton(65, 32, "CHINH SUA VAT TU F3", false);
    drawButton(95, 32, "XOA VAT TU F4", false);
}