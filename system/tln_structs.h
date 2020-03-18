#ifndef _TLN_STRUCTS_H_
#define _TLN_STRUCTS_H_

#include <stdbool.h>

#include "greatCircle.h"

typedef enum { AIRPORT, VOR, NDB, USER } tln_waypoint_type;

typedef struct tln_waypoints {
    tln_waypoint_type type;
    gc_llp_t latlon;

    char icao[6];
    char usId[6];
    char name[32];
    char city[32];
    char state[3];
} tln_wp_t;

typedef struct tln_flightplans {
    tln_wp_t waypoints[20];
} tln_fp_t;

struct tln_sm_data {
    gc_llp_t gps_position;
    float heading;
    float airspeed;

    // Waypoints
    tln_wp_t waypoint_current;
    tln_wp_t waypoint_next;

    double nav_ground_track;   // degrees
    double nav_ground_speed;   // knots
    double nav_bearing;        // degrees
    double nav_desired_track;  // degrees
    double nav_distance;       // nm
    double nav_xtrack;         // nm (negative for left, positive for right)
    double nav_ete;            // seconds

    // Navigation Mode State Data
    int nav_top_state;
    int nav_bot_state;
    bool nav_alternate_set;

    // Waypoint Mode State Data
    int wptCategory;
    int wpt_airportPage;

    int air_category;
    int vor_category;
    int ndb_category;
    int int_category;
    int usr_category;

    float fuel;
    bool fedit;

    int selfTestState;
    int t;

    long systemTime;
    int cursorPosition;
};

#endif  // _STRUCTS_H_