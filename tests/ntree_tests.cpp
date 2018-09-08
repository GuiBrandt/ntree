#include <ntree.hpp>
#include <gtest/gtest.h>

TEST(Empty, IsEmpty) {
    n_tree<3, int> t;
    
    ASSERT_TRUE(t.empty());
}

TEST(Empty, NotEmpty) {
    n_tree<3, int> t;
    t.insert(0);
    
    ASSERT_FALSE(t.empty());
}

TEST(Insert, NoBranching) {
    n_tree<5, double> t;
    t.insert(0.0);
    t.insert(1.2);
    t.insert(2.4);
    t.insert(3.3);

    ASSERT_TRUE(t.is_leaf());
}

TEST(Insert, Branching) {
    n_tree<5, double> t;
    t.insert(0.0);
    t.insert(1.2);
    t.insert(2.4);
    t.insert(3.3);
    t.insert(7.65);
    t.insert(7.67);

    ASSERT_FALSE(t.is_leaf());
}

TEST(Insert, RepeatedSingleLevel) {
    n_tree<5, double> t;
    t.insert(0.0);

    ASSERT_THROW(t.insert(0.0), const char*);
}

TEST(Insert, RepeatedMultiLevel) {
    n_tree<5, double> t;
    t.insert(1.0);
    t.insert(4.0);
    t.insert(3.0);
    t.insert(5.0);
    t.insert(0.0);
    t.insert(2.0);

    ASSERT_THROW(t.insert(0.0), const char*);
}

TEST(Includes, HasDataSingleLevel) {
    n_tree<5, double> t;
    t.insert(0.0);

    ASSERT_TRUE(t.includes(0.0));
}

TEST(Includes, HasDataMultiLevel) {
    n_tree<5, double> t;
    t.insert(1.0);
    t.insert(4.0);
    t.insert(3.0);
    t.insert(5.0);
    t.insert(0.0);
    t.insert(2.0);

    ASSERT_TRUE(t.includes(0.0));
}

TEST(Includes, DoesNotHaveDataSingleLevel) {
    n_tree<5, double> t;
    t.insert(0.0);

    ASSERT_FALSE(t.includes(10.0));
}

TEST(Includes, DoesNotHaveMultiLevel) {
    n_tree<5, double> t;
    t.insert(1.0);
    t.insert(4.0);
    t.insert(3.0);
    t.insert(5.0);
    t.insert(0.0);
    t.insert(2.0);

    ASSERT_FALSE(t.includes(10.0));
}

TEST(Minimum, Empty) {
    n_tree<2, float> t;

    ASSERT_THROW(t.min(), const char*);
}

TEST(Minimum, NotEmpty) {
    n_tree<2, float> t;
    t.insert(1);

    ASSERT_NO_THROW(t.min());
}

TEST(Minimum, SingleLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(6);

    ASSERT_EQ(t.min(), 1);
}

TEST(Minimum, MultiLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.insert(3);
    t.insert(5);
    t.insert(1);

    ASSERT_EQ(t.min(), 1);
}

TEST(Maximum, Empty) {
    n_tree<2, float> t;

    ASSERT_THROW(t.max(), const char*);
}

TEST(Maximum, NotEmpty) {
    n_tree<2, float> t;
    t.insert(1);

    ASSERT_NO_THROW(t.max());
}

TEST(Maximum, SingleLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(6);

    ASSERT_EQ(t.max(), 6);
}

TEST(Maximum, MultiLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.insert(3);
    t.insert(5);
    t.insert(1);

    ASSERT_EQ(t.max(), 8);
}

TEST(Popleft, Empty) {
    n_tree<2, float> t;

    ASSERT_THROW(t.popleft(), const char*);
}

TEST(Popleft, NotEmpty) {
    n_tree<2, float> t;
    t.insert(1);

    ASSERT_NO_THROW(t.popleft());
}

TEST(Popleft, SingleLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(6);

    ASSERT_EQ(t.popleft(), 1);
    ASSERT_FALSE(t.includes(1));
}

TEST(Popleft, MultiLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.insert(3);
    t.insert(5);
    t.insert(1);

    ASSERT_EQ(t.popleft(), 1);
    ASSERT_FALSE(t.includes(1));
}

TEST(Pop, Empty) {
    n_tree<2, float> t;

    ASSERT_THROW(t.pop(), const char*);
}

TEST(Pop, NotEmpty) {
    n_tree<2, float> t;
    t.insert(1);

    ASSERT_NO_THROW(t.pop());
}

TEST(Pop, SingleLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(1);
    t.insert(6);

    ASSERT_EQ(t.pop(), 6);
    ASSERT_FALSE(t.includes(6));
}

TEST(Pop, MultiLevel) {
    n_tree<5, float> t;
    t.insert(4);
    t.insert(2);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.insert(3);
    t.insert(5);
    t.insert(1);

    ASSERT_EQ(t.pop(), 8);
    ASSERT_FALSE(t.includes(8));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();

    return 0;
}