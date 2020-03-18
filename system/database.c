#include "database.h"

#include "tln_structs.h"

tln_wp_t database_airports[] = {
    {AIRPORT, {33.9424964, -118.4080486}, "KLAX", "LAX", "LAX Intl", "Los Angelos", "CA"},
    {AIRPORT,
     {42.3629444f, -71.0063889f},
     "KBOS",
     "BOS",
     "Boston Logan Intl"
     "Boston",
     "MA"},
    {AIRPORT, {21.3245, -157.9251}, "PHNL", "HNL", "Honolulu", "Hawaaaa", "HI"},
    {AIRPORT, {28.4312, -81.3081}, "KMCO", "MCO", "Orlando Intl", "Orlando", "FL"},
    {AIRPORT, {37.6213, -122.3790}, "KSFO", "SFO", "SanFran Intl", "San Francisco", "CA"},
};

tln_wp_t* database_getAirport(int x) {
    return &database_airports[x];
}

//     const greatcircle::LLPoint newportRI = {41.49008 * 0.017453293, -71.312796 * 0.017453293};
//     const greatcircle::LLPoint clevelandOH = {41.499498 * 0.017453293, -81.695391 * 0.017453293};

// tln_waypoint vors[];

// tln_waypoint ndbs[];

// tln_waypoint intersections[];

// tln_waypoint userwaypoints[];

// tln_flightplan flightplans[];
