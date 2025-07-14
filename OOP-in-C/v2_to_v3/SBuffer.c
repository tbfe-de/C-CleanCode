#include "SBuffer.h"

#include <assert.h>     /* assert (macro) */
#include <stdio.h>      /* vsnprintf (function) */
#include <stdarg.h>     /* va_start (macro) */
                        /* va_list (macro) */
                        /* va_end (macro) */
#include <string.h>     /* memset (function) */
                        /* strlen (function) */

/*
    :<---- sizeof array (pointed to by static_buffer) --->:
    : +-static_buffer                  reserved for final :
    : |              +-filled_point    '\0' termination | :
    : |              |                                  | :
    +-V+--+--+--+--+-V+--+--+--+--+--+--+--+--+--+--+--+V-+
    |h |e |l |l |o |\0|  |  |  |  |  |  |  |  |  |  |  |xx|
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    :              :                                   :
    :<--- used --->:<------------- avail ------------->:
    :<---------------- net_length -------------------->:
*/

int SBprintf(SBuffer* sb, const char *fmt, ...) {
    assert(sb != NULL);
    assert(fmt != NULL);

    char *const bspace = sb->filled_point;
    assert(bspace >= &sb->static_buffer[0]);
    assert(bspace <= &sb->static_buffer[sb->net_length]);

    const size_t used = bspace - sb->static_buffer;
    assert(used <= sb->net_length);

    const size_t avail = sb->net_length - used;
    assert((used + avail) == sb->net_length);

    va_list(ap);
    va_start(ap, fmt);
    const int added = vsnprintf(bspace, avail+1, fmt, ap);
    if (added > 0) sb->filled_point += strlen(bspace);
    assert(sb->filled_point <= &sb->static_buffer[sb->net_length]);
    va_end(ap);
    return added;
}

size_t SBstrlen(const SBuffer* sb) {
    return strlen(sb->static_buffer);
}

void SBclear(SBuffer* sb) {
    assert(sb != NULL);
    sb->static_buffer[0] = '\0';
    sb->filled_point = &sb->static_buffer[0];
}

void SBpurge(SBuffer* sb) {
    memset(sb->static_buffer, '\0', sb->net_length + 1);
    sb->filled_point = &sb->static_buffer[0];
}
