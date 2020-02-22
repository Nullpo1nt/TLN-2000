#include "wpt.h"

namespace tln::wpt
{
// WPT
int wptCategory = 0;
int t = 0;

void wpt()
{
    annunciators::setWptMode();
    display::set("wpt", "");
}

void category()
{
    t = 0;

    switch (wptCategory)
    {
    case 0:
        display::set(
            "* AIRPORT          *", "");
        break;
    case 1:
        display::set(
            "* VOR              *", "");
        break;
    case 2:
        display::set(
            "* NDB              *", "");
        break;
    case 3:
        display::set(
            "* INT              *", "");
        break;
    case 4:
        display::set(
            "* USER INT         *", "");
        break;
    }
}

void wptCategoryNext()
{
    if (++wptCategory > 4)
    {
        wptCategory = 0;
    }

    category();
}
}