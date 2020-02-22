#ifndef _TLN2000_H_
#define _TLN2000_H_

#include <stdio.h>
#include <string.h>
#include <cmath>

#include "annunciators.h"
#include "aptVor.h"
#include "calc.h"
#include "display.h"
#include "nav.h"
#include "wpt.h"

#include "greatCircle.h"

namespace tln
{

const double R = 3437.7468f; // - (13 * sin(38.3629444f * 0.017453293f)); // nm

static const greatcircle::LLPoint p = {
    42.3629444f * 0.017453293f,
    -71.0063889f * 0.017453293f};

static const greatcircle::LLPoint q = {
    33.9424964 * 0.017453293f,
    -118.4080486 * 0.017453293f};

typedef struct TLN_WAYPOINT_S
{
    greatcircle::LLPoint latlon;

    char id[6];
    char name[32];
} TLN_WAYPOINT;

typedef struct TLN_FLIGHT_PLAN_S
{
    TLN_WAYPOINT waypoints[20];
} TLN_FLIGHT_PLAN;

typedef enum : int
{
    TLN_STATE_OFF = 0,
    TLN_STATE_SELF_TEST,
    TLN_STATE_FUEL_ON_BOARD_PROMPT,
    TLN_STATE_FUEL_ON_BOARD_EDIT,
    TLN_STATE_READY_FOR_NAV,

    // NAV
    TLN_STATE_NAV,
    TLN_STATE_NAV_DES,

    // WPT
    TLN_STATE_WPT,
    TLN_STATE_WPT_CATEGORY,

    // CALC
    TLN_STATE_CALC,
    TLN_STATE_CALC_EDIT,
    TLN_STATE_CALC_PPOS_SAVE,

    TLN_STATE_AUX_CHECKLIST,
    TLN_STATE_AUX_STATUS,
    TLN_STATE_AUX_VOLTTEMP,
    TLN_STATE_AUX_DATABASE_EXP,
    TLN_STATE_AUX_SOFT_REV,
    TLN_STATE_AUX_SOFT_CODE,

    // APTVOR
    TLN_STATE_APTVOR,
    TLN_STATE_APTVOR_CATEGORY,

    // Match any state
    TLN_STATE_ANY
} TLN_STATE;

typedef enum
{
    // Generic update Event
    TLN_EVENT_UPDATE,
    TLN_EVENT_TIMEOUT,

    // Self test event
    TLN_EVENT_TEST_PASS,

    // Mode key-press events
    TLN_EVENT_BTN_POWER,
    TLN_EVENT_BTN_NAV,
    TLN_EVENT_BTN_NAV_HOLD,
    TLN_EVENT_BTN_WPT,
    TLN_EVENT_BTN_WPT_HOLD,
    TLN_EVENT_BTN_FPL,
    TLN_EVENT_BTN_FPL_HOLD,
    TLN_EVENT_BTN_CALC,
    TLN_EVENT_BTN_CALC_HOLD,
    TLN_EVENT_BTN_AUX,
    TLN_EVENT_BTN_AUX_HOLD,
    TLN_EVENT_BTN_APTVOR,
    TLN_EVENT_BTN_APTVOR_HOLD,

    // Function key presses
    TLN_EVENT_BTN_DIRECT,
    TLN_EVENT_BTN_MSG,
    TLN_EVENT_BTN_ENT,

    // Control wheel
    TLN_EVENT_BTN_ROT_OUT_CW,
    TLN_EVENT_BTN_ROT_OUT_CC,
    TLN_EVENT_BTN_ROT_IN_CW,
    TLN_EVENT_BTN_ROT_IN_CC,

    TLN_EVENT_ANY
} TLN_EVENT;

typedef struct TLN_STATE_TRANSISTION_S
{
    TLN_STATE currentState;
    TLN_EVENT transistionEvent;
    TLN_STATE nextState;
    void (*stateFunction)(void);
} TLN_STATE_TRANSISTION;

typedef struct TLN_DATA_S
{

    greatcircle::LLPoint currentPosition = {
        42.3629444,
        -71.0063889};

    // primary destination
    TLN_WAYPOINT current = {{33.9424964, -118.4080486}, "KLAX", "Los Angelos"}; // namespace tln2000

    //char *currentWpt = "LAXa";
    int track = 124;
    int direct = 124;
    float fly = 0.01f;
    int speed = 250;
    char *evenOdd = "ODD";
    int distance = 227;
    int etem = 54;
    int eteh = 0;
    int etam = 53;
    int etah = 3;

    float msa = 5.3f;
    float mesa = 12.5f;

    char *directWaypoint = "";
} TLN_DATA;

void changeState(TLN_EVENT event);

int getState();

} // namespace tln

#endif // _TLN2000_H_