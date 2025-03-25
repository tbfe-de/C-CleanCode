#include "../gtest/gtest.h"

#include "SBuffer.h"

static char largebuffer[1000];
static char smallbuffer[10];

TEST(sbuf, large) {
    int nchars;
    SBuffer sbuf = SBuffer_INIT(largebuffer);
    nchars = SBprintf(&sbuf, "hello\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n", sbuf.static_buffer);
    nchars = SBprintf(&sbuf, "world\n");
    EXPECT_EQ(6, nchars);
    ASSERT_STREQ("hello\n"
                 "world\n", sbuf.static_buffer);
    nchars = SBprintf(&sbuf, "-----");
    EXPECT_EQ(5, nchars);
    ASSERT_STREQ("hello\n"
                 "world\n"
                 "-----", sbuf.static_buffer);
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
                 "wo", sbuf.static_buffer);
    nchars = SBprintf(&sbuf, "-----");
    EXPECT_EQ(5, nchars);
    ASSERT_STREQ("hello\n"
                 "wo", sbuf.static_buffer);
}
