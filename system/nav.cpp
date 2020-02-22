#include "nav.h"

namespace tln::nav
{

int navTopDisplay = 0;
int navBotDisplay = 0;

// alternate destination
bool altSet = true;

char *navGetTop()
{
    switch (navTopDisplay)
    {
    case 0:
        return "tLAXa 124d 227n 0:54";
        break;
    case 1:
        return "ETE 0:54 ETA 3:53z";
        break;
    case 2:
        return "t124d MAINTAIN ODD";
        break;
    case 3:
        return "d124d t124d FLY > 0.01n";
        break;
    case 4:
        return "[|*|*O*|*|] t124d 250k";
        break;
    case 5:
        return "MSA 53k MESA 125k";
        break;
    default:
        return "ehh?";
    }
}

char *navGetBot()
{
    switch (navBotDisplay)
    {
    case 5:
        return "tLAXa 124d 227n 0:54";
        break;
    case 3:
        return "ETE 0:54 ETA 3:53z";
        break;
    case 1:
        return "t124d MAINTAIN ODD";
        break;
    case 4:
        return "d124d t124d FLY > 0.01n";
        break;
    case 0:
        return "[|*|*O*|*|]t124d250k";
        break;
    case 2:
        return "MSA 53k MESA 125k";
        break;
    case 6:
        if (altSet)
        {
            return "tSANa 124d 292n 1:10";
            break;
        }
    default:
        return "ehh?";
    }
}

void nav()
{
    annunciators::setNavMode();
    display::set(navGetTop(), navGetBot());
}

void navReset()
{
    navTopDisplay = 0;
    navBotDisplay = 0;
    nav();
}

void navNextTop()
{
    navTopDisplay++;
    if (navTopDisplay > 5)
    {
        navTopDisplay = 0;
    }
    nav();
}

void navPrevTop()
{
    navTopDisplay--;
    if (navTopDisplay < 0)
    {
        navTopDisplay = 5;
    }
    nav();
}

void navNextBot()
{
    navBotDisplay++;
    if ((altSet && navBotDisplay > 6) || (!altSet && navBotDisplay > 5))
    {
        navBotDisplay = 0;
    }
    nav();
}

void navPrevBot()
{
    navBotDisplay--;
    if (navBotDisplay < 0)
    {
        if (altSet)
        {
            navBotDisplay = 6;
        }
        else
        {
            navBotDisplay = 5;
        }
    }
    nav();
}

void navDes()
{
    display::set("tLAXa 125d 197n 0:47", "LOS ANGELES       CA");
}

} // namespace tln::nav