#include "tln2000ap_wpt.h"

#include <stdio.h>

#include "annunciators.h"
#include "database.h"
#include "display.h"
#include "state.h"
#include "tln_structs.h"

// WPT

void wpt_displayWaypoint(tln_sm_data_t *data) {
    setWptMode();
    display_clear();
    char top[22] = "";
    char bot[22] = "";

    switch (data->wptCategory) {
        case 0:;
            tln_wp_t *airport = database_getAirport(4);
            gc_solution_t solution;
            gc_distance_bearing(&solution, &data->gps_position, &airport->latlon, TOLERANCE_CM);
            double bearing = gc_bearing_deg(&solution);
            double distance = gc_distance_nm(&solution);

            sprintf(top, "t%-.4sa %3.0fd%3.0fn xxx", airport->usId, bearing, distance);

            switch (data->wpt_airportPage) {
                case 0:
                    sprintf(bot, "%-17.17s %.2s", airport->city, airport->state);
                    break;
            }
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
            if (--data->wpt_airportPage > 7) {
                data->wpt_airportPage = 0;
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
