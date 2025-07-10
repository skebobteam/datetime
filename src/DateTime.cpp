#include "DateTime.h"

const std::string DateTime::weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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

std::string DateTime::GetWeekDay() const {
	long long total_days = seconds / 86400LL;
	return weekdays[(total_days + 1) % 7];
}

void DateTime::Validate(long long secs) {
	if (secs < 0) {
		throw std::invalid_argument("Error: Negative number of seconds!");
	}
}

void DateTime::Validate(int year, int month, int day) {
	if (year < 1) {
		throw std::invalid_argument("Error: Incorrect year!");
	}

	if (month < 1 || month > 12) {
		throw std::invalid_argument("Error: Incorrect month!");
	}

	if (day < 1 || DaysInMonth(year, month) < day) {
		throw std::invalid_argument("Error: Incorrect day!");
	}
}

void DateTime::Validate(int year, int month, int day, int hour, int minute, int secs) {
	Validate(year, month, day);
	
	if (hour < 0 || hour >= 24) {
		throw std::invalid_argument("Error: Incorrect hour!");
	}

	if (minute < 0 || minute >= 60) {
		throw std::invalid_argument("Error: Incorrect minute!");
	}

	if (secs < 0 || secs >= 60) {
		throw std::invalid_argument("Error: Incorrect second!");
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
		throw std::underflow_error("Error: Can't subtract that many days.");
	}
}

void DateTime::AddMonths(int months) {
	if (months != 0){
        long long total_days = seconds / 86400LL;
        int remaining_days = total_days;

        int year = 1;
        bool year_found = false;
        while (!year_found) {
            int days_in_year = IsLeap(year) ? 366 : 365;
            if (remaining_days < days_in_year) {
                year_found = true;
            }
            else {
                remaining_days -= days_in_year;
                ++year;
            }
        }

        int month = 1;
        bool month_found = false;
        while (!month_found && month <= 12) {
            int days_in_month = DaysInMonth(year, month);
            if (remaining_days < days_in_month) {
                month_found = true;
            }
            else {
                remaining_days -= days_in_month;
                ++month;
            }
        }

        int day = remaining_days + 1;

        int total_months = (year - 1) * 12 + (month - 1) + months;
        if (total_months < 0) {
            throw std::underflow_error("Error: total_months cannot be negative!");
        }

        year = total_months / 12;
        month = (total_months % 12) + 1;

	    int max_day = DaysInMonth(year, month);
        if (day > max_day) {
            day = max_day;
        }

        long long remaining_seconds = seconds % 86400LL;

	    seconds = SecondsSinceChrist(year, month, day) + remaining_seconds;
	}
}
