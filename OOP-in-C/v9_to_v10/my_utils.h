#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdlib.h> /* NULL (macro) */

_Bool range_checked_atol(const char* const str, long *const result,
                        long const min, long const max);
_Bool range_checked_atof(const char* const str, double* result,
                          double min, double max);

enum string_list_fail_bits {
    string_list_err_ok = 0,
    string_list_err_nn = 1<<0,
    string_list_err_lo = 1<<1,
    string_list_err_hi = 1<<2,
};

struct string_list_atol_ctl {
    long* pvalue;
    long minimum;
    long maximum;
    enum string_list_fail_bits fail;
};
size_t string_list_atol(const char* const str,
                        struct string_list_atol_ctl desc[]);

struct string_list_atof_ctl {
    double* pvalue;
    double minimum;
    double maximum;
    enum string_list_fail_bits fail;
};
size_t string_list_atof(const char* const str,
                        struct string_list_atof_ctl desc[]);

#endif // include guard
