#define _USE_MATH_DEFINES
#include "../h-files/�alculator.h"
#include <string>
#include <cctype>

using namespace std;

//-------------------------------------------------------------
// Description of methods of the �alculator class
//-------------------------------------------------------------

//-------------------------------------------------------------
// Private methods of class �alculator
//-------------------------------------------------------------

// The function initializes the private fields of the �alculator class
void �alculator::initializer()
{
	number_of_brackets = 0;
	is_prev_number = false;
	is_prev_sign = false;
	is_prev_bracket = false;
	is_prev_function = false;
	is_first = true;
	while (!prefix->is_empty())
		prefix->pop_char();
	while (!result->is_empty())
	{
		result->pop();
		result->End = result->Begin;
	}
}

/*
	The function allows the program to accept the unary minus in the expression record
	string expression -- the string in which we are looking for unary cons
*/
bool �alculator::is_unary_minus(string expression, size_t index)
{
	bool answer;								// The program's response to whether the minus is unary

	if ((index - 1 == 0) && (expression[index - 1] == '-'))
		answer = true;
	else if ((index > 1) && (expression[index - 2] == '(') && (expression[index - 1] == '-'))
		answer = true;
	else
		answer = false;

	return answer;
}

/*
	The function returns the priority of characters in the prefix notation
	char sign -- the sign to be prioritized
*/
size_t �alculator::priority(char sign)
{
	size_t answer;								// Program response about sign priority

	if ((sign == '(') || (sign == ')'))
		answer = 0;
	else if ((sign == '+') || (sign == '-'))
		answer = 1;
	else if (sign == '*')
		answer = 2;
	else
		answer = 3;

	return answer;
}

/*
	The function determines which character is returned from the stack
	char symbol -- character to be identified
*/
void �alculator::packer(char symbol)
{
	string functions[] = { "ln", "lg", "abs", "rnd", "tan", "cot", "atg",
		"sin", "cos", "sqrt" };					// All available functions
	string answer;								// The program's response about what character came back from the stack

	if (((int)symbol >= 65) && ((int)symbol <= 75))
		answer = functions[(int)symbol - 65];
	else
		answer.append(1, symbol);

	result->push_front(answer);
}

/*
	The program determines if expression is a sign or a function and calls the desired method
	string expression -- sign or function passed to the program
*/
double �alculator::math_processor(string expression)
{
	double answer;								// Value of calculated function

	if (expression.length() > 1)
		answer = math_processor_functions(expression);
	else
		answer = math_processor_signs(expression);

	return answer;
}

/*
	The function performs the transferred arithmetic operation
	string expression -- sign passed to the program
*/
double �alculator::math_processor_signs(string expression)
{
	string signs[] = { "+", "-", "*", "/", "^" };	// Arithmetic signs
	double answer;								// Value of calculated function
	double value1;								// First operand
	double value2;								// Second operand
	size_t i;									// For loop parameter

	i = 0;
	while (signs[i] != expression)
		i++;

	switch (i)
	{
		//-------------------------------
	case(0):
		value1 = prefix->pop_double();
		value2 = prefix->pop_double();
		answer = value1 + value2;
		break;
		//-------------------------------
	case(1):
		value1 = prefix->pop_double();
		value2 = prefix->pop_double();
		answer = value1 - value2;
		break;
		//-------------------------------
	case(2):
		value1 = prefix->pop_double();
		value2 = prefix->pop_double();
		answer = value1 * value2;
		break;
		//-------------------------------
	case(3):
		value1 = prefix->pop_double();
		value2 = prefix->pop_double();
		if (value2 != 0)
			answer = value1 / value2;
		else
			throw domain_error("The expression contains division by zero!");
		break;
		//-------------------------------
	case(4):
		value1 = prefix->pop_double();
		value2 = prefix->pop_double();
		answer = pow(value1, value2);
		break;
	}

	return answer;
}

