#include "tln2000.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "annunciators.h"
#include "aptVor.h"
#include "calc.h"
#include "display.h"
#include "nav.h"
#include "wpt.h"

struct TLN_DATA_S {
    LLPoint currentPosition;
    tln_waypoint current;
    float fuel;
    bool fedit;
    int i;
    int selfTestState;
};

struct TLN_DATA_S g_tln2000_data = {.currentPosition = {42.3629444, -71.0063889},
                                    .current = {AIRPORT, {33.9424964, -118.4080486}, "KLAX", "Los Angelos"},
                                    .fuel = 123.4,
                                    .fedit = false,
                                    .i = 0,
                                    .selfTestState = 0};

// Current state
TLN_STATE currentState = TLN_STATE_OFF;

void selfTestStart() {
    g_tln2000_data.selfTestState = 0;
    enableAllAnnunciators();
    displaySet("", "");
}

void selfTest() {
    // 0) Annuciator lights on
    // 1) Screen on, System code  with screen annunciators (~ 7 seconds)
    // 2) Message "WELCOME TO THE WORLD", "OF MODERN NAVIGATION", Annunciators Off
    // 3) "USE OF GPS ALONE IS", "LIMITED TO VFR" (1000 only?)
    // 4) "", "NAV Computer      --OK" (Scrolls up from bottom)
    // 5) "NAV Computer      --OK", "GPS Computer      --OK"
    // 6) "GPS Computer      --OK", "Database          --OK"
    // 7) Fuel on board (@ 18 seconds)

    switch (g_tln2000_data.selfTestState++) {
        case 5:
            displaySet("SOFTWARE CODE: 20000", "c1991       ");
            break;
        case 10:
            disableAllAnnunciators();
            displaySet("WELCOME TO THE WORLD", "OF MODERN NAVIGATION");
        case 12:
            displaySet("", "NAV Computer    --OK");
            break;
        case 14:
            displaySet("NAV Computer    --OK", "GPS Computer    --OK");
            break;
        case 16:
            displaySet("GPS Computer    --OK", "Database        --OK");
            break;
        case 18:
            changeState(TLN_EVENT_TEST_PASS);
            break;
    }
}

void fuelOnBoard() {
    g_tln2000_data.fedit = !g_tln2000_data.fedit;
    if (g_tln2000_data.fedit) {
        displaySet("FUEL ON BOARD", "123.4");
        setEnt(TLN_ANNUNCIATOR_ON);
    } else {
        switch (g_tln2000_data.i) {
            case 0:
                displaySet("FUEL ON BOARD", "");
                snprintf(displayGetBot(), 21, "%.1f", g_tln2000_data.fuel);
                break;
            case 1:
                displaySet("FUEL ON BOARD", " 23.4");
                break;
            case 2:
                displaySet("FUEL ON BOARD", "1 3.4");
                break;
            case 3:
                displaySet("FUEL ON BOARD", "12 .4");
                break;
            case 4:
                displaySet("FUEL ON BOARD", "123. ");
                break;
        }
        setEnt(TLN_ANNUNCIATOR_OFF);
    }
}

void fuelOnBoardNext() {
    if (g_tln2000_data.i < 4) {
        g_tln2000_data.i++;
    }
}

void fuelOnBoardPrev() {
    if (g_tln2000_data.i > 0) {
        g_tln2000_data.i--;
    }
}

bool rdyForUpdate = false;
void readyForNav() {
    setEnt(TLN_ANNUNCIATOR_OFF);
    if (rdyForUpdate) {
        displaySet("Ready for Navigation", "Select any mode   ");
    } else {
        displaySet("Ready for Navigation", "");
    }
    rdyForUpdate = !rdyForUpdate;
}

int t = 0;
void updateTimeout() {
    if (t++ > 1) {
        changeState(TLN_EVENT_TIMEOUT);
    }
}

void resetTimeout() { t = 0; }

void powerOff() {
    displaySet("", "");
    disableAllAnnunciators();
}

// direct
// void aptVorDirect()
// {
//     data.directWaypoint = "KMHT";
// }

void auxMode() { setAuxMode(); }

