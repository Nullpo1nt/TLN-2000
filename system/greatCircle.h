#ifndef _GREATCIRCLE_H_
#define _GREATCIRCLE_H_

#include <cmath>
#include <stdio.h>

namespace greatcircle
{

inline const double mToNM = 0.000539957;

// WGS84
inline const double a = 6378137.0;      // m, a = semi-major axis
inline const double b = 6356752.314245; // m, b = semi-minor axis
inline const double f = 1 / 298.257223563;

inline const double tolerance_cm = 1.57e-009; // ~1 cm accuracy...
inline const double tolerance_mm = 1.0e-12;   // ~0.06mm

typedef struct
{
    double lat;
    double lon;
} LLPoint;

static double spherical_distance(const LLPoint *p1, const LLPoint *p2);

static double llrad_to_meteres(const LLPoint *p1, const LLPoint *p2, const double tolerance = tolerance_cm);

} // namespace greatcircle

#endif /* _GREATCIRCLE_H_ */