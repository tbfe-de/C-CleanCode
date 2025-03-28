#include "../gtest/gtest.h"

#include "SBuffer.h"

#include <string.h> /* memcmp */

static char largebuffer[1000];
static char smallbuffer[10];

TEST(sbuf, large) {
    int nchars;
    SBuffer sbuf = SBuffer_INIT(largebuffer);
    EXPECT_EQ(0, SBstrlen(&sbuf));

    nchars = SBprintf(&sbuf, "hello\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n", sbuf.static_buffer);
    EXPECT_EQ(6, SBstrlen(&sbuf));

    nchars = SBprintf(&sbuf, "world\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n"
                 "world\n", sbuf.static_buffer);
    EXPECT_EQ(12, SBstrlen(&sbuf));

    nchars = SBprintf(&sbuf, "-----");
    EXPECT_EQ(5, nchars);
    ASSERT_STREQ("hello\n"
                 "world\n"
                 "-----", sbuf.static_buffer);
    EXPECT_EQ(17, SBstrlen(&sbuf));

    static const char nulled[sizeof largebuffer];
    SBclear(&sbuf);
    EXPECT_EQ(0, SBstrlen(&sbuf));
    EXPECT_FALSE(memcmp(sbuf.static_buffer, nulled, sizeof nulled) == 0);
    SBpurge(&sbuf);
    EXPECT_TRUE(memcmp(sbuf.static_buffer, nulled, sizeof nulled) == 0);
}

TEST(sbuf, small) {
    int nchars;
    SBuffer sbuf = SBuffer_INIT(smallbuffer);
    nchars = SBprintf(&sbuf, "hello\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n", sbuf.static_buffer);
    nchars = SBprintf(&sbuf, "world\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n"
                 "wor", sbuf.static_buffer);
    nchars = SBprintf(&sbuf, "-----");
    EXPECT_EQ(5, nchars);
    ASSERT_STREQ("hello\n"
                 "wor", sbuf.static_buffer);
}
