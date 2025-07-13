#include "DateTime.h"

const std::string DateTime::NAMES_OF_DAYS_OF_WEEK[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

DateTime::DateTime() : DateTime(0LL) {}

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

DateTime::DateTime(const std::string& datetime) {
	char dot, colon, space;
	int day, month, year, hour, minute, secs;

	std::istringstream ss(datetime);

	ss >> day >> dot >> month >> dot >> year;
	ss.get(space);
	ss >> hour >> colon >> minute >> colon >> secs;

	Validate(ss);
	Validate(year, month, day, hour, minute, secs);
	seconds = SecondsSinceChrist(year, month, day, hour, minute, secs);
}

DateTime::DateTime(const DateTime& obj) {
	seconds = obj.seconds;
}

void DateTime::Validate(long long secs) {
	if (secs < 0) {
		throw std::invalid_argument("Negative number of seconds!");
	}
}

void DateTime::Validate(int year, int month, int day) {
	if (year < 1) {
		throw std::invalid_argument("Incorrect year!");
	}

	if (month < 1 || month > 12) {
		throw std::invalid_argument("Incorrect month!");
	}

	if (day < 1 || DaysInMonth(year, month) < day) {
		throw std::invalid_argument("Incorrect day!");
	}
}

void DateTime::Validate(int year, int month, int day, int hour, int minute, int secs) {
	Validate(year, month, day);
	
	if (hour < 0 || hour >= 24) {
		throw std::invalid_argument("Incorrect hour!");
	}

	if (minute < 0 || minute >= 60) {
		throw std::invalid_argument("Incorrect minute!");
	}

	if (secs < 0 || secs >= 60) {
		throw std::invalid_argument("Incorrect second!");
	}
}

void DateTime::Validate(const std::istringstream& ss) {
	if (ss.fail()) {
		throw std::invalid_argument("Invalid date format (DD.MM.YYYY HH:mm:ss)!");
	}
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

long long DateTime::GetSeconds() const {
	return seconds;
}

int DateTime::GetDayOfWeek() const {
	long long total_days = seconds / 86400LL;
	return (total_days + 1) % 7;
}

std::string DateTime::GetNameOfDayOfWeek() const {
	return NAMES_OF_DAYS_OF_WEEK[GetDayOfWeek()];
}

DateTime DateTime::GetNow() {
	time_t now_1970 = time(nullptr);

	if (now_1970 == -1) {
		throw std::runtime_error("Failed to get current time!");
	} else {
		const long long seconds_SC_to_1970 = 62135596800LL;

		long long actual_date_in_seconds = static_cast<long long>(now_1970) + seconds_SC_to_1970;
		return DateTime(actual_date_in_seconds);
	}
}

void DateTime::GetDate(int& year, int& month, int& day) const {
	int remaining_days = seconds / 86400;
	year = 1;
	bool year_found = false;
	while (!year_found) {
		int days_in_year = IsLeap(year) ? 366 : 365;
		if (remaining_days < days_in_year) {
			year_found = true;
		} else {
			remaining_days -= days_in_year;
			++year;
		}
	}

	month = 1;
	bool month_found = false;
	while (!month_found && month <= 12) {
		int days_in_month = DaysInMonth(year, month);
		if (remaining_days < days_in_month) {
			month_found = true;
		} else {
			remaining_days -= days_in_month;
			++month;
		}
	}

	day = remaining_days + 1;
}

void DateTime::SetSeconds(long long secs) {
	Validate(secs);

	seconds = secs;
}

std::string DateTime::ToString() const {
	int day, month, year, hour, minute, secs, remaining = seconds % 86400;
	std::ostringstream ss;

	GetDate(year, month, day);
	hour = remaining / 3600;
	minute = (remaining % 3600) / 60;
	secs = remaining % 60;

	ss << std::setfill('0')
		<< std::setw(2) << day << "." << std::setw(2) << month << "." << std::setw(4) << year << " "
		<< std::setw(2) << hour << ":" << std::setw(2) << minute << ":" << std::setw(2) << secs;

	return ss.str();
}

void DateTime::AddDays(int day) {
	const long long second_of_day = day * 86400LL;

	if (seconds + second_of_day >= 0) {
		seconds += second_of_day;
	} else {
		throw std::underflow_error("Can't subtract that many days.");
	}
}

void DateTime::AddMonths(int months) {
	if (months != 0) {
		int year, month, day;
		GetDate(year, month, day);

		int total_months = (year - 1) * 12 + (month - 1) + months;
		if (total_months < 0) {
			throw std::underflow_error("Can't subtract that many months!");
		}

		year = (total_months / 12) + 1;
		month = (total_months % 12) + 1;

		int max_day = DaysInMonth(year, month);
		if (day > max_day) {
			day = max_day;
		}

		long long remaining_seconds = seconds % 86400LL;

		seconds = SecondsSinceChrist(year, month, day) + remaining_seconds;
	}
}

void DateTime::AddYears(int years) {
	if (years == 0) {
		return;
	}

	int year, month, day;
	GetDate(year, month, day);

	year += years;

	if (year < 1) { 
		throw std::underflow_error("Year cannot be less than 1!");
	}

	int max_day = DaysInMonth(year, month);
	if (day > max_day) {
		day = max_day;
	}

	long long remaining_seconds = seconds % 86400LL;
	seconds = SecondsSinceChrist(year, month, day) + remaining_seconds;
}

bool DateTime::Compare(const DateTime& obj1, const DateTime& obj2) {
	bool answer = false;
	if (obj1.seconds == obj2.seconds) {
		answer = true;
	}
	return answer;
}
