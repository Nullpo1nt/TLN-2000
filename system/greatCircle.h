#ifndef _GREATCIRCLE_H_
#define _GREATCIRCLE_H_

#define TOLERANCE_CM 1.57e-009  // ~1 cm accuracy...
#define TOLERANCE_MM 1.0e-12    // ~0.06mm

typedef struct {
    double lat;
    double lon;
} LLPoint;

double spherical_distance(const LLPoint *p1, const LLPoint *p2);

double llrad_to_meteres(const LLPoint *p1, const LLPoint *p2, const double tolerance);

#endif /* _GREATCIRCLE_H_ */