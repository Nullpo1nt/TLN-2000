#include "aptVor.h"

namespace tln::aptvor
{

// APTVOR
int category = 0;

void aptVorCategory()
{
    // resetTimeout();

    switch (category)
    {
    case 0:
        display::set(
            "* NEAREST AIRPORT  *", "");
        break;
    case 1:
        display::set(
            "* NEAREST VOR      *", "");
        break;
    case 2:
        display::set(
            "* NEAREST NDB      *", "");
        break;
    case 3:
        display::set(
            "* NEAREST INT      *", "");
        break;
    case 4:
        display::set(
            "* NEAREST USER INT *", "");
        break;
    }
}

void aptVorCategoryNext()
{
    if (++category > 4)
    {
        category = 0;
    }

    aptVorCategory();
}

void aptVor()
{
    annunciators::setAptVorMode();
    display::set("tABQa 080d 756n ARSA", "ALBUQUERQUE       NM");
}

void aptVorNext()
{
    //printf("next\n");
}

void aptVorPrev()
{
    //printf("prev\n");
}

} // namespace tln::aptvor