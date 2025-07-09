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

TEST(DateTimeTest, FullDateConstructor_Valid) {
    EXPECT_GT(DateTime(2, 3, 4, 5, 6, 7).GetSeconds(), 0);
}

TEST(DateTimeTest, FullDateConstructor_Throw) {
    EXPECT_NO_THROW(DateTime(1, 1, 1, 0, 0, 0));
    EXPECT_NO_THROW(DateTime(9999, 12, 31, 23, 59, 59));
}

TEST(DateTimeTest, FullDateConstructor_InvalidHour) {
    EXPECT_ANY_THROW(DateTime(1, 1, 1, -1, 1, 1));
    EXPECT_ANY_THROW(DateTime(1, 1, 1, 24, 1, 1));
}

TEST(DateTimeTest, FullDateConstructor_InvalidMinute) {
    EXPECT_ANY_THROW(DateTime(1, 1, 1, 1, -1, 1));
    EXPECT_ANY_THROW(DateTime(1, 1, 1, 1, 60, 1));
}

TEST(DateTimeTest, FullDateConstructor_InvalidSecs) {
    EXPECT_ANY_THROW(DateTime(1, 1, 1, 1, 1, -1));
    EXPECT_ANY_THROW(DateTime(1, 1, 1, 1, 1, 60));
}

TEST(DateTimeTest, CopyConstructor) {
    EXPECT_EQ(DateTime(DateTime(20)).GetSeconds(), 20);
}

TEST(DateTimeTest, GetWeekDay) {
    EXPECT_EQ(DateTime(1, 1, 1).GetWeekDay(), std::string("Monday"));
    EXPECT_EQ(DateTime(1, 1, 2).GetWeekDay(), std::string("Tuesday"));
    EXPECT_EQ(DateTime(1, 1, 3).GetWeekDay(), std::string("Wednesday"));
    EXPECT_EQ(DateTime(1, 1, 4).GetWeekDay(), std::string("Thursday"));
    EXPECT_EQ(DateTime(1, 1, 5).GetWeekDay(), std::string("Friday"));
    EXPECT_EQ(DateTime(1, 1, 6).GetWeekDay(), std::string("Saturday"));
    EXPECT_EQ(DateTime(1, 1, 7).GetWeekDay(), std::string("Sunday"));
    EXPECT_EQ(DateTime(1, 1, 8).GetWeekDay(), std::string("Monday"));
    EXPECT_EQ(DateTime(1000, 2, 1).GetWeekDay(), std::string("Saturday"));
    EXPECT_EQ(DateTime(2025, 3, 1).GetWeekDay(), std::string("Saturday"));
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
    EXPECT_EQ(DateTime::SecondsSinceChrist(2, 1, 2), 31622400);
    EXPECT_EQ(DateTime::SecondsSinceChrist(2, 2, 1), 34214400);
    EXPECT_EQ(DateTime::SecondsSinceChrist(3, 1, 1), 63072000);
}

TEST(DateTimeTest, FullSecondsSinceChrist) {
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 1, 0, 0, 0), 0);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 1, 1, 0, 0), 3600);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 1, 0, 1, 0), 60);
    EXPECT_EQ(DateTime::SecondsSinceChrist(1, 1, 1, 0, 0, 1), 1);
}

TEST(DateTimeTest, AddDays_Valid) {
    DateTime dt;
    dt.AddDays(1);
    EXPECT_EQ(dt.GetSeconds(), 86400);
    dt.AddDays(-1);
    EXPECT_EQ(dt.GetSeconds(), 0);
}

TEST(DateTimeTest, AddDays_Throw) {
    EXPECT_ANY_THROW(DateTime(86399).AddDays(-1));
    EXPECT_NO_THROW(DateTime(86400).AddDays(-1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}