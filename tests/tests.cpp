#include <gtest/gtest.h>
#include "DateTime.h"

TEST(DateTimeTest, DefaultConstructor) {
    ASSERT_EQ(DateTime().GetSeconds(), 0);
}

TEST(DateTimeTest, SecondsConstructor_Valid) {
    EXPECT_EQ(DateTime(1).GetSeconds(), 1);
}

TEST(DateTimeTest, SecondsConstructor_Negative) {
    EXPECT_ANY_THROW(DateTime(-1).GetSeconds());
    EXPECT_NO_THROW(DateTime(1).GetSeconds());
}

TEST(DateTimeTest, DateConstructor_Valid) {
    EXPECT_GT(DateTime(2, 3, 4).GetSeconds(), 0);
}

TEST(DateTimeTest, DateConstructor_Throw) {
    EXPECT_NO_THROW(DateTime(1, 1, 1));
}

TEST(DateTimeTest, DateConstructor_InvalidYear) {
    EXPECT_ANY_THROW(DateTime(-1, 1, 1));
}

TEST(DateTimeTest, DateConstructor_InvalidMonth) {
    EXPECT_ANY_THROW(DateTime(1, -1, 1));
    EXPECT_ANY_THROW(DateTime(1, 13, 1));
}

TEST(DateTimeTest, DateConstructor_InvalidDay) {
    EXPECT_NO_THROW(DateTime(1, 1, 15));
    EXPECT_ANY_THROW(DateTime(1, 1, -1));
    EXPECT_ANY_THROW(DateTime(1, 1, 32));
    EXPECT_ANY_THROW(DateTime(1, 2, 29));
    EXPECT_ANY_THROW(DateTime(1, 4, 31));
}

TEST(DateTimeTest, CopyConstructor) {
    EXPECT_EQ(DateTime(DateTime(20)).GetSeconds(), 20);
}

TEST(DateTimeTest, Compare) {
    EXPECT_TRUE(DateTime::Compare(DateTime(1), DateTime(1)));
    EXPECT_FALSE(DateTime::Compare(DateTime(1), DateTime(2)));
}

TEST(DateTimeTest, IsLeap) {
    EXPECT_TRUE(DateTime::IsLeap(4));
    EXPECT_FALSE(DateTime::IsLeap(3));
    EXPECT_TRUE(DateTime::IsLeap(2000));
    EXPECT_FALSE(DateTime::IsLeap(1900));
}

TEST(DateTimeTest, DaysInMonth) {
    EXPECT_EQ(DateTime::DaysInMonth(1, 3), 31);
    EXPECT_EQ(DateTime::DaysInMonth(1, 4), 30);
    EXPECT_EQ(DateTime::DaysInMonth(1, 2), 28);
    EXPECT_EQ(DateTime::DaysInMonth(4, 2), 29);
}

TEST(DateTimeTest, SecondsSinceChrist) {
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 1), 0);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 2), 86400);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 3), 172800);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 11), 864000);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}