#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "greatCircle.h"

// const double R = 3437.7468f;  // - (13 * sin(38.3629444f * 0.017453293f)); // nm

// static const greatcircle::LLPoint p = {42.3629444f * 0.017453293f, -71.0063889f * 0.017453293f};

// static const greatcircle::LLPoint q = {33.9424964 * 0.017453293f, -118.4080486 * 0.017453293f};

typedef enum { AIRPORT, VOR, NDB, USER } tln_waypoint_type;

typedef struct tln_waypoints {
    tln_waypoint_type type;
    LLPoint latlon;

    char id[6];
    char name[32];
} tln_waypoint;

typedef struct tln_flightplans {
    tln_waypoint waypoints[20];
} tln_flightplan;

#endif  // _STRUCTS_H_