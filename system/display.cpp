#include "display.h"

namespace tln::display
{

char top[21];
char bot[21];

char *getTop()
{
    return top;
}
char *getBot()
{
    return bot;
}

void setTop(const char *s)
{
    strncpy(top, s, 20);
}

void setBot(const char *s)
{
    strncpy(bot, s, 20);
}

void set(char *top, char *bot)
{
    setTop(top);
    setBot(bot);
}

void clear()
{
    set("", "");
}

} // namespace tln::display