TLN_STATE_TRANSISTION states[] = {

    // Power on
    {TLN_STATE_OFF, TLN_EVENT_BTN_POWER, TLN_STATE_SELF_TEST, &selfTestStart},

    // From any state, power off
    {TLN_STATE_ANY, TLN_EVENT_BTN_POWER, TLN_STATE_OFF, &powerOff},

    {TLN_STATE_SELF_TEST, TLN_EVENT_UPDATE, TLN_STATE_SELF_TEST, &selfTest},
    {TLN_STATE_SELF_TEST, TLN_EVENT_TEST_PASS, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoard},
    {TLN_STATE_SELF_TEST, TLN_EVENT_ANY, TLN_STATE_SELF_TEST, 0},

    // NAV
    {TLN_STATE_NAV, TLN_EVENT_UPDATE, TLN_STATE_NAV, &nav},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_NAV, &navNextTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_NAV, &navPrevTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV, &navNextBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV, &navPrevBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV_HOLD, TLN_STATE_NAV, &navReset},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV, TLN_STATE_NAV_DES, &navDes},

    // NAV destination
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav},
    {TLN_STATE_NAV_DES, TLN_EVENT_UPDATE, TLN_STATE_NAV_DES, &navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV_DES, &navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV_DES, &navDes},

    // WPT
    {TLN_STATE_WPT, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &category},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &wptCategoryNext},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_UPDATE, TLN_STATE_WPT_CATEGORY, &updateTimeout},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_TIMEOUT, TLN_STATE_WPT, &wpt},

    // CALC
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_CALC, &calcNext},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_CALC, &calcPrev},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_CALC, &calcNextSub},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_CALC, &calcPrevSub},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ENT, TLN_STATE_CALC_EDIT, 0},
    {TLN_STATE_CALC, TLN_EVENT_BTN_CALC, TLN_STATE_CALC_PPOS_SAVE, &calcSavePPos},
    {TLN_STATE_CALC_PPOS_SAVE, TLN_EVENT_BTN_CALC, TLN_STATE_CALC, &calc},
    {TLN_STATE_CALC_EDIT, TLN_EVENT_BTN_ENT, TLN_STATE_CALC, &calc},

    // AptVor - category
    // {TLN_STATE_APTVOR, TLN_EVENT_BTN_DIRECT, TLN_STATE_DIRECT, &aptVorDirect},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR_CATEGORY, &aptVorCategory},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_APTVOR, &aptVorNext},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_APTVOR, &aptVorPrev},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR_CATEGORY, &aptVorCategoryNext},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_UPDATE, TLN_STATE_APTVOR_CATEGORY, &updateTimeout},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_TIMEOUT, TLN_STATE_APTVOR, &aptVor},

    // Fuel On Board Prompt, after Init
    {TLN_STATE_FUEL_ON_BOARD_PROMPT, TLN_EVENT_UPDATE, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoard},
    {TLN_STATE_FUEL_ON_BOARD_PROMPT, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoardNext},
    {TLN_STATE_FUEL_ON_BOARD_PROMPT, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoardPrev},
    {TLN_STATE_FUEL_ON_BOARD_PROMPT, TLN_EVENT_BTN_ENT, TLN_STATE_READY_FOR_NAV, &readyForNav},
    {TLN_STATE_FUEL_ON_BOARD_PROMPT, TLN_EVENT_ANY, TLN_STATE_FUEL_ON_BOARD_PROMPT, 0},

    // Ready for nav
    {TLN_STATE_READY_FOR_NAV, TLN_EVENT_UPDATE, TLN_STATE_READY_FOR_NAV, &readyForNav},

    // Fuel On Board Edit
    // {TLN_STATE_FUEL_ON_BOARD_EDIT, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_FUEL_ON_BOARD_EDIT, 0},
    // {TLN_STATE_FUEL_ON_BOARD_EDIT, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_FUEL_ON_BOARD_EDIT, 0},
    // {TLN_STATE_FUEL_ON_BOARD_EDIT, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_FUEL_ON_BOARD_EDIT, 0},
    // {TLN_STATE_FUEL_ON_BOARD_EDIT, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_FUEL_ON_BOARD_EDIT, 0},
    // {TLN_STATE_FUEL_ON_BOARD_EDIT, TLN_EVENT_BTN_ENT, TLN_STATE_FUEL_ON_BOARD_PROMPT, 0},

    // Switch Modes from anywhere
    {TLN_STATE_ANY, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR, &aptVor},
    {TLN_STATE_ANY, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav},
    {TLN_STATE_ANY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT, &wpt},
    {TLN_STATE_ANY, TLN_EVENT_BTN_CALC, TLN_STATE_CALC, &calc},
    {TLN_STATE_ANY, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_CHECKLIST, &auxMode}};

void changeState(const TLN_EVENT event) {
    int statesSize = sizeof(states) / sizeof(states[0]);

    for (int i = 0; i < statesSize; i++) {
        TLN_STATE_TRANSISTION *entry = &states[i];

        if ((currentState == entry->currentState || entry->currentState == TLN_STATE_ANY) &&
            (TLN_EVENT_ANY == entry->transistionEvent || event == entry->transistionEvent)) {
            currentState = entry->nextState;
            if (entry->stateFunction != 0) {
                entry->stateFunction();
            }
            return;
        }
    }

    // TODO Remove simulation code
    // data.currentPosition.lat += 0.1;
    // data.currentPosition.lon -= 0.1;
}

int getState() { return currentState; }
