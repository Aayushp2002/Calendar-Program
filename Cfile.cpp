// include headers
#include "Cfile.h"
#include "EH.h" 

#include <iostream> // For cin, cout, and system
#include <iomanip> // For format
#include <vector> // For vector 
#include <sstream> // For file handle
const int COLFMT1 = 45;
const int COLFMT2 = 65;



void Cfile::openfile()
{
    // Open file (read and write)
    myFile.open("Events.txt", ios::app);
    // Check for error
    if (!myFile.is_open())
        cout << "ERROR: Unable to open file." << endl;
    else
        cout << "Successfully opened File." << endl;
}

fstream Cfile::getfile()
{
    fstream myFile("Events.txt");
    return myFile;
}

void Cfile::addevent(Date& date, string text)
{
    myFile << setw(COLFMT1) << left << date.displayDate() << setw(COLFMT2) << left << text << '\n';
}

void Cfile::closefile()
{
    if (!myFile.is_open())
        cout << "ERROR: File not open." << endl;
    else
    {
        myFile.close();
        cout << "File saved and closed." << endl;
    }
}

void Cfile::emptyfile()
{
    
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();
    cout << "All content erased!" << endl;
}

bool Cfile::isempty()
{
    if (!getfile())
        return 0;
    bool is_Empty = getfile().peek() == EOF;
    return is_Empty;
}



void Cfile::sortevents()
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    vector<string> translateVect;
    Date dateFromFile;
    string description;
    vector<Date> dates;

    
    myFile.open("Events.txt");
    string line;
    while (getline(myFile, line))
    {
        
        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setmonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setday(stoi(extractDay));

        dateFromFile.setyear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.settext(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    //Bubble sort for ordered dates
    Date temp;
    for (int passes = 1; passes < dates.size(); passes++)
    {
        for (int index = 0; index < dates.size() - passes; index++)
        {
            if (dates.at(index) > dates.at(index + 1))
            {
                temp = dates.at(index);
                dates.erase(dates.begin() + index);
                dates.insert(dates.begin() + index + 1, temp);
            }
        }
    }
    myFile.close();

    //empty file
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();

    //ask user sorted events into file
    myFile.open("Events.txt", ios::app);
    for (int i = 0; i < dates.size(); i++)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].gettext() << endl;
    myFile.close();
    cout << "\nAll events are sorted!" << endl;
}

void Cfile::backwardSortEvents()
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    
    vector<string> translateVect;
    Date dateFromFile;
    string description;
   
    vector<Date> dates;

    
    myFile.open("Events.txt");
    string line;
    while (getline(myFile, line))
    {
        
        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setmonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setday(stoi(extractDay));

        dateFromFile.setyear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.settext(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    
    Date temp;
    for (int passes = 1; passes < dates.size(); passes++)
    {
        for (int index = 0; index < dates.size() - passes; index++)
        {
            if (dates.at(index) > dates.at(index + 1))
            {
                temp = dates.at(index);
                dates.erase(dates.begin() + index);
                dates.insert(dates.begin() + index + 1, temp);
            }
        }
    }
    myFile.close();

    
    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();

    
    myFile.open("Events.txt", ios::app);
    for (int i = dates.size() - 1; i >= 0; i--)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].gettext() << endl;
    myFile.close();
    cout << "\nAll events are sorted!" << endl;
}





Cfile::Cfile() {};

void Cfile::displayevents()
{
    // Check if file is empty
    if (isempty() == true)
        cout << "There is no data to display." << endl;
    else if (isempty() == false)
    {
        // show header
        cout << setw(40) << left << "Date" << setw(60) << left << "Description" << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
        // show all content from file
        myFile.open("Events.txt", std::ofstream::in);
        if (myFile.is_open())
            cout << myFile.rdbuf();
        // close file
        myFile.close();
        cout << endl;
    }
}

void Cfile::deleteEvent(Date& date)
{
    const string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    vector<string> translateVect;
    Date dateFromFile;
    string description;
    vector<Date> dates;


    myFile.open("Events.txt");
    string line;
    while (getline(myFile, line))
    {

        istringstream iss(line);
        string sub;
        while (iss >> sub)
            translateVect.push_back(sub);
        for (int i = 0; i < 12; i++)
        {
            if (translateVect[0] == months[i])
                dateFromFile.setmonth(i + 1);
        }

        string extractDay = translateVect[1];
        extractDay.erase(extractDay.end() - 3, extractDay.end());
        dateFromFile.setday(stoi(extractDay));

        dateFromFile.setyear(stoi(translateVect[2]));

        for (int i = 4; i < translateVect.size(); i++)
            description += translateVect[i] + " ";
        dateFromFile.settext(description);
        description.clear();

        dates.push_back(dateFromFile);

        translateVect.clear();
    }

    int equal;
    for (int index = 0; index < dates.size(); index++)
    {
        equal = date > dates.at(index);
        if (equal == 2)
            dates.erase(dates.begin() + index);
    }

    myFile.close();


    myFile.open("Events.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();


    myFile.open("Events.txt", ios::app);
    for (int i = 0; i < dates.size(); i++)
        myFile << setw(COLFMT1) << left << dates[i].displayDate() << setw(COLFMT2) << left << dates[i].gettext() << endl;
    myFile.close();
    cout << "Event(s) successfully removed from file!" << endl;
}