/*
	The function evaluates the passed function from the passed argument
	string expression -- function passed to the program
*/
double �alculator::math_processor_functions(string expression)
{
	string functions[] = { "ln", "lg", "abs", "rnd", "tan", "cot", "atg",
		"sin", "cos", "sqrt" };					// All available functions
	double answer;								// Value of calculated function
	double value;								// Function argument
	size_t i;									// For loop parameter

	i = 0;
	while (functions[i] != expression)
		i++;

	switch (i)
	{
		//-------------------------------
	case(0):
		value = prefix->pop_double();
		answer = log(value);
		break;
		//-------------------------------
	case(1):
		value = prefix->pop_double();
		answer = log10(value);
		break;
		//-------------------------------
	case(2):
		value = prefix->pop_double();
		answer = abs(value);
		break;
		//-------------------------------
	case(3):
		value = prefix->pop_double();
		answer = round(value);
		break;
		//-------------------------------
	case(4):
		value = prefix->pop_double();
		answer = tan(value);
		break;
		//-------------------------------
	case(5):
		value = prefix->pop_double();
		answer = cos(value) / sin(value);
		break;
		//-------------------------------
	case(6):
		value = prefix->pop_double();
		answer = atan(value);
		break;
		//-------------------------------
	case(7):
		value = prefix->pop_double();
		answer = sin(value);
		break;
		//-------------------------------
	case(8):
		value = prefix->pop_double();
		answer = cos(value);
		break;
		//-------------------------------
	case(9):
		value = prefix->pop_double();
		answer = sqrt(value);
		break;
		//-------------------------------
	}

	return answer;
}

//-------------------------------------------------------------
// Public methods of class �alculator
//-------------------------------------------------------------

// �alculator class constructor
�alculator::�alculator()
{
	prefix = new Stack;
	if (prefix == NULL)
		throw out_of_range("Memory not allocated!");

	result = new List;
	if (prefix == NULL)
	{
		delete prefix;
		throw out_of_range("Memory not allocated!");
	}

	initializer();
}

// Destructor of the �alculator class
�alculator::~�alculator()
{
	delete prefix;
	delete result;
}

/*
	The function checks if the expression is a number and, if so, performs certain actions
	std::string expression -- string to check
	size_t* index -- index of the current character of the string
*/
bool �alculator::if_float(string expression, size_t* index)
{
	string helper;								// Auxiliary string for storing the number
	bool answer;								// The program's response as to whether the expression is a number
	bool dot;									// A flag indicating whether the point has been previously encountered in this number

	answer = false;
	if (isdigit(expression[*index - 1]))
	{
		// Two numbers separated by a space or constant + number
		if (is_prev_number || is_prev_function)
			throw domain_error("The expression is invalid (found wrong sequence of function numbers). Try entering it again.");

		helper.append(1, expression[(*index)-- - 1]);
		answer = true;
		dot = false;
		if (*index != 0)
		{
			do
			{
				while ((*index != 0) && (isdigit(expression[*index - 1])))
					helper.insert(0, 1, expression[(*index)-- - 1]);

				if ((*index != 0) && (expression[*index - 1] == '.') && (!dot))
				{
					dot = true;
					helper.insert(0, 1, expression[(*index)-- - 1]);
				}
				else if ((*index != 0) && (expression[*index - 1] == '.'))		// Two dots in a number
					throw domain_error("The expression is invalid (found two points in the number). Try entering it again.");
				else
					dot = false;
			} while (dot == true);

			if (is_unary_minus(expression, *index))
			{
				helper.insert(0, 1, '-');
				(*index)--;
			}
		}

		result->push_front(helper);
		// Changing the value of flags "previous items"
		is_prev_number = true;
		is_prev_sign = is_prev_bracket = is_prev_function = is_first = false;
	}

	return answer;
}

