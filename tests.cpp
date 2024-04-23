#include "whattotest.cpp"
#include <gtest/gtest.h>

TEST(maximTest, marePrimul) { 
    ASSERT_EQ(0, maxim(1,0));
    ASSERT_EQ(1, maxim(0,1));
    ASSERT_EQ(2, maxim(0,2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
