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

	bool IsLeap(int) const;
	int DaysInMonth(int, int) const;
	long long SecondsSinceChrist(int, int, int) const;

	long long GetSeconds();
};

#endif // DATETIME_H_