#include "tln2000ap_wpt.h"

#include <stdio.h>

#include "annunciators.h"
#include "database.h"
#include "display.h"
#include "state.h"
#include "tln_structs.h"

// WPT

// struct {
//     char name[10]
// } wpt_pages[] = {{"AIRPORT"}, {"VOR"}, {"NDB"}, {"INT"}, {"USER"}};

int wpt_currentAirport = 0;

void wpt_waypointNext(tln_sm_data_t *data) {
    if (++wpt_currentAirport > 4) {
        wpt_currentAirport = 4;
    } else {
        wpt_displayWaypoint(data);
    }
}

void wpt_waypointPrev(tln_sm_data_t *data) {
    if (--wpt_currentAirport < 0) {
        wpt_currentAirport = 0;
    } else {
        wpt_displayWaypoint(data);
    }
}

void wpt_select(tln_sm_data_t *data) {
    setEnt((data->systemTime % 2 == 0) ? TLN_ANNUNCIATOR_ON : TLN_ANNUNCIATOR_OFF);
    test();
}

void wpt_selectPrevField(tln_sm_data_t *data) {}
void wpt_selectNextField(tln_sm_data_t *data) {}
void wpt_selectPrevLetter(tln_sm_data_t *data) {}
void wpt_selectNextLetter(tln_sm_data_t *data) {}
void wpt_selectEnter(tln_sm_data_t *data) {
    setEnt(TLN_ANNUNCIATOR_OFF);
}

void wpt_displayAirport(char *top, char *bot, tln_wp_t *airport, gc_llp_t *currentPosition, int page, int cursorPos) {
    gc_solution_t solution;
    gc_distance_bearing(&solution, currentPosition, &airport->latlon, TOLERANCE_CM);
    double bearing = gc_bearing_deg(&solution);
    double distance = gc_distance_nm(&solution);

    sprintf(top, "t%-.4sa %3.0fd%3.0fn xxx", airport->usId, bearing, distance);

    switch (page) {
        case 0:
            sprintf(bot, "%-17.17s %.2s", airport->city, airport->state);
            break;
        case 1:
            sprintf(bot, "%-20.20s", airport->name);
            break;
        case 2:
            sprintf(bot, "ATS ----- APP -----");
            break;
        case 3:
            sprintf(bot, "TWR ----- GND -----");
            break;
        case 4:
            sprintf(bot, "CTF ----- UNI -----");
            break;
        case 5:
            sprintf(bot, "ELEVATION");
            break;
        case 6:
            sprintf(bot, "beacon, light, appr, services");
            break;
        case 7:
            sprintf(bot, "runway");
            break;
    }
}

void wpt_displayWaypoint(tln_sm_data_t *data) {
    setWptMode();
    display_clear();
    char top[22] = "";
    char bot[32] = "";

    switch (data->wptCategory) {
        case 0:;
            tln_wp_t *airport = database_getAirport(wpt_currentAirport);
            wpt_displayAirport(top, bot, airport, &data->gps_position, data->wpt_airportPage, -1);
            break;
        case 1:
            displaySet("fSGDv 219d 89.3n", "NAPA         CA");
            break;
        case 2:
            displaySet("fSGDv 219d 89.3n", "NAPA         CA");
            break;
        case 3:
            displaySet("tTWAINi 063d 1358n", "REGION:NORTH CENTRAL");
            break;
        case 4:
            displaySet("tTRMBLu 196d 116n", "l37d23510N122d06490w");
            break;
    }

    display_write(0, 0, top, 0);
    display_write(0, 1, bot, 0);
}

void wpt_displayCategory(tln_sm_data_t *data) {
    data->t = 0;

    // display_sprintf(0, "", wpt_pages[data->wptCategory]);
    switch (data->wptCategory) {
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

void wpt_categoryNext(tln_sm_data_t *data) {
    if (++data->wptCategory > 4) {
        data->wptCategory = 0;
    }

    wpt_displayCategory(data);
}

void wpt_pagePrev(tln_sm_data_t *data) {
    switch (data->wptCategory) {
        case 0:
            if (--data->wpt_airportPage < 0) {
                data->wpt_airportPage = 7;
            }
            break;
    }
    wpt_displayWaypoint(data);
}

void wpt_pageNext(tln_sm_data_t *data) {
    switch (data->wptCategory) {
        case 0:
            if (++data->wpt_airportPage > 7) {
                data->wpt_airportPage = 0;
            }
            break;
    }
    wpt_displayWaypoint(data);
}

void wpt_categoryReset(tln_sm_data_t *data) {
    data->wptCategory = 0;
}

void wpt_airport_display(tln_sm_data_t *data) {}

void wpt_vor_display(tln_sm_data_t *data) {}

void wpt_ndb_display(tln_sm_data_t *data) {}

void wpt_int_display(tln_sm_data_t *data) {}

void wpt_user_display(tln_sm_data_t *data) {}
