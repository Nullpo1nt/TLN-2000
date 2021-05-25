#include "display.h"

#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "annunciators.h"

// 5x7 (35-bit) pixel per character
// 2x20 (1400-bit) charaters

char display[2][31];

char *displayGetTop() {
    return display[0];
}
char *displayGetBot() {
    return display[1];
}

void displaySetTop(const char *s) {
    strcpy(display[0], s);
}

void displaySetBot(const char *s) {
    strcpy(display[1], s);
}

void displaySet(const char *top, const char *bot) {
    displaySetTop(top);
    displaySetBot(bot);
}

void display_clear() {
    memset(display[0], ' ', 20);
    memset(display[1], ' ', 20);
}

void display_write(int x, int y, const char *src, int len) {
    int srcLen = strlen(src);
    memmove(display[y] + x, src, srcLen);
    display[y][21] = 0;
}

void display_input(int x, int y, const char *src, int cursorPosition) {
    display_write(x, y, src, 0);

    if (getAnnunciatorEnt() == TLN_ANNUNCIATOR_OFF) {
        display_write(x + cursorPosition, y, " ", 0);
    }
}

int itoa(int x, int y, int number, int width) {
    int i = 0;
}

void ftoa(int x, int y, float number, int afterpoint) {
    if (x > 20 || y > 1) {
        printf("ftoa x,y: %i, %i", x, y);
        exit(1);
    }

    float ipart = (int)number;
    int i = itoa(x, y, ipart, 0);

    if (afterpoint != 0) {
        float fpart = number - (float)ipart;
        display[y][i] = '.';
        fpart = fpart * pow(10, afterpoint);
        itoa(x, y, (int)fpart, afterpoint);
    }
}
