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

	 void push_front(const T& val); //adds element to the head of the list
	 void pop_front(); //removes element from the front
	 void push_end(const T& val); //adds an element to the end of the list
	 void pop_back(); //removes an element from the end of the list

	 T& front();//returns the data at the head
	 T& back(); // returns the data at the tail

	 const T& front() const; //returns the const element at the head

	 void remove(const T& val); //removes the node that matches the val
	 void clear(); //removes all the nodes in the linked list

	 bool empty() const; //checks if the list is empty
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
	 }else
	 {
		 //just in case because if there is no head to the list there also wouldn't be a tail
		 tail = nullptr;
	 }
 }
 template<typename T>
 void tList<T>::push_front(const T& val)
 {
	 node* origHead = head;
	 head = new node{ val, origHead, nullptr }; //just so I can debug easier this goes; data, ->next, ->prev
	 if(origHead!=nullptr) // whenever i add or remove something i wanna run this check so that I can make sure I had something there originally
	 {
		 origHead->prev = head;
	 }
	 if(tail==nullptr) // a solid check so I can iterate through the list and locate where the tail should be if it doesn't already exist
	 {
		 node* tmpNode = head; //creating a temporary node at the head
		 while(tmpNode->next != nullptr) //iterates through until we find a node that doesn't have a node following it
		 {
			 tmpNode = tmpNode->next;
		 }
		 tail = tmpNode; //set the tail to the last item in the list
	 }
 }
 template<typename T>
 void tList<T>::push_end(const T& val) //should essentially be the opposite of the push_front except using the tail and prev
 {
	 node* origTail = tail;
	 tail = new node{ val, nullptr, origTail }; //data, next, prev
	 if(origTail!=nullptr) //same reasoning as before I want to make sure if i add something 
	 {
		 origTail->next = tail;
	 }
	 if(head == nullptr)//checking if there was a front, if this new added element was the first one this check will set a head
	 {
		 node* tmpNode = tail; //creating a temporary node at the tail for backwards iteration
		 while (tmpNode->prev != nullptr) //iterates through until we find a node that doesn't have a node before it
		 {
			 tmpNode = tmpNode->prev;
		 }
		 head = tmpNode; //set the head to the last item in the list
	 }
 }
 template<typename T>
 void tList<T>::pop_back()//same concept as deleting from the front just using prev instead of next
 {
	 node* newTail = tail->prev;
	 delete tail;
	 tail = newTail;

	 if(tail!=nullptr) //if there is a node there lets remove the 
	 {
		 tail->next = nullptr;
	 }
	 else //pretty basic if the tail is null it is safe to assume the head is as well 
	 {
		 head = nullptr;
	 }

 }
template <typename T>
void tList<T>::remove(const T& val)
{
	node** tmpNode = &head; //first things first we gotta set the first temp node to the head
	while((*tmpNode)->next->data!=val) //basic check checking to see if the next node
	{
		tmpNode = &((*tmpNode)->next);
	}
	node* tmpNode2 = (*tmpNode)->next->next; //skipping one so we can set the next and prev when we remove a value
	delete (*tmpNode)->next; //deleting the node that matched up
	(*tmpNode)->next = tmpNode2;
	tmpNode2->prev = (*tmpNode);
}
template <typename T>
void tList<T>::clear()
{
	node* endNode = head; //the node to kill all others!!!!
	while(endNode !=nullptr)//once I remove all nodes this node will be null
	{
		node* nextNode = endNode->next; //just to set an extra node for the delete keyword
		delete endNode;
		endNode = nextNode; //now the end node is the node that was endNode->next
	}
	head = nullptr;
	tail = nullptr;
}
template <typename T>
bool tList<T>::empty() const
{
	return head == nullptr; //if this returns true the list should be empty
}
 template <typename T>
 T& tList<T>::front()
 {
	 return head->data; //returning data
 }
 template <typename T>
 T& tList<T>::back()
 {
	 return tail->data;//returning data
 }
 template <typename T>
 const T& tList<T>::front() const
 {
	 return head->data; //returning data not much to this method, idk what to say here lol
 }
