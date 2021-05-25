#include "tln2000ap.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "annunciators.h"
#include "database.h"
#include "display.h"
#include "tln2000ap_aptVor.h"
#include "tln2000ap_aux.h"
#include "tln2000ap_calc.h"
#include "tln2000ap_nav.h"
#include "tln2000ap_wpt.h"

tln_sm_t tln2000sm;

struct tln_sm_data g_tln2000_data = {
    .gps_position = {42.3629444f, -71.0063889f},
    .nav_ground_speed = 250,
    .nav_ground_track = 270,

    // Active Flight Plan
    .waypoint_current = {AIRPORT, {42.3629444f, -71.0063889f}, "KBOS", "BOS", "Boston"},
    .waypoint_next = {AIRPORT, {33.9424964, -118.4080486}, "KLAX", "LAX", "Los Angelos"},

    // Aircraft Properties
    .fuel = 123.4f,
    .fedit = false,
    .selfTestState = 0,
    .t = 0,
    .systemTime = 0l,
    .cursorPosition = 0,
    .nav_alternate_set = true};

void selfTestStart(tln_sm_data_t *data) {
    data->selfTestState = 0;
    displaySet("", "");
    enableAllAnnunciators();
}

void selfTest(tln_sm_data_t *data) {
    // 0) Annuciator lights on
    // 1) Screen on, System code  with screen annunciators (~ 7 seconds)
    // 2) Message "WELCOME TO THE WORLD", "OF MODERN NAVIGATION", Annunciators Off
    // 3) "USE OF GPS ALONE IS", "LIMITED TO VFR" (1000 only?)
    // 4) "", "NAV Computer      --OK" (Scrolls up from bottom)
    // 5) "NAV Computer      --OK", "GPS Computer      --OK"
    // 6) "GPS Computer      --OK", "Database          --OK"
    // 7) Fuel on board (@ 18 seconds)

    switch (data->selfTestState++) {
        case 5:
            displaySet("SOFTWARE CODE: 20000", "c1991       ");
            state_update(tln2000sm, TLN_EVENT_LCD_ON);
            break;
        case 10:
            disableAllAnnunciators();
            displaySet("WELCOME TO THE WORLD", "OF MODERN NAVIGATION");
            break;
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
            state_update(tln2000sm, TLN_EVENT_TEST_PASS);
            break;
    }
}

void fuelOnBoard() {
    display_clear();

    g_tln2000_data.fedit = !g_tln2000_data.fedit;
    if (g_tln2000_data.fedit) {
        // displaySet("FUEL ON BOARD", "123.4");
        setEnt(TLN_ANNUNCIATOR_ON);
    } else {
        // switch (g_tln2000_data.i) {
        //     case 0:

        //         // displaySet("FUEL ON BOARD", "");
        //         // snprintf(displayGetBot(), 21, "%.1f", g_tln2000_data.fuel);
        //         break;
        //     case 1:
        //         displaySet("FUEL ON BOARD", " 23.4");
        //         break;
        //     case 2:
        //         displaySet("FUEL ON BOARD", "1 3.4");
        //         break;
        //     case 3:
        //         displaySet("FUEL ON BOARD", "12 .4");
        //         break;
        //     case 4:
        //         displaySet("FUEL ON BOARD", "123. ");
        //         break;
        // }
        setEnt(TLN_ANNUNCIATOR_OFF);
    }

    display_write(0, 0, "FUEL ON BOARD", 0);
    display_input(15, 1, "432.1", g_tln2000_data.cursorPosition);
}

void fuelOnBoardNext() {
    if (g_tln2000_data.cursorPosition < 4) {
        g_tln2000_data.cursorPosition++;
    }
}

void fuelOnBoardPrev() {
    if (g_tln2000_data.cursorPosition > 0) {
        g_tln2000_data.cursorPosition--;
    }
}

