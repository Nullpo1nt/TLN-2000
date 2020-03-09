#include "wpt.h"

#include "annunciators.h"
#include "display.h"

// WPT
struct WPT_DATA_S {
    int wptCategory;
    int t;
} g_wpt_data = {0, 0};

void wpt() {
    setWptMode();
    displaySet("wpt", "");
}

void category() {
    g_wpt_data.t = 0;

    switch (g_wpt_data.wptCategory) {
        case 0:
            displaySet("* AIRPORT          *", "");
            break;
        case 1:
            displaySet("* VOR              *", "");
            break;
        case 2:
            displaySet("* NDB              *", "");
            break;
        case 3:
            displaySet("* INT              *", "");
            break;
        case 4:
            displaySet("* USER INT         *", "");
            break;
    }
}

void wptCategoryNext() {
    if (++g_wpt_data.wptCategory > 4) {
        g_wpt_data.wptCategory = 0;
    }

    category();
}
