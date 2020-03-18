#ifndef _DISPLAY_H_
#define _DISPLAY_H_

void displaySet(const char *top, const char *bot);

char *displayGetTop();
char *displayGetBot();

void displaySetTop(const char *s);
void displaySetBot(const char *s);

// void write(int x, int maxLen,)
void display_write(int x, int y, const char *src, int len);
void display_input(int x, int y, const char *src, int cursorPosition);

void display_clear();

#endif