void readyForNav(tln_sm_data_t *data) {
    setEnt(TLN_ANNUNCIATOR_OFF);
    if (data->systemTime % 2 == 0) {
        displaySet("Ready for Navigation", "Select any mode   ");
    } else {
        displaySet("Ready for Navigation", "");
    }
}

void resetTimeout() {
    g_tln2000_data.t = 0;
}

void powerOff() {
    displaySet("", "");
    disableAllAnnunciators();
}

double xxx = 0;
double xx = 0.1;

void updateSystems(tln_sm_data_t *data) {
    xxx += xx;
    if (xxx > 3) {
        xx = -0.1;
    }
    if (xxx < 0) {
        xx = 0.1;
    }

    data->systemTime += 1;

    // Update timeout event var
    if (data->t != -1) {
        if (data->t++ > 1) {
            state_update(tln2000sm, TLN_EVENT_TIMEOUT);
        }
    }

    data->gps_position.lon -= 0.1;
    data->nav_ground_speed = 250 + sin(xxx) * 20;
    data->nav_ground_track = 270 + sin(xxx) * 20;

    // Aircraft to next waypoint
    gc_solution_t aircraft_to_waypoint;
    gc_distance_bearing(&aircraft_to_waypoint, &data->gps_position, &data->waypoint_next.latlon, TOLERANCE_CM);

    // Current waypoint to next
    gc_solution_t current_to_next;
    gc_distance_bearing(&current_to_next, &data->waypoint_current.latlon, &data->waypoint_next.latlon, TOLERANCE_CM);

    data->nav_bearing = gc_bearing_deg(&aircraft_to_waypoint);
    data->nav_desired_track = gc_bearing_deg(&current_to_next);
    data->nav_distance = gc_distance_nm(&aircraft_to_waypoint);
    data->nav_xtrack =
        gc_distance_nm(&aircraft_to_waypoint) * sin(aircraft_to_waypoint.bearing - current_to_next.bearing);
    data->nav_ete = (data->nav_distance / data->nav_ground_speed) * 3600;  // convert to seconds from hours
}

