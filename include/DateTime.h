#ifndef DATETIME_H_
#define DATETIME_H_

class DateTime {
private:
	long long seconds;

public:
	DateTime();
	DateTime(long long seconds);
	DateTime(int year, int month, int day);
	DateTime(DateTime& datetime);
};

#endif // DATETIME_H_