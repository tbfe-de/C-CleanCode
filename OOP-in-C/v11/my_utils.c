#include "my_utils.h"

#include <ctype.h>      /* isspace (macro/function) */
#include <stdbool.h>    /* bool (macro) */
                        /* true (macro) */
                        /* false (macro) */
#include <stdlib.h>     /* strtol() */
                        /* strtod() */

bool range_checked_atol(const char* const s, long *const rp,
                        long const min, long const max) {
    char* pe;
    if (!s) return false;
    const long v = strtol(s, &pe, 10);
    if ((*pe != '\0')
     || (v < min)
     || (v > max)) return false;
    return *rp = v, true;
}

bool range_checked_atof(const char* const s, double *const rp,
                        double const min, double const max) {
    char* pe;
    if (!s) return false;
    const double v = strtod(s, &pe);
    if ((*pe != '\0')
     || (v < min)
     || (v > max)) return false;
    return *rp = v, true;
}

size_t string_list_atol(const char* const s,
                        struct string_list_atol_ctl desc[]) {
    if (!s) return 0;
    size_t parsed = 0;
    const char *parsepos = s;
    while (desc[parsed].pvalue != NULL) {
        while (*parsepos && isspace(*parsepos))
            ++parsepos;
        if (*parsepos == '\0')
            break;
        const char* const spos = parsepos;
        const long v = strtol(spos, (char**)&parsepos, 10);
        // avoid warning -----------^^^^^^^^
        if ((parsepos == spos)
         || (*parsepos && !isspace(*parsepos))) {
            desc[parsed].fail = string_list_err_nn;
            break;
        }
        if (v < desc[parsed].minimum) {
            desc[parsed].fail = string_list_err_lo;
            break;
        }
        if (v > desc[parsed].maximum) {
            desc[parsed].fail = string_list_err_hi;
            break;
        }
        *(desc[parsed].pvalue) = v;
        desc[parsed++].fail = string_list_err_ok;
    }
    return parsed;
}

size_t string_list_atof(const char* const s,
                        struct string_list_atof_ctl desc[]) {
    if (!s) return 0;
    size_t parsed = 0;
    const char *parsepos = s;
    while (desc[parsed].pvalue != NULL) {
        desc[parsed].fail = string_list_err_ok;
        while (*parsepos && isspace(*parsepos))
            ++parsepos;
        if (*parsepos == '\0')
            break;
        const char* const spos = parsepos;
        const double v = strtod(spos, (char**)&parsepos);
        // avoid warning -------------^^^^^^^^
        if ((parsepos == spos)
         || (*parsepos && !isspace(*parsepos))) {
            desc[parsed].fail = string_list_err_nn;
            break;
        }
        if (v < desc[parsed].minimum) {
            desc[parsed].fail = string_list_err_lo;
            break;
        }
        if (v > desc[parsed].maximum) {
            desc[parsed].fail = string_list_err_hi;
            break;
        }
        *(desc[parsed].pvalue) = v;
        desc[parsed++].fail = string_list_err_ok;
    }
    return parsed;
}
