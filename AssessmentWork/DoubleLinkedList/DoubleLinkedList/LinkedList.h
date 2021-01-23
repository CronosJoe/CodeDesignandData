#pragma once
#include <cstddef>
#include <iostream>

template<typename T>
class templatedList
{
	struct node
	{
		T data; //for right now I'm just gonna stick to ints I might want to template this later but one hurdle at a time
		Node* next;
		Node* prev;
	};
	node* head;
	node* tail;
public:
	void tList(); //this will initialize the head and tail of the list to null
};
	
template<typename T>
 void inline templatedList<T>::tList()
{
	head = NULL;
	tail = NULL;
}

