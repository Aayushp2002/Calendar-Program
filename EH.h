#pragma once
#include <string>
using namespace std;

class EH
{
private:
	string message;
public:
	string x();
	EH(string m = "ERROR: Invalid value; Try again.");
};