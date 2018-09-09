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

TEST(Includes, HasDataNoRebalance) {
    avl_tree<int> t;
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(4);
    t.insert(2);

    EXPECT_EQ(t.height(), 3);

    for (int i = 1; i <= 5; i++)
        ASSERT_TRUE(t.includes(i));
}

TEST(Includes, DoesNotHaveDataNoRebalance) {
    avl_tree<int> t;
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(4);
    t.insert(2);

    EXPECT_EQ(t.height(), 3);
    ASSERT_FALSE(t.includes(10));
}

TEST(Insert, RebalanceLeft) {
    avl_tree<int> t;
    for (int i = 1; i <= 10; i++)
        t.insert(i);

    EXPECT_EQ(t.height(), 4);

    for (int i = 1; i <= 10; i++) {
        std::cerr << i << std::endl;
        ASSERT_TRUE(t.includes(i));
    }
}

TEST(Insert, RebalanceRight) {
    avl_tree<int> t;

    for (int i = 10; i >= 1; i--)
        t.insert(i);

    EXPECT_EQ(t.height(), 4);
    
    for (int i = 1; i <= 10; i++)
        ASSERT_TRUE(t.includes(i));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}