#pragma once
#include <iostream>
#include "Stack.h"
#include "list.h"
#include "prototypes.h"

class �alculator
{
private:
	Stack* prefix;								// Stack for forming a prefix record
	List* result;								// Polish notation of entered expression

	size_t number_of_brackets;					// The variable stores the number of closing parentheses

	bool is_prev_number;						// Flag indicating whether the previous expression is a number
	bool is_prev_sign;							// Flag indicating whether the previous expression is an arithmetic sign
	bool is_prev_bracket;						// Flag indicating whether the previous expression is a bracket
	bool is_prev_function;						// Flag indicating whether the previous expression is a function
	bool is_first;								// Flag indicating whether the expression is the first

	// The function initializes the private fields of the �alculator class
	void initializer();

	/*
		The function allows the program to accept the unary minus in the expression record
		string expression -- the string in which we are looking for unary cons
	*/
	bool is_unary_minus(std::string expression, size_t index);

	/*
		The function returns the priority of characters in the prefix notation
		char sign -- the sign to be prioritized
	*/
	size_t priority(char sign);

	/*
		The function determines which character is returned from the stack
		char symbol -- character to be identified
	*/
	void packer(char symbol);

	/*
		The program determines if expression is a sign or a function and calls the desired method
		std::string expression -- sign or function passed to the program
	*/
	double math_processor(std::string expression);

	/*
		The function performs the transferred arithmetic operation
		std::string expression -- sign passed to the program
	*/
	double math_processor_signs(std::string expression);

	/*
		The function evaluates the passed function from the passed argument
		std::string expression -- function passed to the program
	*/
	double math_processor_functions(std::string expression);

public:

	// �alculator class constructor
	�alculator();

	// Destructor of the �alculator class
	~�alculator();

	/*
		The function checks if the expression is a number and, if so, performs certain actions
		std::string expression -- string to check
		size_t* index -- index of the current character of the string
	*/
	bool if_float(std::string expression, size_t* index);

	/*
		The function checks if the expression is an arithmetic sign and, if so, performs certain actions
		std::string expression -- string to check
		size_t* index -- index of the current character of the string
	*/
	bool if_sign(std::string expression, size_t* index);

	/*
		The function checks if the expression is a parenthesis and, if so, performs certain actions
		std::string expression -- string to check
		size_t* index -- index of the current character of the string
	*/
	bool if_brackets(std::string expression, size_t* index);

	/*
		The function checks if the expression is a constant and, if so, performs certain actions
		string expression -- string to check
		size_t* index -- index of the current character of the string
	*/
	bool if_constant(std::string expression, size_t* index);

	/*
		A function checks if an expression is a function and, if so, performs certain actions
		std::string expression -- string to check
		size_t* index -- index of the current character of the string
	*/
	bool if_function(std::string expression, size_t* index);

	/*
		The function checks the string entered by the user for correctness
		std::string expression -- the string to be checked for correctness
	*/
	std::string verification_and_forming(std::string expression);

	// A function that converts infix notation to prefix and calculates the value
	double count();

	// The function outputs an expression written in a Polish notetion
	void print_result();
};