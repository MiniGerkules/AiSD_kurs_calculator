#pragma once

#include <iostream>

/*
	Entering an expression from a file
	std::string name -- the name of the file from which information is read
*/
std::string input_from_file(std::string name = "data");

/*
	Function defining there is a substring in a string with a specific character
	std::string first -- first line (in which we are looking)
	std::string second -- second line (which we are looking for)
	size_t index -- the index of the element of the first line from which to start looking for the second line
*/
bool my_find(std::string first, std::string second, size_t index);

/*
	User input
	string str -- string to output
*/
size_t input(std::string str);

// A function that delays the program and clears the console
void delay();