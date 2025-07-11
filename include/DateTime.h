#ifndef DATETIME_H_
#define DATETIME_H_

#include <ctime>

#include <string>
#include <sstream>

#include <stdexcept>

class DateTime {
private:
	long long seconds;
	static const std::string weekdays[7];

public:
	DateTime();
	DateTime(long long);
	DateTime(int, int, int);
	DateTime(int, int, int, int, int, int);
	DateTime(const std::string&);
	DateTime(const DateTime&);

	static void Validate(long long);
	static void Validate(int, int, int);
	static void Validate(int, int, int, int, int, int);
	static void Validate(const std::istringstream&);

	static bool IsLeap(int);
	static int DaysInMonth(int, int);
	
	static long long SecondsSinceChrist(int, int, int);
	static long long SecondsSinceChrist(int, int, int, int, int, int);
	
	long long GetSeconds() const;
	std::string GetWeekDay() const;
	static DateTime GetNow();
	void GetDate(int&, int&, int&) const;

	void SetSeconds(long long);
  
	void AddDays(int);
	void AddMonths(int);
  
	static bool Compare(const DateTime&, const DateTime&);
};

#endif // DATETIME_H_