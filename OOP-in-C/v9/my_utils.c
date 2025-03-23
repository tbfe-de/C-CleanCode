#include "my_utils.h"

#include <stdbool.h>
#include <stdlib.h>

bool range_checked_atol(const char* const s, long *const rp,
                        long const min, long const max) {
    const char* pe;
    const long v = strtol(s, &pe, 10);
    if ((*pe != '\0')
     || (v < min)
     || (v > max)) return false;
    return *rp = v, true;
}

bool range_checked_atof(const char* const s, double *const rp,
                        double const min, double const max) {
    const char* pe;
    const double v = strtod(s, &pe);
    if ((*pe != '\0')
     || (v < min)
     || (v > max)) return false;
    return *rp = v, true;
}