tln_sm_transition_t states[] = {

    // Power on
    {TLN_STATE_OFF, TLN_EVENT_BTN_POWER, TLN_STATE_SELF_TEST_START, &selfTestStart},
    {TLN_STATE_OFF, TLN_EVENT_ANY, TLN_STATE_OFF, 0},

    // From any state, power off
    {TLN_STATE_ANY, TLN_EVENT_BTN_POWER, TLN_STATE_OFF, &powerOff},

    {TLN_STATE_SELF_TEST_START, TLN_EVENT_UPDATE, TLN_STATE_SELF_TEST_START, &selfTest},
    {TLN_STATE_SELF_TEST_START, TLN_EVENT_LCD_ON, TLN_STATE_SELF_TEST, 0},
    {TLN_STATE_SELF_TEST_START, TLN_EVENT_ANY, TLN_STATE_SELF_TEST_START, 0},

    {TLN_STATE_SELF_TEST, TLN_EVENT_UPDATE, TLN_STATE_SELF_TEST, &selfTest},
    {TLN_STATE_SELF_TEST, TLN_EVENT_TEST_PASS, TLN_STATE_FUEL_ON_BOARD_PROMPT, &fuelOnBoard},

    // NAV
    {TLN_STATE_NAV, TLN_EVENT_UPDATE, TLN_STATE_NAV, &nav_updateDisplay},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_NAV, &navNextTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_NAV, &navPrevTop},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV, &navNextBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV, &navPrevBot},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV_HOLD, TLN_STATE_NAV, &navReset},
    {TLN_STATE_NAV, TLN_EVENT_BTN_NAV, TLN_STATE_NAV_DES, &navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav_updateDisplay},

    // NAV destination
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav_updateDisplay},
    {TLN_STATE_NAV_DES, TLN_EVENT_UPDATE, TLN_STATE_NAV_DES, &navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_NAV_DES, &navDes},
    {TLN_STATE_NAV_DES, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_NAV_DES, &navDes},

    // WPT
    //{TLN_STATE_WPT, TLN_EVENT_SYSTEM_UPDATE, TLN_STATE_WPT, &wpt_updateData, 1},
    {TLN_STATE_WPT, TLN_EVENT_UPDATE, TLN_STATE_WPT, &wpt_displayWaypoint},
    {TLN_STATE_WPT, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_WPT, &wpt_pagePrev},
    {TLN_STATE_WPT, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_WPT, &wpt_pageNext},
    {TLN_STATE_WPT, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_WPT, &wpt_waypointPrev},
    {TLN_STATE_WPT, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_WPT, &wpt_waypointNext},
    {TLN_STATE_WPT, TLN_EVENT_BTN_ENT, TLN_STATE_WPT_SELECT, &wpt_select},
    {TLN_STATE_WPT, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &wpt_displayCategory},
    {TLN_STATE_WPT, TLN_EVENT_BTN_WPT_HOLD, TLN_STATE_WPT, &wpt_categoryReset},

    {TLN_STATE_WPT_SELECT, TLN_EVENT_UPDATE, TLN_STATE_WPT_SELECT, &wpt_select},
    {TLN_STATE_WPT_SELECT, TLN_EVENT_BTN_ROT_OUT_CC, TLN_STATE_WPT_SELECT, &wpt_selectPrevField},
    {TLN_STATE_WPT_SELECT, TLN_EVENT_BTN_ROT_OUT_CW, TLN_STATE_WPT_SELECT, &wpt_selectNextField},
    {TLN_STATE_WPT_SELECT, TLN_EVENT_BTN_ROT_IN_CC, TLN_STATE_WPT_SELECT, &wpt_selectPrevLetter},
    {TLN_STATE_WPT_SELECT, TLN_EVENT_BTN_ROT_IN_CW, TLN_STATE_WPT_SELECT, &wpt_selectNextLetter},
    {TLN_STATE_WPT_SELECT, TLN_EVENT_BTN_ENT, TLN_STATE_WPT, &wpt_selectEnter},

    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT_CATEGORY, &wpt_categoryNext},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_TIMEOUT, TLN_STATE_WPT, &wpt_displayCategory},
    {TLN_STATE_WPT_CATEGORY, TLN_EVENT_BTN_WPT_HOLD, TLN_STATE_WPT, &wpt_categoryReset},

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

    {TLN_STATE_AUX_CHECKLIST, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_SYSTEM_STATUS, 0},
    {TLN_STATE_AUX_SYSTEM_STATUS, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_SENSOR_STATUS, 0},
    {TLN_STATE_AUX_SENSOR_STATUS, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_CONFIGURE, 0},
    {TLN_STATE_AUX_CONFIGURE, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_SETUP, 0},
    {TLN_STATE_AUX_SETUP, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_CHECKLIST, 0},

    // Switch Modes from anywhere
    {TLN_STATE_ANY, TLN_EVENT_BTN_APTVOR, TLN_STATE_APTVOR, &aptVor},
    {TLN_STATE_ANY, TLN_EVENT_BTN_NAV, TLN_STATE_NAV, &nav_updateDisplay},
    {TLN_STATE_ANY, TLN_EVENT_BTN_WPT, TLN_STATE_WPT, &wpt_displayWaypoint},
    {TLN_STATE_ANY, TLN_EVENT_BTN_CALC, TLN_STATE_CALC, &calc},
    {TLN_STATE_ANY, TLN_EVENT_BTN_AUX, TLN_STATE_AUX_CHECKLIST, &auxMode},
    {TLN_STATE_ANY, TLN_EVENT_SYSTEM_UPDATE, TLN_STATE_ANY, &updateSystems}};

tln_sm_t init_tln2000() {
    return state_new(TLN_STATE_OFF, states, (sizeof(states) / sizeof(states[0])), &g_tln2000_data);
}