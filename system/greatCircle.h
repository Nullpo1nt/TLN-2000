#ifndef _GREATCIRCLE_H_
#define _GREATCIRCLE_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define TOLERANCE_CM 1.57e-009  // ~1 cm accuracy...
#define TOLERANCE_MM 1.0e-12    // ~0.06mm

#define M_TO_NM(x) (x / 1852)

typedef struct {
    double lat;
    double lon;
} gc_llp_t;

// Distance (meters) and bearing (+- radians)
typedef struct {
    double distance;
    double bearing;
} gc_solution_t;

// #define DMS_TO_DD(d, m, s) (d + (m / 60) + (sec / 3600))

double gc_distance_nm(const gc_solution_t *solution);
double gc_bearing_deg(const gc_solution_t *solution);
void gc_distance_bearing(gc_solution_t *solution, const gc_llp_t *p1, const gc_llp_t *p2, const double tolerance);

#endif /* _GREATCIRCLE_H_ */