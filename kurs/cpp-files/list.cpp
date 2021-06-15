#include "../h-files/List.h"

using namespace std;

//-------------------------------------------------------------
// Description of methods of the List class
//-------------------------------------------------------------

// List class constructor
List::List()
{
	Begin = NULL;
	End = NULL;
}

// Destructor of the List class
List::~List()
{
	while (Begin != NULL)
		pop();

	Begin = NULL;
	End = NULL;
}

/*
	List_item class constructor
	List_item* next -- pointer to next item
	string value -- the value of the information field of the list item
*/
List::List_item::List_item(List_item* next, List_item* prev, string value)
	: Next(next), Prev(prev), Value(value)
{}

/*
	The function that adds an item to the list
	string value -- the value of the information field of the list item
*/
void List::push_front(string value)
{
	if (Begin == NULL)
	{
		Begin = new List_item(NULL, NULL, value);
		if (Begin == NULL)
			throw std::out_of_range("Memory not allocated.");
		End = Begin;
	}
	else
	{
		Begin = new List_item(Begin, NULL, value);
		if (Begin == NULL)
			throw std::out_of_range("Memory not allocated.");
		Begin->Next->Prev = Begin;
	}
}

// Function that returns the first item of the list
string List::pop()
{
	List_item* deleted;							// Excluded list item
	string value;								// List item value

	if (Begin == NULL)
		throw out_of_range("The list is empty.");

	value = Begin->Value;
	deleted = Begin;
	Begin = Begin->Next;
	delete deleted;

	return value;
}

// Function that check the list for emptiness (if empty -- true, otherwise -- false)
bool List::is_empty()
{
	bool answer;								// The program's response about the empty list

	if (Begin == NULL)
		answer = true;
	else
		answer = false;

	return answer;
}