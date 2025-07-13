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

TEST(DateTimeTest, StringDateConstructor_Valid) {
    EXPECT_GT(DateTime("01.01.0001 01:01:01").GetSeconds(), 0);
    EXPECT_EQ(DateTime("01.07.2025 18:30:45").GetSeconds(), DateTime(2025, 7, 1, 18, 30, 45).GetSeconds());
    EXPECT_EQ(DateTime("01.01.1970 00:00:00").GetSeconds(), 62135596800LL);
}

TEST(DateTimeTest, StringDateConstructor_Throw) {
    EXPECT_NO_THROW(DateTime("01.01.0001 01:01:01"));
    EXPECT_ANY_THROW(DateTime("1 January 2000 00:11:22"));
    EXPECT_ANY_THROW(DateTime("invalid string"));
    EXPECT_ANY_THROW(DateTime(""));
}

TEST(DateTimeTest, CopyConstructor) {
    EXPECT_EQ(DateTime(DateTime(20)).GetSeconds(), 20);
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

TEST(DateTimeTest, GetNameOfDayOfWeek) {
    EXPECT_EQ(DateTime(1, 1, 1).GetNameOfDayOfWeek(), std::string("Monday"));
    EXPECT_EQ(DateTime(1, 1, 2).GetNameOfDayOfWeek(), std::string("Tuesday"));
    EXPECT_EQ(DateTime(1, 1, 3).GetNameOfDayOfWeek(), std::string("Wednesday"));
    EXPECT_EQ(DateTime(1, 1, 4).GetNameOfDayOfWeek(), std::string("Thursday"));
    EXPECT_EQ(DateTime(1, 1, 5).GetNameOfDayOfWeek(), std::string("Friday"));
    EXPECT_EQ(DateTime(1, 1, 6).GetNameOfDayOfWeek(), std::string("Saturday"));
    EXPECT_EQ(DateTime(1, 1, 7).GetNameOfDayOfWeek(), std::string("Sunday"));
    EXPECT_EQ(DateTime(1, 1, 8).GetNameOfDayOfWeek(), std::string("Monday"));
    EXPECT_EQ(DateTime(1000, 2, 1).GetNameOfDayOfWeek(), std::string("Saturday"));
    EXPECT_EQ(DateTime(2025, 3, 1).GetNameOfDayOfWeek(), std::string("Saturday"));
}

TEST(DateTimeTest, GetNow) {
    EXPECT_NO_THROW({
        time_t before = static_cast<long long>(time(nullptr)) + 62135596800LL;
        DateTime now = DateTime::GetNow();
        time_t after = static_cast<long long>(time(nullptr)) + 62135596800LL;
        EXPECT_GE(now.GetSeconds(), before);
        EXPECT_LE(now.GetSeconds(), after);
    });
}

TEST(DateTimeTest, ToString) {
    EXPECT_EQ(DateTime().ToString(), "01.01.0001 00:00:00");
    EXPECT_EQ(DateTime("1.1.1 1:1:1").ToString(), "01.01.0001 01:01:01");
    EXPECT_EQ(DateTime(55, 10, 5).ToString(), "05.10.0055 00:00:00");
    EXPECT_EQ(DateTime(123, 7, 10, 5, 4, 3).ToString(), "10.07.0123 05:04:03");
    EXPECT_EQ(DateTime("31.12.2023 23:59:59").ToString(), "31.12.2023 23:59:59");
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

TEST(DateTimeTest, AddMonths_Valid1) {
    DateTime dt(1, 1, 31, 11, 22, 33);
    dt.AddMonths(37);
    EXPECT_EQ(dt.GetSeconds(), DateTime(4, 2, 29, 11, 22, 33).GetSeconds());
    dt.AddMonths(-24);
    EXPECT_EQ(dt.GetSeconds(), DateTime(2, 2, 28, 11, 22, 33).GetSeconds());
    dt.AddMonths(50);
    EXPECT_EQ(dt.GetSeconds(), DateTime(6, 4, 28, 11, 22, 33).GetSeconds());
}

TEST(DateTimeTest, AddMonths_Valid2) {
    DateTime dt(1, 1, 31, 11, 22, 33);
    dt.AddMonths(1);
    EXPECT_EQ(dt.GetSeconds(), DateTime(1, 2, 28, 11, 22, 33).GetSeconds());
    dt.AddMonths(0);
    EXPECT_EQ(dt.GetSeconds(), DateTime(1, 2, 28, 11, 22, 33).GetSeconds());
}

TEST(DateTimeTest, AddMonths_Throw) {
    EXPECT_ANY_THROW(DateTime(5, 3, 1, 11, 22, 33).AddMonths(-51));
    EXPECT_NO_THROW(DateTime(5, 3, 1, 11, 22, 33).AddMonths(-50));
}

TEST(DateTimeTest, AddYears_Valid1) {
    DateTime dt(1900, 5, 15, 11, 22, 33);
    dt.AddYears(105);
    EXPECT_EQ(dt.GetSeconds(), DateTime(2005, 5, 15, 11, 22, 33).GetSeconds());
    dt.AddYears(-228);
    EXPECT_EQ(dt.GetSeconds(), DateTime(1777, 5, 15, 11, 22, 33).GetSeconds());
}

TEST(DateTimeTest, AddYears_Valid2) {
    DateTime dt(4, 2, 29, 11, 22, 33);
    dt.AddYears(1);
    EXPECT_EQ(dt.GetSeconds(), DateTime(5, 2, 28, 11, 22, 33).GetSeconds());
    dt.AddYears(0);
    EXPECT_EQ(dt.GetSeconds(), DateTime(5, 2, 28, 11, 22, 33).GetSeconds());
}

TEST(DateTimeTest, AddYears_Throw) {
    EXPECT_ANY_THROW(DateTime().AddYears(-1));
    EXPECT_ANY_THROW(DateTime(5, 3, 1, 11, 22, 33).AddYears(-5));
    EXPECT_NO_THROW(DateTime(5, 3, 1, 11, 22, 33).AddYears(-4));
}

TEST(DateTimeTest, Compare) {
    EXPECT_TRUE(DateTime::Compare(DateTime(1), DateTime(1)));
    EXPECT_FALSE(DateTime::Compare(DateTime(1), DateTime(2)));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}