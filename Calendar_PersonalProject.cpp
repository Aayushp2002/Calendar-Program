//==========================================================
//
// Title:                Personal Calendar App
// Develope:			 Aayush Patel
// Date completed:       
//
//
//==========================================================
#include <fstream>// For files
#include <cstdlib> // defines a collection of functions and macros to facilitate efficient, high-performing, standardized code
#include <iomanip> // For formatting
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
// header files including
#include "EH.h"
#include "Cfile.h"
#include "date.h" 

using namespace std; // std::cout --> cout only

void displayBorder()
{
	char line = 240;
	for (int i = 0; i < 100; i++)
		cout << line;
	cout << endl << endl;
}

void recordEvent(Date& date)
{
	Cfile myFile;
	myFile.openfile();
	string userInputText;
	cout << "Enter a description of the event: ";
	cin.ignore(1000, '\n');
	getline(cin, userInputText);
	myFile.addevent(date, userInputText);
	cout << endl;
	cout << "Event recorded!" << endl;
	myFile.closefile();
}

void verifyPassword()
{
	//fstream file to reserve password
	fstream passwordFile;
	passwordFile.open("passwordStorage.txt", ios::in);

	// take password string if created
	string password;
	getline(passwordFile, password);

	// close file
	passwordFile.close();

	// check if password DNE
	if (password.empty())
	{
		// open file to reserve new password
		passwordFile.open("passwordStorage.txt", ios::out);

		// ask user for password
		cout << "Create password: ";
		cin >> password;

		// password is stored in file
		passwordFile << password;

		// close file
		passwordFile.close();
	}
	// open file to take password
	passwordFile.open("passwordStorage.txt", ios::in);
	getline(passwordFile, password);
	// close file
	passwordFile.close();

	// ask user for password
	string userInput;
	cout << "Enter Password: ";
	cin >> userInput;

	// keep on asking for password until correct
	while (userInput != password)
	{
		cout << "Access denied." << endl << "Reenter password: ";
		cin >> userInput;
	}
	cout << "Access granted!" << endl;

	displayBorder();
}

int displayMenuOption()
{
	int userInputMenu;
	cout << "Which course of action would you like this calendar to perform?" << endl;
	cout << "\tPress [1] to display date on calendar." << endl;
	cout << "\tPress [2] to record an event in file." << endl;
	cout << "\tPress [3] to delete an event from file." << endl;
	cout << "\tPress [4] to display events from file." << endl;
	cout << "\tPress [5] to compare two dates." << endl;
	cout << "\tPress [6] to empty all events from file." << endl;
	cout << "\tPress [7] to sort all events in file." << endl;
	cout << "\tPress [9] to quit program." << endl;
	cin >> userInputMenu;
	return userInputMenu;
}

