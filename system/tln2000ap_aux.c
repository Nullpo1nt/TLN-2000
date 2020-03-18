#include "tln2000ap_aux.h"

#include <stdbool.h>

#include "annunciators.h"
#include "display.h"

int auxPage = 0;
bool demoMode = false;

void auxMode() {
    setAuxMode();
    display_clear();
}