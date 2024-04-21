#include "whattotest.cpp"
#include <gtest/gtest.h>

TEST(maximTest, marePrimul) { 
    ASSERT_EQ(1, maxim(1,0));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
