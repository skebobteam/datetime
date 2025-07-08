#ifndef DATETIME_H_
#define DATETIME_H_

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

	long long GetSeconds() const;
	void AddDays(int day);
};

#endif // DATETIME_H_