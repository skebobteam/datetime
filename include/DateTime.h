#ifndef DATETIME_H_
#define DATETIME_H_

#include <string>

class DateTime {
private:
	long long seconds;

public:
	DateTime();
	DateTime(long long);
	DateTime(int, int, int);
	DateTime(const DateTime&);

	static bool IsLeap(int);
	static int DaysInMonth(int, int);
	static long long SecondsSinceChrist(int, int, int);
	DateTime& AddYears(int);

	long long GetSeconds() const;
	std::string GetWeekDay() const;
};

#endif // DATETIME_H_