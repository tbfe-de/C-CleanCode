#ifndef SBUFFER_H
#define SBUFFER_H

#include <stddef.h> /* size_t (typedef) */

typedef struct SBuffer_ {
    char *static_buffer;
    size_t net_length;
    char *filled_point;
} SBuffer;

#define SBuffer_INIT(charray)\
    { charray, (sizeof charray) - 1, &charray[0] }

size_t SB_strlen(const SBuffer*);
void SB_clear(SBuffer*);
int SBprintf(SBuffer*, const char*, ...);

#endif // include guard
