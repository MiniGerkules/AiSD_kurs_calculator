#pragma once

#include <iostream>

// Class describing the STACK data structure
class Stack
{
	private:
		// Class describing the stack element
		class Stack_item
		{
		public:
			Stack_item* Next;						// Next item in the stack
			char Value_char;						// Stack item information field (char)
			double Value_double;					// Stack item information field (double)

			/*
				Stack_item class constructor
				char next -- pointer to next item
				int value -- the value of the information field of the stack member
			*/
			Stack_item(Stack_item* next, char value, double value_double);
		};

		Stack_item* Top;							// Top of stack

	public:
		friend class �alculator;

		// Stack class constructor
		Stack();

		// Destructor of the Stack class
		~Stack();

		/*
			The function that adds an item to the stack
			char value -- the value of the information field of the stack item
		*/
		void push(char value);

		/*
			The function that adds an item to the stack
			char value -- the value of the information field of the stack item
		*/
		void push(double value);

		// Function that returns the top of the stack
		char pop_char();

		// Function that returns the top of the stack
		double pop_double();

		// Viewing the value of the top of the stack
		char peek_char();

		// Function that check the stack for emptiness (if empty -- true, otherwise -- false)
		bool is_empty();
};