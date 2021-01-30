#pragma once
#include <cstddef>
#include <iostream>

template<typename T>
class tList
{
	struct node
	{
		T data; //for right now I'm just gonna stick to ints I might want to template this later but one hurdle at a time
		node* next;
		node* prev;
	};
	node* head;
	node* tail;
public:
	 tList(); //this will initialize the head and tail of the list to null
	 tList(const tList &other); //copy constructor 
	 ~tList(); // deconstructs the list

	 void pop_front(const T& val); //adds element to the head of the list
	 void pop_front(); //removes element from the front

	 T& front();//returns the element at the head
	 T& back(); // returns the element at the tail
};

//constructor
template<typename T>
 tList<T>::tList()
{
	head = nullptr; // this sets the head to a null since there is currently nothing in the list on constructor
	tail = nullptr; //same thing to the tail
	//no point in setting prev and next yet since these are just null objects right now
}
 //copy constructor
 template<typename T>
 tList<T>::tList(const tList& otherNode) //constructor to copy another list
 {
	 head = new node{ other.head->data, nullptr, nullptr }; //data, next, previous

	 node* nextNode = other.head->next;
	 node* copyNode = head;
	 node* prevNode = nullptr; //since this first one is the head

	 while (nextNode != nullptr)
	 {
		 *copyNode->next = new node{ nextNode->data,nullptr,nullptr }; //this will overwrite the copy node(the one we are working on) with the next one in the list should let us change out of scope since it is a reference
		 copyNode->prev = prevNode;
		 prevNode = copyNode;
		 copyNode = copyNode->next; 
		 nextNode = nextNode->next;
	 }
	 tail = copyNode; //finally set the tail to the last node
 }
 //destructor
 template<typename T>
 tList<T>::~tList()
 {
	 while (head != nullptr) //this will delete the list by removing each object until the heal is a null pointer again
	 {
		 pop_front();
	 }
 }

 //removes front element
 template<typename T>
 void tList<T>::pop_front()
 {
	 node* newHead = head->next; //first setting up a temp to save what the new head will be (the next element in the list)
	 delete head; //removing the original head
	 head = newHead; //finally saving the head->next to where the old head had been in the list
	 if (head != nullptr) //in case the new head was null like when we remove the entire list
	 {
		 head->prev = nullptr; //setting head prev to nullpointer!
	 }
 }

