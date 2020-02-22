#include "tln2000.h"

namespace tln
{

// Current state
TLN_STATE currentState = TLN_STATE_OFF;

// Internal state data
TLN_DATA data;

int selfTestState = 0;

void selfTestStart()
{
    selfTestState = 0;
    annunciators::enableAllAnnunciators();
    display::set("", "");
}

void selfTest()
{
    // 0) Annuciator lights on
    // 1) Screen on, System code  with screen annunciators (~ 7 seconds)
    // 2) Message "WELCOME TO THE WORLD", "OF MODERN NAVIGATION", Annunciators Off
    // 3) "USE OF GPS ALONE IS", "LIMITED TO VFR" (1000 only?)
    // 4) "", "NAV Computer      --OK" (Scrolls up from bottom)
    // 5) "NAV Computer      --OK", "GPS Computer      --OK"
    // 6) "GPS Computer      --OK", "Database          --OK"
    // 7) Fuel on board (@ 18 seconds)

    switch (selfTestState++)
    {
    case 5:
        display::set("SOFTWARE CODE: 20000", "c1991       ");
        break;
    case 10:
        annunciators::disableAllAnnunciators();
        display::set("WELCOME TO THE WORLD", "OF MODERN NAVIGATION");
    case 12:
        display::set("", "NAV Computer    --OK");
        break;
    case 14:
        display::set("NAV Computer    --OK", "GPS Computer    --OK");
        break;
    case 16:
        display::set("GPS Computer    --OK", "Database        --OK");
        break;
    case 18:
        changeState(TLN_EVENT_TEST_PASS);
        break;
    }
}

float fuel = 123.4;
bool fedit = false;
int i = 1;
void fuelOnBoard()
{

    fedit = !fedit;
    if (fedit)
    {
        display::set("FUEL ON BOARD", "123.4");
        annunciators::setEnt(annunciators::TLN_ANNUNCIATOR_ON);
    }
    else
    {
        switch (i)
        {
        case 0:
            display::set("FUEL ON BOARD", "");
            snprintf(display::getBot(), 21, "%.1f", fuel);
            break;
        case 1:
            display::set("FUEL ON BOARD", " 23.4");
            break;
        case 2:
            display::set("FUEL ON BOARD", "1 3.4");
            break;
        case 3:
            display::set("FUEL ON BOARD", "12 .4");
            break;
        case 4:
            display::set("FUEL ON BOARD", "123. ");
            break;
        }
        annunciators::setEnt(annunciators::TLN_ANNUNCIATOR_OFF);
    }
}

void fuelOnBoardNext()
{
    if (i < 4)
    {
        i++;
    }
}

void fuelOnBoardPrev()
{
    if (i > 0)
    {
        i--;
    }
}

bool rdyForUpdate = false;
void readyForNav()
{
    annunciators::setEnt(annunciators::TLN_ANNUNCIATOR_OFF);
    if (rdyForUpdate)
    {
        display::set("Ready for Navigation", "Select any mode   ");
    }
    else
    {
        display::set("Ready for Navigation", "");
    }
    rdyForUpdate = !rdyForUpdate;
}

int t = 0;
void updateTimeout()
{
    if (t++ > 1)
    {
        changeState(TLN_EVENT_TIMEOUT);
    }
}

void resetTimeout()
{
    t = 0;
}

void powerOff()
{
    display::set("", "");
    annunciators::disableAllAnnunciators();
}

// direct
// void aptVorDirect()
// {
//     data.directWaypoint = "KMHT";
// }

void aux()
{
    annunciators::setAuxMode();
}

TLN_STATE auxState = TLN_STATE_AUX_CHECKLIST;

TLN_STATE_TRANSISTION states[] = {

    // Power on
    {TLN_STATE_OFF, TLN_EVENT_BTN_POWER, TLN_STATE_SELF_TEST, &selfTestStart},

    // From any state, power off
    {TLN_STATE_ANY, TLN_EVENT_BTN_POWER, TLN_STATE_OFF, &powerOff},

    {TLN_STATE_SELF_TEST, TLN_EVENT_UPDATE, TLN_STATE_SELF_TEST, &selfTest},
    {TLN_STATE_SELF_TEST, TLN_EVENT_TEST_PASS, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoard},
    {TLN_STATE_SELF_TEST, TLN_EVENT_ANY, TLN_STATE_SELF_TEST, 0},

    // NAV
    {TLN_STATE_NAV, TLN_EVENT_UPDATE, TLN_STATE_NAV, &nav::nav},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_NAV, &nav::navNextTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_NAV, &nav::navPrevTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV, &nav::navNextBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV, &nav::navPrevBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV_HOLD, TLN_STATE_NAV, &nav::navReset},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV, TLN_STATE_NAV_DES, &nav::navDes},

    // NAV destination
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav::nav},
    {TLN_STATE_NAV_DES, TLN_EVENT_UPDATE, TLN_STATE_NAV_DES, &nav::navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV_DES, &nav::navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV_DES, &nav::navDes},

    // WPT
    {TLN_STATE_WPT, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &wpt::category},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &wpt::wptCategoryNext},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_UPDATE, TLN_STATE_WPT_CATEGORY, &updateTimeout},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_TIMEOUT, TLN_STATE_WPT, &wpt::wpt},

    // CALC
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_CALC, &calc::calcNext},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_CALC, &calc::calcPrev},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_CALC, &calc::calcNextSub},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_CALC, &calc::calcPrevSub},
    {TLN_STATE_CALC, TLN_EVENT_BTN_ENT, TLN_STATE_CALC_EDIT, 0},
    {TLN_STATE_CALC, TLN_EVENT_BTN_CALC, TLN_STATE_CALC_PPOS_SAVE, &calc::calcSavePPos},
    {TLN_STATE_CALC_PPOS_SAVE, TLN_EVENT_BTN_CALC, TLN_STATE_CALC, &calc::calc},
    {TLN_STATE_CALC_EDIT, TLN_EVENT_BTN_ENT, TLN_STATE_CALC, &calc::calc},

    // AptVor - category
    // {TLN_STATE_APTVOR, TLN_EVENT_BTN_DIRECT, TLN_STATE_DIRECT, &aptVorDirect},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR_CATEGORY, &aptvor::aptVorCategory},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_APTVOR, &aptvor::aptVorNext},
    {TLN_STATE_APTVOR, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_APTVOR, &aptvor::aptVorPrev},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR_CATEGORY, &aptvor::aptVorCategoryNext},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_UPDATE, TLN_STATE_APTVOR_CATEGORY, &updateTimeout},
    {TLN_STATE_APTVOR_CATEGORY, TLN_EVENT_TIMEOUT, TLN_STATE_APTVOR, &aptvor::aptVor},

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
    {TLN_STATE_ANY, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR, &aptvor::aptVor},
    {TLN_STATE_ANY, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav::nav},
    {TLN_STATE_ANY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT, &wpt::wpt},
    {TLN_STATE_ANY, TLN_EVENT_BTN_CALC, TLN_STATE_CALC, &calc::calc},
    {TLN_STATE_ANY, TLN_EVENT_BTN_AUX, auxState, &aux}};

void changeState(const TLN_EVENT event)
{
    int statesSize = sizeof(states) / sizeof(states[0]);

    for (int i = 0; i < statesSize; i++)
    {
        TLN_STATE_TRANSISTION *entry = &states[i];

        if ((currentState == entry->currentState || entry->currentState == TLN_STATE_ANY) &&
            (TLN_EVENT_ANY == entry->transistionEvent || event == entry->transistionEvent))
        {
            currentState = entry->nextState;
            if (entry->stateFunction != 0)
            {
                entry->stateFunction();
            }
            return;
        }
    }

    // TODO Remove simulation code
    // data.currentPosition.lat += 0.1;
    // data.currentPosition.lon -= 0.1;
}

int getState()
{
    return currentState;
}

} // namespace tln