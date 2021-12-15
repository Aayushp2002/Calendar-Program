#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date
{
//private
	int year = 2021;int day = 1;
	string text = "";
	int month = 1;

public:
	void setyear(int y);
	void settext(string txt);string gettext()const;
	string getmonth()const;
	int getmonthInt()const;
	int getyear()const;int getday()const;
	bool isLeapYear()const;string getDayOfWeek();
	string displayDate();
	void displayCalendar();
	void setmonth(int m);void setday(int d);

// operation overload
	friend bool operator!=(const Date& dateOne, const Date& dateTwo);friend int operator-(Date& date1, Date& date2);
	int operator>(const Date& anyDate);friend ostream& operator<<(ostream& osObject, Date& date);
//
	Date();Date(int m, int d, int y);
};