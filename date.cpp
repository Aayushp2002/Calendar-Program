#include "date.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "EH.h"
using namespace std;

void Date::setday(int d)
{
	try
	{
		if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
		{
			if (d < 1 || d > 31)
				throw EH("ERROR: Invalid day value");
			else
				day = d;
		}
		else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
		{
			if (d < 1 || d > 30)
				throw EH("ERROR: Invalid day value");
			else
				day = d;
		}
		else if (month == 2)
		{
			if (isLeapYear())
			{
				if (d < 1 || d > 29)
					throw EH("ERROR: Invalid day value");
				else
					day = d;
			}
			else if (isLeapYear() == false)
			{
				if (d < 1 || d > 28)
					throw EH("ERROR: Invalid day value");
				else
					day = d;
			}
		}
	}
	catch (EH errorObject)
	{
		cout << errorObject.x() << endl;
	}
}
///
void Date::setmonth(int m)
{
	try
	{
		if (m < 1 || m > 12)
			throw EH("Error: Invalid month value");
		else
			month = m;
	}
	catch (EH errorObject)
	{
		cout << errorObject.x() << endl;
	}
}
///

void Date::setyear(int y)
{
	try
	{
		if (y < 1583 || y > 9999)
			throw EH("ERROR: Invalid year value");
		else
			year = y;
	}
	catch (EH errorObject)
	{
		cout << errorObject.x() << endl;
	}
}

void Date::settext(string txt)
{
	text = txt;
}

string Date::gettext()const
{
	return text;
}



int Date::getmonthInt()const
{
	return month;
}

string Date::getmonth()const
{
	const string monthName[12] =
	{ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return monthName[month - 1];
}

int Date::getyear()const
{
	return year;
}

int Date::getday()const
{
	return day;
}



string Date::getDayOfWeek()
{
	const string daysOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	//evaluate year code ,year to array

	int yearArra[4];
	int y = this->getyear();
	for (int i = 3; i >= 0; i--)
	{
		yearArra[i] = y % 10;
		y /= 10;
	}
	//array into two ints
	//YcYy 4024 ---> 40/ 24
	int Yc = 0;
	int Yy = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			Yc *= 10;
			Yc += yearArra[i];
		}
		else if (i == 2 || i == 3)
		{
			Yy *= 10;
			Yy += yearArra[i];
		}
	}
	//calculate century code
	if (Yc % 4 == 0)
		Yc = 0;
	else if (Yc % 4 == 1)
		Yc = 5;
	else if (Yc % 4 == 2)
		Yc = 3;
	else if (Yc % 4 == 3)
		Yc = 1;
	int y7 = Yy % 7;
	int y4 = Yy / 4;
	int Y = Yc + y7 + y4;

	//evaluate day code
	int D = this->getday() % 7;

	//evaluate month code
	int monthCode[12] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	if (this->isLeapYear() == true)
	{
		monthCode[0] = 5;
		monthCode[1] = 1;
	}
	else if (this->isLeapYear() == false)
	{
		monthCode[0] = 6;
		monthCode[1] = 2;
	}
	int M = monthCode[this->month - 1];

	
	string theDayOfTheWeek = daysOfWeek[(D + M + Y) % 7];
	return theDayOfTheWeek;
}

bool Date::isLeapYear()const
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

string Date::displayDate()
{
	string o = "th";
	if ((day == 1) || (day == 21) || (day == 31))
		o = "st";
	else if ((day == 2) || (day == 22))
		o = "nd";
	else if ((day == 3) || (day == 23))
		o = "rd";
	string sDay = to_string(getday());
	string sYear = to_string(getyear());
	return getmonth() + " " + sDay + o + ", " + sYear + " (" + getDayOfWeek() + ")";
}

