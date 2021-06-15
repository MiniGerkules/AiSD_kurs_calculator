#include "../h-files/Stack.h"

using namespace std;

//-------------------------------------------------------------
// Description of methods of the Stack class
//-------------------------------------------------------------

// Stack class constructor
Stack::Stack()
{
	Top = NULL;
}

// Destructor of the Stack class
Stack::~Stack()
{
	while (Top != NULL)
		pop_char();

	Top = NULL;
}

/*
	Stack_item class constructor
	Stack_item* next -- pointer to next item
	char value -- the value of the information field of the stack member
*/
Stack::Stack_item::Stack_item(Stack_item* next, char value_char, double value_double)
	: Next(next), Value_char(value_char), Value_double(value_double)
{}

/*
	The function that adds an item to the stack
	char value -- the value of the information field of the stack item
*/
void Stack::push(char value)
{
	Stack_item* new_item = NULL;				// New item being added to the stack

	if (Top == NULL)
	{
		Top = new Stack_item(NULL, value, 0);
		if (Top == NULL)
			throw out_of_range("Memory not allocated.");
	}
	else
	{
		new_item = new Stack_item(Top, value, 0);
		if (new_item == NULL)
			throw out_of_range("Memory not allocated.");
		Top = new_item;
	}
}

/*
	The function that adds an item to the stack
	double value -- the value of the information field of the stack item
*/
void Stack::push(double value)
{
	Stack_item* new_item = NULL;				// New item being added to the stack

	if (Top == NULL)
	{
		Top = new Stack_item(NULL, ' ', value);
		if (Top == NULL)
			throw out_of_range("Memory not allocated.");
	}
	else
	{
		new_item = new Stack_item(Top, ' ', value);
		if (new_item == NULL)
			throw out_of_range("Memory not allocated.");
		Top = new_item;
	}
}

// Function that returns the top of the stack
char Stack::pop_char()
{
	Stack_item* deleted;					// Excluded stack item
	char value;								// Stack item value

	if (Top == NULL)
		throw domain_error("The expression is invalid (incorrect parenthesis sequence found). Try entering it again.");

	value = Top->Value_char;
	deleted = Top;
	Top = Top->Next;
	delete deleted;

	return value;
}

// Function that returns the top of the stack
double Stack::pop_double()
{
	Stack_item* deleted;					// Excluded stack item
	double value;							// Stack item value

	if (Top == NULL)
		throw domain_error("The stack is empty.");

	value = Top->Value_double;
	deleted = Top;
	Top = Top->Next;
	delete deleted;

	return value;
}

// Viewing the value of the top of the stack
char Stack::peek_char()
{
	return Top->Value_char;
}

// Function that check the stack for emptiness
bool Stack::is_empty()
{
	bool answer;								// The program's response about the empty list

	if (Top == NULL)
		answer = true;
	else
		answer = false;

	return answer;
}