/*
	The function checks if the expression is an arithmetic sign and, if so, performs certain actions
	string expression -- string to check
	size_t* index -- index of the current character of the string
*/
bool �alculator::if_sign(string expression, size_t* index)
{
	char signs[] = { '+', '-', '*', '/', '^'};		// Arithmetic signs
	bool answer;								// The answer of the program about the belonging of the entered character to arithmetic signs
	size_t i;									// For loop

	answer = false;
	for (i = 0; i < 5;i++)
		if (expression[*index - 1] == signs[i])
		{
			// Two arithmetic signs in a row or function + sign
			if (is_prev_sign || (is_prev_bracket && expression[*index] == ')'))
				throw domain_error("The expression is invalid (found an incorrect sequence of arithmetic signs or arithmetic signs and brackets). Try entering it again.");	

			// If the function has no argument at the end of the expression
			if (is_first)
				throw domain_error("The expression is invalid (the string ends with an arithmetic sign). Try entering it again.");

			// Remove characters from the stack until a lower priority character appears
			answer = true;
			// Division priority is slightly higher than multiplication priority
			if (signs[i] != '/')
				while ((!prefix->is_empty()) && (priority(prefix->peek_char()) >= priority(signs[i])))
					packer(prefix->pop_char());
			else
				while ((!prefix->is_empty()) && (priority(prefix->peek_char()) >= priority(signs[i]) && (prefix->peek_char() != '*')))
					packer(prefix->pop_char());

			prefix->push(signs[i]);

			// Changing the value of flags "previous items"
			is_prev_sign = true;
			is_prev_number = is_prev_bracket = is_prev_function = false;
			i = 5;
			(*index)--;
		}

	return answer;
}

/*
	The function checks if the expression is a parenthesis and, if so, performs certain actions
	string expression -- string to check
	size_t* index -- index of the current character of the string
*/
bool �alculator::if_brackets(string expression, size_t* index)
{
	bool answer;								// Function response on whether a character is a parenthesis or not

	if (expression[*index - 1] == ')')
	{
		// Closing parenthesis and number or closing parenthesis and function
		if (is_prev_number|| is_prev_function || (is_prev_bracket && expression[*index] == '('))
			throw domain_error("The expression is invalid (found an incorrect sequence of parentheses or parentheses with numbers or functions). Try entering it again.");
		
		answer = true;
		prefix->push(')');				// Add the parenthesis to the stack
		number_of_brackets++;			// Increase the number of closing parentheses

		is_prev_bracket = true;
		is_prev_number = is_prev_sign = is_prev_function = false;
		(*index)--;
	}
	else if (expression[*index - 1] == '(')
	{
		// Open parenthesis and sign (not minus)
		if (is_prev_sign && (expression[*index] != '-'))
			throw domain_error("The expression is invalid (found wrong sequence of parentheses with numbers or functions). Try entering it again.");

		answer = true;
		while ((!prefix->is_empty()) && (prefix->peek_char() != ')'))
			packer(prefix->pop_char());

		// If the expression contains an incorrect parenthesis sequence, throw an exception
		if ((!prefix->is_empty()) && (prefix->peek_char() == ')'))
		{
			prefix->pop_char();			// Removing the bracket from the stack
			number_of_brackets--;		// Reducing the number of closing parentheses
		}
		else
			throw domain_error("The expression is invalid (incorrect parenthesis sequence found). Try entering it again.");

		is_prev_bracket = true;
		is_prev_number = is_prev_sign = is_prev_function = is_first = false;
		(*index)--;
	}
	else 
		answer = false;

	return answer;
}

/*
	The function checks if the expression is a constant and, if so, performs certain actions
	string function -- string to check
	size_t* index -- index of the current character of the string
*/
bool �alculator::if_constant(string expression, size_t* index)
{
	string constant[] = { "e" , "ip"};			// All possible constants (the titles are reversed as we go from right to left)
	string helper;
	bool answer;								// The program's response as to whether the input string is a constant
	size_t i, j;								// For loop parameter

	answer = false;
	for (i = 1; i < 3; i++)
		if (my_find(expression, constant[i - 1], *index))
		{
			// Two constants separated by space or number + constant
			if (is_prev_number || is_prev_function || (is_prev_bracket && expression[*index] == '('))
				throw domain_error("The expression is invalid (found wrong sequence of numbers, or numbers and functions, or numbers and parentheses). Try entering it again.");	
			
			answer = true;
			for (j = i; j > 0; j--)
				helper.append(1, tolower(expression[*index - j]));

			// String length is i
			*index -= i;

			if ((*index > 0) && (is_unary_minus(expression, *index)))
			{
				helper.insert(0, 1, '-');
				(*index)--;
			}

			result->push_front(helper);
			// Changing the value of flags "previous items"
			is_prev_number = true;
			is_prev_sign = is_prev_bracket = is_prev_function = is_first = false;
			i = 3;
		}

	return answer;
}

