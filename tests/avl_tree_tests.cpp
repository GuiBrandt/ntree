#include <avl_tree.hpp>
#include <gtest/gtest.h>

TEST(Insert, Leaf) {
    avl_tree<int> t;
    t.insert(0);

    EXPECT_TRUE(t.is_leaf());
    ASSERT_TRUE(t.includes(0));
}

TEST(Insert, NoRebalance) {
    avl_tree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(0);

    EXPECT_EQ(t.height(), 2);
    ASSERT_TRUE(t.includes(0));
}

TEST(Insert, Rebalance) {
    avl_tree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    EXPECT_EQ(t.height(), 3);
    ASSERT_TRUE(t.includes(5));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}