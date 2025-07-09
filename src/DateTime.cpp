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

	if (day < 1 || DaysInMonth(year, month) < day) {
		throw "Error: Incorrect day!";
	}

	seconds = SecondsSinceChrist(year, month, day);
}

DateTime::DateTime(const DateTime& obj) {
	seconds = obj.seconds;
}

long long DateTime::GetSeconds() const {
	return seconds;
}

std::string DateTime::GetWeekDay() const {
	long long total_days = seconds / 86400LL;
	static const std::string weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return weekdays[(total_days + 1) % 7];
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
        days += DaysInMonth(m, year);
    }

    days += (day - 1);

    return days * 86400LL;
}

DateTime& DateTime::AddYears(int years) {
	if (years == 0) {
		return *this;
	}

	long long total_days = seconds / 86400LL;
	int weekday = (total_days + 1) % 7;

	int year = 1;
	int remaining_days = total_days;

	while (true) {
		int days_in_year = IsLeap(year) ? 366 : 365;
		if (remaining_days < days_in_year) {
			break;
		}
		remaining_days -= days_in_year;
		++year;
	}

	int month = 1;
	for (; month <= 12; ++month) {
		int days_in_month = DaysInMonth(year, month);
		if (remaining_days < days_in_month) {
			break;
		}
		remaining_days -= days_in_month;
	}

	int day = remaining_days + 1;

	year += years;

	if (year < 1) { //проверка не ушли ли мы во время до н.э.
		throw "Error: Year cannot be less than 1!";
	}

	if (month == 2 && day == 29 && !IsLeap(year)) {
		day = 28;
	}

	seconds = SecondsSinceChrist(year, month, day);

	long long new_days = seconds / 86400LL;
	int new_weekday = (new_days + 1) % 7;
	if (new_weekday != weekday) {
		throw "Error: Weekday mismatch!";
	}

	return *this;
}
