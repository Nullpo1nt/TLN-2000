#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <string.h>

namespace tln::display
{

void set(char *top, char *bot);

char *getTop();
char *getBot();

void setTop(const char *s);
void setBot(const char *s);

// void write(int x, int maxLen,)

void clear();

} // namespace tln::display

#endif