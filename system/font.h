#ifndef _FONT_H_
#define _FONT_H_

typedef enum {
    // A-Z
    // a-z
    // 0-9
    // Symbols
    SYB_COLON,
    SYB_PERIOD,
    SYB_AT,     // @
    SYB_AMP,    // &
    SYB_QUOTE,  // '
    SYB_POUND,  // #

    SYB_PLUS,
    SYB_MINUS,
    SYB_PLUS_MINUS,

    SYB_DEGREE,
    SYB_DEGREE_C,
    SYB_LINE,         // -
    SYB_UNDERSCORE,   // _
    SYB_ARROR_RIGHT,  // ->
    SYB_ARROR_LEFT,
    SYB_ARROR_UP,
    SYB_ARROR_DOWN,

    // Labels
    LBL_ZULU,            // Z (little)
    LBL_LOCAL,           // L (little)
    LBL_KNOTS,           // KT (over)
    LBL_DME_MILES,       // DM (over)
    LBL_NAUTICAL_MILES,  // NM (over)
    LBL_HEADING,         // HD (over)
    LBL_TRUE_AIRSPEED,   // TA (over)
    LBL_DA,              // DA (over)
    LBL_KILO_FEET,       // KF (over)
    LBL_FEET_MINUTE,     // FM (over)
    LBL_GROUND_TRACK,    // TK
    LBL_DESIRED_TRACK,   // DT
    LBL_DIRECT_TRACK,    // DK
    LBL_EXPECTED_ALT,    // AT
    LBL_TO,              // TO
    LBL_FROM,            // FM
    LBL_FROM_2,          // Fr
    LBL_TRUE,            // Tr
    LBL_LAT_LON,         // LL
    LBL_NORTH,           // N (little)
    LBL_SOUTH,           // S
    LBL_WEST,            // W
    LBL_EAST,            // E

    WPT_AIRPORT,       // A (little)
    WPT_AIRPORT_MIL,   // M (little)
    WPT_VOR,           // V (little)
    WPT_NDB,           // N (little)
    WPT_INTERSECTION,  // I (little)
    WPT_USER,          // U (little)

} tnl_font;

#endif