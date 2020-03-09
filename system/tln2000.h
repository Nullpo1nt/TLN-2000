#ifndef _TLN2000_H_
#define _TLN2000_H_

#include "greatCircle.h"
#include "structs.h"

typedef enum {
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

typedef enum {
    // Generic update Event
    TLN_EVENT_ANY = 0,
    TLN_EVENT_UPDATE = 1,
    TLN_EVENT_TIMEOUT = 2,

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
    TLN_EVENT_BTN_ROT_IN_CC
} TLN_EVENT;

typedef struct TLN_STATE_TRANSISTION_S {
    TLN_STATE currentState;
    TLN_EVENT transistionEvent;
    TLN_STATE nextState;
    void (*stateFunction)(void);
} TLN_STATE_TRANSISTION;

void changeState(TLN_EVENT event);

int getState();

#endif  // _TLN2000_H_