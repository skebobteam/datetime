#include "DateTime.h"

DateTime::DateTime() {
	seconds = 0LL;
}

DateTime::DateTime(long long secs) {
	if (secs >= 0) {
		seconds = secs; 
	} else {
    	throw "Error: Negative number of seconds!";
    }
}

DateTime::DateTime(int year, int month, int day) {
	if (year < 0) {
		throw "Error: Incorrect year!";
	}

	if (month < 1 || month > 12) {
		throw "Error: Incorrect month!";
	}

	if (DaysInMonth(year, month) != day) {
		throw "Error: Incorrect day!";
	}

	seconds = SecondsSinceChrist(year, month, day);
}

DateTime::DateTime(const DateTime& obj) {
	seconds = obj.seconds;
}

bool DateTime::IsLeap(int year) const {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int DateTime::DaysInMonth(int year, int month) const {
	if (month == 2) {
        return IsLeap(year) ? 29 : 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
	} else {
        return 31;
	}
}

long long DateTime::SecondsSinceChrist(int year, int month, int day) const {
	long long days = 0;

    for (int y = 1; y < year; y++) {
        days += IsLeap(y) ? 366 : 365;
    }

    for (int m = 1; m < month; m++) {
        days += DaysInMonth(m, year);
    }

    days += (day - 1);

    return days * 86400LL;
}
