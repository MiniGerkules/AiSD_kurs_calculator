#include "../h-files/prototypes.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//-------------------------------------------------------------
// Description of functions
//-------------------------------------------------------------

/*
	Entering an expression from a file
	std::string name -- the name of the file from which information is read
*/
string input_from_file(string name)
{
	ifstream fin;									// Class object for reading information from a file
	string expression;								// Read expression

	fin.open(name + ".txt");
	if (!fin.is_open())
		throw domain_error("Unable to open file!");

	getline(fin, expression);
	fin.close();
		
	return expression;
}

/*
	Function defining there is a substring in a string with a specific character
	std::string first -- first line (in which we are looking)
	std::string second -- second line (which we are looking for)
	size_t index -- the index of the element of the first line from which to start looking for the second line
*/
bool my_find(string first, string second, size_t index)
{
	bool answer;								// The program's response to match strings
	size_t size;								// Second line size
	size_t i;									// For loop parameter

	if (index < second.length())
		answer = false;
	else
	{
		answer = true;
		size = second.length();
		for (i = 0; (i < size) && answer; i++)
			if (tolower(first[index - i - 1]) != tolower(second[i]))
				answer = false;
	}

	return answer;
}

/*
	User input
	string str -- string to output
*/
size_t input(string str)
{
	size_t answer;								// User input

	cout << str;
	cin >> answer;
	if (cin.fail())
		cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;

	return answer;
}

// A function that delays the program and clears the console
void delay()
{
	system("pause");
	system("cls");
}