void Date::displayCalendar()
{
	const int COLFMT1 = 14 + (getmonth().length() / 2);
	const int COLFMT2 = 14 - (getmonth().length() / 2);
	const int COLFMT3 = 4;
	const int COLFMT4 = 28;

	
	string month_ = getmonth();
	transform(month_.begin(), month_.end(), month_.begin(), [](unsigned char c) {return toupper(c); });

	
	cout << setfill(char(175)) << setw(COLFMT1) << right << month_ << setfill(char(174)) << setw(COLFMT2) << left << char(174) << endl;

	
	string dayOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	for (int i = 0; i < 7; i++)
		cout << setfill(char(32)) << setw(COLFMT3) << left << dayOfTheWeek[i];
	cout << endl;

	
	int yearArra[4];
	int y = this->getyear();
	for (int i = 3; i >= 0; i--)
	{
		yearArra[i] = y % 10;
		y /= 10;
	}
	int Yc = 0;
	int Yy = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			Yc *= 10;
			Yc += yearArra[i];
		}
		else if (i == 2 || i == 3)
		{
			Yy *= 10;
			Yy += yearArra[i];
		}
	}
	
	if (Yc % 4 == 0)
		Yc = 0;
	else if (Yc % 4 == 1)
		Yc = 5;
	else if (Yc % 4 == 2)
		Yc = 3;
	else if (Yc % 4 == 3)
		Yc = 1;
	int y7 = Yy % 7;
	int Y4 = Yy / 4;
	int Y = Yc + y7 + Y4;

	
	int monthCode[12] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	if (this->isLeapYear() == true)
	{
		monthCode[0] = 5;
		monthCode[1] = 1;
	}
	else if (this->isLeapYear() == false)
	{
		monthCode[0] = 6;
		monthCode[1] = 2;
	}
	int M = monthCode[this->month - 1];

	
	//replace d with 1 because 1 is the first day of every month and 1 mod 7 equals 1
	int firstDayOfMonthIndex = (1 + M + Y) % 7;

	
	int numberOfDaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	//Check for leap year
	if (this->isLeapYear() == true)
		numberOfDaysInMonth[1] = 29;
	else if (this->isLeapYear() == false)
		numberOfDaysInMonth[1] = 28;
	int lastDayOfMonthIndex = numberOfDaysInMonth[this->month - 1];
	lastDayOfMonthIndex += firstDayOfMonthIndex;

	
	int ind = 1;
	int dayIndex = 1;
	for (int week = 1; week <= 6; week++)
	{
		while (ind <= (week * 7))
		{
			if ((ind <= firstDayOfMonthIndex) || (ind > lastDayOfMonthIndex))
				cout << "    ";
			else
			{
				if (dayIndex <= 9)
				{
					if (this->getday() == dayIndex)
						cout << "|" << dayIndex << "| ";
					else
						cout << " " << dayIndex << "  ";
				}
				else if (10 <= dayIndex)
				{
					if (this->getday() == dayIndex)
						cout << "|" << dayIndex << "|";
					else
						cout << " " << dayIndex << " ";
				}
				dayIndex++;
			}
			ind++;
		}
		cout << endl;
	}
}



int Date::operator>(const Date& anyDate)
{

	if (year > anyDate.year)
		return 1;//true
	else if (year == anyDate.year)
	{
		if (month > anyDate.month)
			return 1;
		else if (month == anyDate.month)
		{
			if (day > anyDate.day)
				return 1;
			else if (day == anyDate.day)
				return 2;//equal
			else
				return 0;//false
		}
		else
			return 0;
	}
	else
		return 0;
}
ostream& operator<<(ostream& osObject, Date& date)
{
	string o = "th";
	if ((date.getday() == 1) || (date.getday() == 21) || (date.getday() == 31))
		o = "st";
	else if ((date.getday() == 2) || (date.getday() == 22))
		o = "nd";
	else if ((date.getday() == 3) || (date.getday() == 23))
		o = "rd";
	osObject << date.getDayOfWeek() << ", " << date.getmonth() << " " << date.getday() << o << ", " << date.getyear();
	return osObject;
}

bool operator!=(const Date& dateOne, const Date& dateTwo)
{
	if (dateOne.getyear() == dateTwo.getyear())
	{
		if (dateOne.getmonth() == dateTwo.getmonth())
		{
			if (dateOne.getday() == dateTwo.getday())
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

int operator-(Date& date1, Date& date2)
{
	Date oldDate;
	Date newDate;
	int isOlder = date2 > date1;
	if (isOlder == 0)
	{
		oldDate = date2;
		newDate = date1;
	}
	else if (isOlder == 1)
	{
		oldDate = date1;
		newDate = date2;
	}
	else if (isOlder == 2)
		return 0;

	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysInt = oldDate.getday();
	int monthsInt = oldDate.getmonthInt();
	int yearsInt = oldDate.getyear();
	int daysDifference = 0;
	while (oldDate != newDate)
	{
		// Check if leap year
		if (oldDate.isLeapYear() == true)
			months[1] = 29;
		else
			months[1] = 28;

		daysInt++;
		daysDifference++;
		if (daysInt > months[monthsInt - 1])
		{
			daysInt = 1;
			oldDate.setday(daysInt);
			monthsInt++;
			if (monthsInt > 12)
			{
				monthsInt = 1;
				oldDate.setmonth(monthsInt);
				yearsInt++;
				oldDate.setyear(yearsInt);
			}
			else
				oldDate.setmonth(monthsInt);
		}
		else
			oldDate.setday(daysInt);
	}
	return daysDifference;
}

Date::Date(){}

Date::Date(int m, int d, int y)
{
	if (y >= 1583 && y <= 9999)
		year = y;
	else
		year = 2021;
	if (m >= 1 && m <= 12)
		month = m;
	else
		month = 1;
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		if ((d >= 1) && (d <= 31))
			day = d;
		else
			day = 1;
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		if ((d >= 1) && (d <= 30))
			day = d;
		else
			day = 1;
	}
	else if (month == 2)
	{
		if (isLeapYear())
		{
			if ((d >= 1) && (d <= 29))
				day = d;
			else
				day = 1;
		}
		else
		{
			if ((d >= 1) && (d <= 28))
				day = d;
			else
				day = 1;
		}
	}
}