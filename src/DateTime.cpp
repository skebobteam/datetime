#include "DateTime.h"

DateTime::DateTime() {
	seconds = 0LL;
}

DateTime::DateTime(long long secs) {
	Validate(secs);

	seconds = secs;
}

DateTime::DateTime(int year, int month, int day) {
	Validate(year, month, day);

	seconds = SecondsSinceChrist(year, month, day);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int secs) {
	Validate(year, month, day, hour, minute, secs);

	seconds = SecondsSinceChrist(year, month, day, hour, minute, secs);
}

DateTime::DateTime(const DateTime& obj) {
	seconds = obj.seconds;
}

long long DateTime::GetSeconds() const {
	return seconds;
}

void DateTime::Validate(long long secs) {
	if (secs < 0) {
    	throw "Error: Negative number of seconds!";
    }
}

void DateTime::Validate(int year, int month, int day) {
	if (year < 1) {
		throw "Error: Incorrect year!";
	}

	if (month < 1 || month > 12) {
		throw "Error: Incorrect month!";
	}

	if (day < 1 || DaysInMonth(year, month) < day) {
		throw "Error: Incorrect day!";
	}
}

void DateTime::Validate(int year, int month, int day, int hour, int minute, int secs) {
	Validate(year, month, day);
    
	if (hour < 0 || hour >= 24) {
		throw "Error: Incorrect hour!";
	}

	if (minute < 0 || minute >= 60) {
		throw "Error: Incorrect minute!";
	}

	if (secs < 0 || secs >= 60) {
		throw "Error: Incorrect second!";
	}
}

bool DateTime::Compare(const DateTime& obj1, const DateTime& obj2) {
	bool answer = false;
	if (obj1.seconds == obj2.seconds) {
		answer = true;
	}
	return answer;
}


bool DateTime::IsLeap(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int DateTime::DaysInMonth(int year, int month) {
	if (month == 2) {
		return IsLeap(year) ? 29 : 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	} else {
		return 31;
	}
}

long long DateTime::SecondsSinceChrist(int year, int month, int day) {
	long long days = 0;

	for (int y = 1; y < year; y++) {
		days += IsLeap(y) ? 366 : 365;
	}

	for (int m = 1; m < month; m++) {
		days += DaysInMonth(year, m);
	}

	days += (day - 1);

	return days * 86400LL;
}

long long DateTime::SecondsSinceChrist(int year, int month, int day, int hour, int minute, int secs) {
    return SecondsSinceChrist(year, month, day) + hour * 3600LL + minute * 60LL + secs;
}

void DateTime::AddDays(int day) {
	const long long second_of_day = day * 86400LL;

	if (seconds + second_of_day >= 0) {
		seconds += second_of_day;
	} else {
		throw "Error: Can't subtract that many days.";
	}
}