/*
	A function checks if an expression is a function and, if so, performs certain actions
	string expression -- string to check
	size_t* index -- index of the current character of the string
*/
bool �alculator::if_function(string expression, size_t* index)
{
	string functions[] = { "nl", "gl", "sba", "dnr", "nat", "toc", "gta" ,
		"nis", "soc", "trqs" };					// All available functions  (the titles are reversed as we go from right to left)
	bool answer;								// The program's response as to whether the input string is a function
	size_t i;									// For loop parameter

	answer = false;
	for (i = 0; i < 10; i++)
		if (my_find(expression, functions[i], *index))
		{
			// Number + function or constant + function
			if (is_prev_sign || is_prev_function || (is_prev_bracket && expression[*index] == ')'))
				throw domain_error("The expression is invalid (found wrong sequence of functions or functions and arithmetic signs). Try entering it again.");	
			
			// If the function has no argument at the end of the expression
			if (is_first)
				throw domain_error("The expression is invalid (the string ends with a function with no argument). Try entering it again.");

			// All functions have priority 3
			answer = true;
			while ((!prefix->is_empty()) && (priority(prefix->peek_char()) == 3))
				packer(prefix->pop_char());

			prefix->push((char)(65 + i));

			// Changing the value of flags "previous items"
			is_prev_function = true;
			is_prev_number = is_prev_bracket = is_prev_sign = false;

			*index -= functions[i].length();
			i = 10;
		}

	return answer;
}

/*
	The function checks user input and forms a prefix notation of the expression
	string expression -- the string to be checked for correctness
*/
string �alculator::verification_and_forming(string expression)
{
	size_t i;									// For loop parameter

	// Initializing all variables
	initializer();

	// Bypassing from right to left
	i = expression.length();
	while (i > 0)
		if (expression[i - 1] != ' ')
		{
			if (!if_float(expression, &i))
				if (!if_sign(expression, &i))
					if (!if_brackets(expression, &i))
						if (!if_constant(expression, &i))
							if (!if_function(expression, &i))
								throw domain_error("The expression is invalid (invalid characters found). Try entering it again.");
		}
		else
			// Removing a space
			expression.erase(i-- - 1, 1);

	// Closing parenthesis or binary character without a second value
	if ((is_prev_bracket && expression[0] == ')') || (is_prev_sign && expression[0] != '-'))
		throw domain_error("The expression is invalid (expression ends with an arithmetic sign or a function with no value). Try entering it again.");

	// Incorrect parenthesis sequence
	if (number_of_brackets != 0)
		throw domain_error("The expression is invalid (incorrect parenthesis sequence found). Try entering it again.");

	while (!prefix->is_empty())
		packer(prefix->pop_char());

	return expression;
}

// A function that converts infix notation to prefix and calculates the value
double �alculator::count()
{
	List::List_item* current;				// Current element of the prefix entry
	double answer;							// Calculation result

	answer = 0;
	current = result->End;
	while (current != NULL)
	{
		try
		{
			answer = stod(current->Value);
			prefix->push(answer);
		}
		catch (invalid_argument)
		{
			if (current->Value == "e")
				prefix->push(M_E);
			else if (current->Value == "-e")
				prefix->push(-M_E);
			else if (current->Value == "pi")
				prefix->push(M_PI);
			else if (current->Value == "-pi")
				prefix->push(-M_PI);
			else
			{
				answer = math_processor(current->Value);
				prefix->push(answer);
			}
		}
		current = current->Prev;
	}

	if (!prefix->is_empty())
		answer = prefix->pop_double();
	
	return answer;
}

// The function outputs an expression written in a Polish notetion
void �alculator::print_result()
{
	List::List_item* current;				// Current list item

	current = result->Begin;
	while (current != NULL)
	{
		cout << current->Value << " ";
		current = current->Next;
	}
}