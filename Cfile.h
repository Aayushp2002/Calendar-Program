#pragma once
#include <fstream>
#include "date.h"
#include <string>
#include <iostream>
using namespace std;

class Cfile
{
// private
	fstream myFile;
public:
	void deleteEvent(Date& date);
	void sortevents();
	void backwardSortEvents();
	bool isempty();
	void emptyfile(); void closefile();
	void displayevents();
	void openfile();
	void addevent(Date& date, string text);
	
	
	Cfile();
	fstream getfile();
};