void executeProgram()
{
	int userInput;
	userInput = displayMenuOption();
	cout << endl;
	//validation loop
	while (userInput != 9)
	{
		if (userInput == 1)
		{
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//input validations with error
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw EH("ERROR: Invalid month value");
				else
				{
					date1.setmonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw EH("ERROR: Invalid year value");
					else
					{
						date1.setyear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw EH("ERROR: Invalid day value");
							else
							{
								//display date1
								date1.setday(userInputDay);
								cout << endl << date1 << endl;
								date1.displayCalendar();
							}

						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw EH("ERROR: Invalid day value");
							else
							{
								//display date1
								date1.setday(userInputDay);
								cout << endl << date1 << endl;
								date1.displayCalendar();
							}
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw EH("ERROR: Invalid day value");
								else
								{
									//display date1
									date1.setday(userInputDay);
									cout << endl << date1 << endl;
									date1.displayCalendar();
								}
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw EH("ERROR: Invalid day value");
								else
								{
									//display date1
									date1.setday(userInputDay);
									cout << endl << date1 << endl;
									date1.displayCalendar();
								}
							}
						}
					}
				}
			}
			catch (EH errorObj)
			{
				cout << errorObj.x() << endl;
			}

			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 2)
		{
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//input validations with error 
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw EH("ERROR: Invalid month value");
				else
				{
					date1.setmonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw EH("ERROR: Invalid year value");
					else
					{
						date1.setyear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw EH("ERROR: Invalid day value");
							else
							{
								date1.setday(userInputDay);
								recordEvent(date1);
							}
						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw EH("ERROR: Invalid day value");
							else
							{
								date1.setday(userInputDay);
								recordEvent(date1);
							}
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw EH("ERROR: Invalid day value");
								else
								{
									date1.setday(userInputDay);
									recordEvent(date1);
								}
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw EH("ERROR: Invalid day value");
								else
								{
									date1.setday(userInputDay);
									recordEvent(date1);
								}
							}
						}
					}
				}
			}
			catch (EH errorObj)
			{
				cout << errorObj.x() << endl;
			}
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 3)
		{
			Date date1;
			int userInputMonth, userInputDay, userInputYear;
			cout << "Enter date(MM DD YYYY) seperate with spaces: ";
			cin >> userInputMonth >> userInputDay >> userInputYear;
			//input validations with error 
			try
			{
				if (userInputMonth < 1 || userInputMonth > 12)
					throw EH("ERROR: Invalid month value");
				else
				{
					date1.setmonth(userInputMonth);
					if (userInputYear < 1583 || userInputYear > 9999)
						throw EH("ERROR: Invalid year value");
					else
					{
						date1.setyear(userInputYear);
						if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
						{
							if (userInputDay < 1 || userInputDay > 31)
								throw EH("ERROR: Invalid day value");
							else
								date1.setday(userInputDay);
						}
						else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
						{
							if (userInputDay < 1 || userInputDay > 30)
								throw EH("ERROR: Invalid day value");
							else
								date1.setday(userInputDay);
						}
						else if (userInputMonth == 2)
						{
							if (date1.isLeapYear() == true)
							{
								if (userInputDay < 1 || userInputDay > 29)
									throw EH("ERROR: Invalid day value");
								else
									date1.setday(userInputDay);
							}
							else if (date1.isLeapYear() == false)
							{
								if (userInputDay < 1 || userInputDay > 28)
									throw EH("ERROR: Invalid day value");
								else
									date1.setday(userInputDay);
							}
						}
					}
				}
			}
			catch (EH errorObj)
			{
				cout << errorObj.x() << endl;
			}
			Cfile myFile;
			myFile.deleteEvent(date1);
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 4)
		{
			Cfile myFile;
			myFile.displayevents();
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 5)
		{
			//  two Date objects
			Date date1;
			Date date2;
			// sentenial loops to get dates

			bool userInputPass1 = false;
			bool userInputPass2 = false;
			while (userInputPass1 == false)
			{
				int userInputMonth, userInputDay, userInputYear;
				cout << "Enter first date(MM DD YYYY) seperate with spaces: ";
				cin >> userInputMonth >> userInputDay >> userInputYear;
				//input validations with error
				try
				{
					if (userInputMonth < 1 || userInputMonth > 12)
						throw EH("ERROR: Invalid month value");
					else
					{
						date1.setmonth(userInputMonth);
						if (userInputYear < 1583 || userInputYear > 9999)
							throw EH("ERROR: Invalid year value");
						else
						{
							date1.setyear(userInputYear);
							if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
							{
								if (userInputDay < 1 || userInputDay > 31)
									throw EH("ERROR: Invalid day value");
								else
								{
									date1.setday(userInputDay);
									userInputPass1 = true;
								}
							}
							else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
							{
								if (userInputDay < 1 || userInputDay > 30)
									throw EH("ERROR: Invalid day value");
								else
								{
									date1.setday(userInputDay);
									userInputPass1 = true;
								}
							}
							else if (userInputMonth == 2)
							{
								if (date1.isLeapYear() == true)
								{
									if (userInputDay < 1 || userInputDay > 29)
										throw EH("ERROR: Invalid day value");
									else
									{
										date1.setday(userInputDay);
										userInputPass1 = true;
									}
								}
								else if (date1.isLeapYear() == false)
								{
									if (userInputDay < 1 || userInputDay > 28)
										throw EH("ERROR: Invalid day value");
									else
									{
										date1.setday(userInputDay);
										userInputPass1 = true;
									}
								}
							}
						}
					}
				}
				catch (EH errorObj)
				{
					cout << errorObj.x() << endl;
				}
			}
			while (userInputPass2 == false)
			{
				int userInputMonth, userInputDay, userInputYear;
				cout << "Enter second date(MM DD YYYY) seperate with spaces: ";
				cin >> userInputMonth >> userInputDay >> userInputYear;
				//input validations with error
				try
				{
					if (userInputMonth < 1 || userInputMonth > 12)
						throw EH("ERROR: Invalid month value");
					else
					{
						date2.setmonth(userInputMonth);
						if (userInputYear < 1583 || userInputYear > 9999)
							throw EH("ERROR: Invalid year value");
						else
						{
							date2.setyear(userInputYear);
							if ((userInputMonth == 1) || (userInputMonth == 3) || (userInputMonth == 5) || (userInputMonth == 7) || (userInputMonth == 8) || (userInputMonth == 10) || (userInputMonth == 12))
							{
								if (userInputDay < 1 || userInputDay > 31)
									throw EH("ERROR: Invalid day value");
								else
								{
									date2.setday(userInputDay);
									userInputPass2 = true;
								}
							}
							else if ((userInputMonth == 4) || (userInputMonth == 6) || (userInputMonth == 9) || (userInputMonth == 11))
							{
								if (userInputDay < 1 || userInputDay > 30)
									throw EH("ERROR: Invalid day value");
								else
								{
									date2.setday(userInputDay);
									userInputPass2 = true;
								}
							}
							else if (userInputMonth == 2)
							{
								if (date2.isLeapYear() == true)
								{
									if (userInputDay < 1 || userInputDay > 29)
										throw EH("ERROR: Invalid day value");
									else
									{
										date2.setday(userInputDay);
										userInputPass2 = true;
									}
								}
								else if (date2.isLeapYear() == false)
								{
									if (userInputDay < 1 || userInputDay > 28)
										throw EH("ERROR: Invalid day value");
									else
									{
										date2.setday(userInputDay);
										userInputPass2 = true;
									}
								}
							}
						}
					}
				}
				catch (EH errorObj)
				{
					cout << errorObj.x() << endl;
				}
			}
			int compareDates = date1 > date2;

			cout << "First Date: " << date1 << endl;
			cout << "Second Date: " << date2 << endl;

			if (compareDates == 2)
				cout << "Dates are the same." << endl;

			int daysApart = date1 - date2;
			cout << "They are " << daysApart << " days apart." << endl;

			// input from menu
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 6)
		{
			char userInputChar;
			cout << "Are you sure you would like to empty your file? (y/n): ";
			cin >> userInputChar;
			while (userInputChar != 'y' && userInputChar != 'n')
			{
				cout << "(y/n): ";
				cin >> userInputChar;
			}
			if (userInputChar == 'y')
			{
				Cfile myFile;
				myFile.emptyfile();
			}
			displayBorder();
			// input from menu
			userInput = displayMenuOption();
			cout << endl;
		}
		else if (userInput == 7)
		{
			Cfile myFile;
			char userInputChar;
			cout << "How would you like to sort your events?\n\tPress [1] for chronological.\n\tPress [2] for reverse chronological.\n";
			cin >> userInputChar;
			while (userInputChar != '1' && userInputChar != '2')
			{
				cout << "(1 or 2): ";
				cin >> userInputChar;
			}
			if (userInputChar == '1')
				myFile.sortevents();
			else if (userInputChar == '2')
				myFile.backwardSortEvents();
			displayBorder();
			userInput = displayMenuOption();
			cout << endl;
		}
		else
		{
			// input from menu
			cout << userInput << " is not an option.  Please enter a number listed." << endl;
			userInput = displayMenuOption();
		}
	}
	//program closer
	cout << "Calendar App terminated." << endl;
	displayBorder();
}

int main()
{
	//program header
	cout << "Welcome to Calendar App!" << endl;
	displayBorder();

	//calling functions
	verifyPassword();
	executeProgram();
}
