#include "tln2000ap_nav.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "annunciators.h"
#include "display.h"
#include "state.h"
#include "tln_structs.h"

void timeToStr(char *buf, long timeS) {
    long hours = timeS / 3600;
    long minutes = (timeS % 3600) / 60;
    long seconds = timeS % 60;

    if (hours > 0) {
        sprintf(buf, "%2.1ld:%2.2ld", hours, minutes);
    } else {
        sprintf(buf, "%2.1ld:%2.2ld", minutes, seconds);
    }
}

void nav_WaypointDisplay(char *buf, tln_sm_data_t *data, tln_wp_t *waypoint) {
    char type = '?';

    switch (waypoint->type) {
        case AIRPORT:
            type = 'a';
            break;
        case VOR:
            type = 'v';
            break;
        case NDB:
            type = 'n';
            break;
        case USER:
            type = 'u';
            break;
    }

    char timeStr[7];
    timeToStr(timeStr, data->nav_ete);

    // "tLAXa 124d 227n 0:54";
    sprintf(buf, "t%-.4s%c %3.0fd%3.0fn %.5s", waypoint->usId, type, data->nav_bearing, data->nav_distance, timeStr);
}

void nav_timeDisplay(char *buf, tln_sm_data_t *data) {
    char timeStr[7];
    timeToStr(timeStr, data->nav_ete);

    // TODO: ETA
    // "tLAXa 124d 227n 0:54";
    sprintf(buf, "ETE %.5s ETA X:XXz", timeStr);
}

void nav_vertNavigationDisplay(char *buf, tln_sm_data_t *data) {
    char odd[4] = "ODD";
    char even[5] = "EVEN";
    char *oddEven = (data->nav_ground_track > 0 && data->nav_ground_track < 180) ? odd : even;

    sprintf(buf, "t%3.0fd MAINTAIN %.4s", data->nav_ground_track, oddEven);

    // TODO: AT 12.5 FOR 5.3 d600f
}

void nav_groundTrackDisplay(char *buf, tln_sm_data_t *data) {
    double xtrack = fabs(data->nav_xtrack);
    int precis = (xtrack < 10) ? 2 : ((xtrack < 100) ? 1 : 0);
    sprintf(buf, "d%3.0fd t%3.0fd FLY%c%4.*fn", data->nav_desired_track, data->nav_ground_track,
            (data->nav_xtrack < 0) ? '<' : '>', precis, xtrack);
}

void nav_cdiDisplay(char *buf, tln_sm_data_t *data) {
    // TODO CDI
    sprintf(buf, "[|*|*O*|*|]t%3.0fd%3.0fk", data->nav_ground_track, data->nav_ground_speed);
}

void nav_msaDisplay(char *buf, tln_sm_data_t *data) {
    sprintf(buf, "MSA xxk MESA xxxk");
    // TODO sprintf(buf, "MSA 53k MESA 125k");
}

void nav_TopDisplay(tln_sm_data_t *data) {
    char topDisplay[21] = "";
    switch (data->nav_top_state) {
        case 0:;
            nav_WaypointDisplay(topDisplay, data, &data->waypoint_next);
            break;
        case 1:
            nav_timeDisplay(topDisplay, data);
            break;
        case 2:
            nav_vertNavigationDisplay(topDisplay, data);
            break;
        case 3:
            nav_groundTrackDisplay(topDisplay, data);
            break;
        case 4:
            nav_cdiDisplay(topDisplay, data);
            break;
        case 5:
            nav_msaDisplay(topDisplay, data);
            break;
        default:;
            // return "ehh?";
    }
    display_write(0, 0, topDisplay, 0);
}

void nav_BotDisplay(tln_sm_data_t *data) {
    char botDisplay[21] = "";
    switch (data->nav_bot_state) {
        case 5:
            nav_WaypointDisplay(botDisplay, data, &data->waypoint_next);
            break;
        case 3:
            nav_timeDisplay(botDisplay, data);
            break;
        case 1:
            nav_vertNavigationDisplay(botDisplay, data);
            break;
        case 4:
            nav_groundTrackDisplay(botDisplay, data);
            break;
        case 0:;
            nav_cdiDisplay(botDisplay, data);
            break;
        case 2:
            nav_msaDisplay(botDisplay, data);
            break;
        case 6:
            if (data->nav_alternate_set == true) {
                // return "tSANa 124d 292n 1:10";
                break;
            }
        default:;
            // return "ehh?";
    }
    display_write(0, 1, botDisplay, 0);
}

void nav_updateDisplay(tln_sm_data_t *data) {
    display_clear();
    setNavMode();
    nav_TopDisplay(data);
    nav_BotDisplay(data);
}

void navReset(tln_sm_data_t *data) {
    data->nav_top_state = 0;
    data->nav_bot_state = 0;
    nav_updateDisplay(data);
}

void navNextTop(tln_sm_data_t *data) {
    data->nav_top_state++;
    if (data->nav_top_state > 5) {
        data->nav_top_state = 0;
    }
    nav_updateDisplay(data);
}

void navPrevTop(tln_sm_data_t *data) {
    data->nav_top_state--;
    if (data->nav_top_state < 0) {
        data->nav_top_state = 5;
    }
    nav_updateDisplay(data);
}

void navNextBot(tln_sm_data_t *data) {
    data->nav_bot_state++;
    if ((data->nav_alternate_set && data->nav_bot_state > 6) || (!data->nav_alternate_set && data->nav_bot_state > 5)) {
        data->nav_bot_state = 0;
    }
    nav_updateDisplay(data);
}

void navPrevBot(tln_sm_data_t *data) {
    data->nav_bot_state--;
    if (data->nav_bot_state < 0) {
        if (data->nav_alternate_set) {
            data->nav_bot_state = 6;
        } else {
            data->nav_bot_state = 5;
        }
    }
    nav_updateDisplay(data);
}

void navDes(tln_sm_data_t *data) {
    displaySet("tLAXa 125d 197n 0:47", "LOS ANGELES       CA");
}
