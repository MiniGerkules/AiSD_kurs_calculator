#pragma once

#include <iostream>

// Class describing a doubly linked list
class List
{
private:
	// Class describing the List element
	class List_item
	{
	public:
		List_item* Next;						// Next item in the list
		List_item* Prev;						// Previous item in the list
		std::string Value;						// List item information field

		/*
			List_item class constructor
			List_item* next -- pointer to next item
			Node* value -- the value of the information field of the list member
		*/
		List_item(List_item* next, List_item* prev, std::string value);
	};

	List_item* Begin;							// Beginning of the list
	List_item* End;								// End of the list

public:
	friend class �alculator;

	// List class constructor
	List();

	// Destructor of the List class
	~List();

	/*
		A function that adds an item to the List
		string value -- the value of the information field of the List item
	*/
	void push_front(std::string value);

	// A function that returns an element from the beginning of the List
	std::string pop();

	// Function that check the List for emptiness (if empty -- true, otherwise -- false)
	bool is_empty();
};