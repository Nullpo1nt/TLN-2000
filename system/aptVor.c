#include "aptVor.h"

#include "annunciators.h"
#include "display.h"

// APTVOR
struct APTVOR_DATA_S {
    int category;
} g_aptvor_data = {0};

void aptVorCategory() {
    // resetTimeout();

    switch (g_aptvor_data.category) {
        case 0:
            displaySet("* NEAREST AIRPORT  *", "");
            break;
        case 1:
            displaySet("* NEAREST VOR      *", "");
            break;
        case 2:
            displaySet("* NEAREST NDB      *", "");
            break;
        case 3:
            displaySet("* NEAREST INT      *", "");
            break;
        case 4:
            displaySet("* NEAREST USER INT *", "");
            break;
    }
}

void aptVorCategoryNext() {
    if (++g_aptvor_data.category > 4) {
        g_aptvor_data.category = 0;
    }

    aptVorCategory();
}

void aptVor() {
    setAptVorMode();
    displaySet("tABQa 080d 756n ARSA", "ALBUQUERQUE       NM");
}

void aptVorNext() {
    // printf("next\n");
}

void aptVorPrev() {
    // printf("prev\n");
}
