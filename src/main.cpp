#include "DateTime.h"
#include <iostream>

int main()
{
    bool continuation = true;
    int num_case;
    std::string separator = "\n-------------------------------------------------\n";
    std::cout << separator;
    std::cout << "\nMenu:\n   0: End program.\n   1: Create object (seconds).\n   2: Create object (year, month, day).\n   3: Create object (year, month, day, hour, minute, second).\n   4: Create object (string).\n   5: Compare two objects.\n   6: Add days.\n   7: Add months.\n   8: Add years.\n   9: Get day of the week.\n   10: Time now.\n   11: Print.\n";
    std::cout << separator;

    DateTime sampler;

    while (continuation) {
        try {
            std::cout << "\n\nEnter the case number: ";
            std::cin >> num_case;
            switch (num_case) {
                case 1: {
                    int seconds;
                    std::cout << "Enter the number (seconds): ";
                    std::cin >> seconds;
                    DateTime tmp(seconds);
                    sampler = tmp;
                    break;
                }
                case 2: {
                    int year, month, day;
                    std::cout << "Enter the numbers (year, month, day): ";
                    std::cin >> year >> month >> day;
                    DateTime tmp(year, month, day);
                    sampler = tmp;
                    break;
                }
                case 3: {
                    int year, month, day, hour, minute, second;
                    std::cout << "Enter the numbers (year, month, day, hour, minute, second): ";
                    std::cin >> year >> month >> day >> hour >> minute >> second;
                    DateTime tmp(year, month, day, hour, minute, second);
                    sampler = tmp;
                    break;
                }
                case 4: {
                    std::string str;
                    std::cout << "Enter the string (DD.MM.YY hh:mm:ss): ";
                    std::cin.ignore();
                    getline(std::cin, str);
                    DateTime tmp(str);
                    sampler = tmp;
                    break;
                }
                case 5: {
                    int seconds;
                    std::cout << "Enter the second object (seconds) to compare with sampler: ";
                    std::cin >> seconds;
                    DateTime tmp(seconds);
                    std::cout << sampler.Compare(tmp, sampler);
                    break;
                }
                case 6: {
                    int days;
                    std::cout << "Enter the number of days: ";
                    std::cin >> days;
                    sampler.AddDays(days);
                    break;
                }
                case 7: {
                    int months;
                    std::cout << "Enter the number of months: ";
                    std::cin >> months;
                    sampler.AddMonths(months);
                    break;
                }
                case 8: {
                    int years;
                    std::cout << "Enter the number of years: ";
                    std::cin >> years;
                    sampler.AddYears(years);
                    break;
                }
                case 9: {
                    std::cout << sampler.GetWeekDay();
                    break;
                }
                case 10: {
                    std::cout << sampler.GetNow().ToString();
                    break;
                }
                case 11: {
                    std::cout << sampler.ToString();
                    break;
                }
                default: {
                    continuation = false;
                    break;
                }
            }
        } catch(std::invalid_argument& e) {
            std::cout << "An invalid argument: " << e.what() << "\n";
        } catch (std::underflow_error& e) {
            std::cout << "A underflow error: " << e.what() << "\n";
        } catch(std::runtime_error& e) {
            std::cout << "A runtime error: " << e.what() << "\n";
        } catch(...) {
            std::cout << "An unknown error: " << "\n";
        }
    }
}