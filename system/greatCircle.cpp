#include "greatCircle.h"

namespace greatcircle
{

double spherical_distance(const LLPoint *p1, const LLPoint *p2)
{
    const double phi1 = 0.5 * M_PI - p1->lat;
    const double phi2 = 0.5 * M_PI - p2->lat;
    const double r = 0.5 * (6378137 + 6356752); // mean radius in meters
    const double t = sin(phi1) * sin(phi2) * cos(p1->lon - p2->lon) + cos(phi1) * cos(phi2);
    return r * acos(t);
}

/**
 * Vincenty’s Inverse Formula
 * FAA Order 8260.54A, Appendix 2
 */
double llrad_to_meteres(const LLPoint *p1, const LLPoint *p2, const double tolerance /* = tolerance_cm */)
{
    // Values needed outside the iterative portion
    double cos2Alpha, cos_2sigmam, lamda0, sigma;

    // reduced latitude, defined by tan U = (1 - f) tan phi
    const double U1 = atan((1.0 - f) * tan(p1->lat));
    const double U2 = atan((1.0 - f) * tan(p2->lat));

    const double L = p2->lon - p1->lon;

    // Line 13, First approximation of lamda
    double lamda = L;

    do
    {
        // sqrt of Line 14
        const double sinSigma =
            sqrt(
                pow(cos(U2) * sin(lamda), 2.0) +
                pow((cos(U1) * sin(U2)) - (sin(U1) * cos(U2) * cos(lamda)), 2.0));

        // Line 15
        const double cosSigma =
            (sin(U1) * sin(U2)) + (cos(U1) * cos(U2) * cos(lamda));

        // Line 16
        sigma = atan2(sinSigma, cosSigma);

        // Line 17
        const double sinAlpha =
            (cos(U1) * cos(U2) * sin(lamda)) / sin(sigma);

        // Line 18
        cos2Alpha = 1.0 - (sinAlpha * sinAlpha);
        cos_2sigmam =
            cos(sigma) - ((2.0 * sin(U1) * sin(U2)) / cos2Alpha);

        // Line 10
        const double C =
            (f / 16.0) *
            cos2Alpha *
            (4.0 + (f * (4.0 - (3.0 * cos2Alpha))));

        lamda0 = lamda; // Store lamda

        // Line 11
        const double square =
            cos_2sigmam + (C * cosSigma *
                           (-1.0 + (2.0 * pow(cos_2sigmam, 2))));
        const double bracket = sigma + (C * sinSigma * square);
        lamda = L + (1.0 - C) * f * sinAlpha * bracket;
    } while (fabs(lamda0 - lamda) > tolerance);

    const double u2 = cos2Alpha * (((a - b) * (a + b)) / (b * b));

    // Line 3
    const double A =
        1.0 + (u2 / 16384.0) *
                  (4096.0 + (u2 *
                             (-768.0 + (u2 *
                                        (320.0 - (175.0 * u2))))));

    // Line 4
    const double B =
        (u2 / 1024.0) *
        (256.0 + (u2 *
                  (-128.0 + (u2 *
                             (74.0 - (47.0 * u2))))));

    // Line 6
    const double deltaSigma =
        B * sin(sigma) *
        (cos_2sigmam +
         ((B / 4.0) * (cos(sigma) * ((2.0 * pow(cos_2sigmam, 2.0)) - 1.0)) -
          ((B / 6.0) * (cos_2sigmam *
                        ((4.0 * pow(sin(sigma), 2.0) - 3.0)) *
                        ((4.0 * pow(cos_2sigmam, 2.0) - 3.0))))));

    // Line 19
    const double s = b * A * (sigma - deltaSigma);

    return s;
}

} // namespace greatcircle

// int main(int argc, const char *argv[])
// {
//     // KBOS
//     const greatcircle::LLPoint p = {
//         42.3629444f * 0.017453293f,
//         -71.0063889f * 0.017453293f};

//     // KLAX
//     const greatcircle::LLPoint q = {
//         33.9424964 * 0.017453293f,
//         -118.4080486 * 0.017453293f};

//     printf("%f m (mm)\n", llrad_to_meteres(&p, &q, greatcircle::tolerance_mm));
//     printf("%f m (cm)\n", llrad_to_meteres(&p, &q, greatcircle::tolerance_cm));
//     printf("%f m (m)\n", llrad_to_meteres(&p, &q, greatcircle::tolerance_m));
//     printf("%f m\n", spherical_distance(&p, &q));

//     const greatcircle::LLPoint newportRI = {41.49008 * 0.017453293, -71.312796 * 0.017453293};
//     const greatcircle::LLPoint clevelandOH = {41.499498 * 0.017453293, -81.695391 * 0.017453293};

//     printf("%f m (mm)\n", llrad_to_meteres(&newportRI, &clevelandOH, greatcircle::tolerance_mm));
//     printf("%f m (cm)\n", llrad_to_meteres(&newportRI, &clevelandOH, greatcircle::tolerance_cm));
//     printf("%f m (m)\n", llrad_to_meteres(&newportRI, &clevelandOH, greatcircle::tolerance_m));
//     printf("%f m\n", spherical_distance(&newportRI, &clevelandOH));
//     const greatcircle::LLPoint x = {
//         39.152501 * 0.017453293f,
//         -84.412977 * 0.017453293f};

//     // KLAX
//     const greatcircle::LLPoint y = {
//         39.152505 * 0.017453293f,
//         -84.412946 * 0.017453293f};

//     printf("%f m (mm)\n", llrad_to_meteres(&x, &y, greatcircle::tolerance_mm));
//     printf("%f m (cm)\n", llrad_to_meteres(&x, &y, greatcircle::tolerance_cm));
//     printf("%f m (m)\n", llrad_to_meteres(&x, &y, greatcircle::tolerance_m));
//     printf("%f m\n", spherical_distance(&x, &y));
//     return 0;
// }
