#include "Five.h"
#include <gtest/gtest.h>

TEST(FiveTest, Basic){
    Five a("4");
    Five b("1");
    Five c=a.add(b);
    EXPECT_EQ(c.to_string(),"10");
}
