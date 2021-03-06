// You might have to adjust #include to be able to compile.
#include "stdafx.h"
using namespace std;

// Define how big your calendar should be.
// Minimum 21 (You can go lower, it shouldn't break but ugly), and must be divisible by 7 (it still shouldn't break).
#define CALENDAR_WIDTH 28

// function prototypes.
void displayMonthAndYear(string monthNames[], int month, int year);
void displayDaysOfWeek(string dayNames[]);
int displayMonthlyCalendar(int monthly[], int month, int startingDayOfWeek);
void centerizeText(string text, int width);
void renderPadding(int width);
int getFirstDayOfWeekOfYear(int year);
int checkLeapYear(int year);

int main()
{
	int monthly[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	string dayNames[] = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" };

	// Prompt for which calendar year to display.

	int year = 0;
	cout << "Enter year: ";
	cin >> year;
	cout << endl;

	// Check if the year is leap year then adjust February day span.

	monthly[1] = checkLeapYear(year) ? 29 : 28;

	// Determine the first day of the week of the year.

	int dayOfWeek = getFirstDayOfWeekOfYear(year);

	// Display monthly calendar for the year.
	for (int month = 0; month < 12; month++) {
		// Render month-year label.
		displayMonthAndYear(monthNames, month, year);
		cout << endl;

		// Render week day names.
		displayDaysOfWeek(dayNames);
		cout << endl;

		// Render monthly calendar.
		dayOfWeek = displayMonthlyCalendar(monthly, month, dayOfWeek);
		cout << endl;

		// Render calendar month bottom-margin.
		cout << endl;
	}

	return 0; // End program.
}

// Display the month-year label centerized to the calendar width.
void displayMonthAndYear(string monthNames[], int month, int year) {
	string monthName = monthNames[month];
	string yearName = to_string(year);

	centerizeText(monthName + " " + yearName, CALENDAR_WIDTH);
}

// Display the names of days of week.
void displayDaysOfWeek(string dayNames[]) {
	int width = CALENDAR_WIDTH / 7;

	for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++)
	{
		centerizeText(dayNames[dayOfWeek], width);
	}
}

// Display the calendar of the month.
// Return the following day of week for next month.
int displayMonthlyCalendar(int monthly[], int month, int startingDayOfWeek) {
	int width = CALENDAR_WIDTH / 7;
	int monthlyDays = monthly[month];

	// Render padding to offset until starting day of the week.

	int dayOfWeek;
	for (dayOfWeek = 0; dayOfWeek < startingDayOfWeek; dayOfWeek++)
	{
		renderPadding(width);
	}

	// Render days of month. One line per week.

	for (int day = 0; day < monthlyDays; day++, dayOfWeek++)
	{
		// If day of week is Sunday, start a new line.
		if (dayOfWeek > 6) {
			dayOfWeek = 0;
			cout << endl;
		}

		// Render the day of month.
		centerizeText(to_string(day + 1), width);
	}

	return dayOfWeek % 7;
}

// Centerize the text in the given width.
void centerizeText(string text, int width) {
	// Calculate the padding width for centerizing the text.
	double padding = (width - text.length()) / 2.0;

	// Render the text in between the paddings.
	renderPadding((int)floor(padding));
	cout << text;
	renderPadding((int)ceil(padding));
}

// Render empty space to fill the width to form padding.
void renderPadding(int width) {
	for (int i = 0; i < width; i++)
	{
		cout << " ";
	}
}

// Get the day of the week of the specified date.
// Return a value ranging from 0 until 6, where 0 is Sunday, 6 is Saturday.
//
// This function uses Gauss's algorithm: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gauss's_algorithm
int getFirstDayOfWeekOfYear(int year) {
	return (1 + (5 * ((year - 1) % 4)) + (4 * ((year - 1) % 100)) + (6 * ((year - 1) % 400))) % 7;
}

// Determine whether the specified year is a leap year.
// Return true if year is leap year; otherwise, false.
//
// A leap year is a year divisible by 4 (means no remainder after division),
// but not divisible by 100 unless it can be divisible by 400.
// https://en.wikipedia.org/wiki/Leap_year#Algorithm
int checkLeapYear(int year) {
	// This logic from your friend is incorrect.
	// Your friend should have tested his function on some sample...
	// Year 1600 / 2000 / 2400 should be leap year.
	// But because the years divisible by 100, it always become false.
	/*if (year % 4 == 0 || year % 400 == 0) {
		if (year % 100 == 0)
			return false;
		else
			return true;
	}
	return false;*/

	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}