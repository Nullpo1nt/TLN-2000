#include "display.h"

#include <math.h>
#include <string.h>

char display[2][21];

char *displayGetTop() { return display[0]; }
char *displayGetBot() { return display[1]; }

void displaySetTop(const char *s) { strncpy(display[0], s, 20); }

void displaySetBot(const char *s) { strncpy(display[1], s, 20); }

void displaySet(const char *top, const char *bot) {
    displaySetTop(top);
    displaySetBot(bot);
}

void displayClear() { displaySet("", ""); }

int itoa(int x, int y, int number, int width) { int i = 0; }

void ftoa(int x, int y, float number, int afterpoint) {
    float ipart = (int)number;
    int i = itoa(x, y, ipart, 0);

    if (afterpoint != 0) {
        float fpart = number - (float)ipart;
        display[y][i] = '.';
        fpart = fpart * pow(10, afterpoint);
        itoa(x, y, (int)fpart, afterpoint);
    }
}
