#pragma once
#include <cstddef>
#include <iostream>
using namespace std;
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
	 void push_back(const T& val); //adds an element to the end of the list
	 void pop_back(); //removes an element from the end of the list

	 T& front();//returns the data at the head
	 T& back(); // returns the data at the tail

	 const T& front() const; //returns the const element at the head

	 void remove(const T& val); //removes the node that matches the val
	 void clear(); //removes all the nodes in the linked list

	 bool empty() const; //checks if the list is empty

	 void resize(size_t newSize); //resizes the list deleting excess defaulting additional
	 int getSize();//gonna need this for the resize method

	 void sort();//sorts the list

	 void print(); //prints the list

	 //Add copy operator 
	 //tList& operator=(const tList& rhs);
	 //iterator stuff ;-;
	 class iterator
	 {
		 //current node to work on
		 node* cur; //does this only work if template is used again? I put it inside the tList class to remove this error
		 tList* list; //adding this to make some of the methods easier

	 public:
		 //constructors
		 iterator();
		 iterator(tList *List, node *startNode);
		 //operators
		 bool operator ==( iterator& rhs); //returns true if the iterator points to the same node, not sure if it needs const?
		 bool operator !=( iterator& rhs); //returns false if the iterator is not pointing to the same node, this seems the same as last one? well I'll know when i make it
		 T& operator*() const; //returns ref to the element pointed to by current node

		 iterator &operator++(); //returns ref to this iterator after incremented
		 iterator operator++(int);//returns an iterator to current while the existing iterator is incremented
		 iterator &operator--();//decrements
		 iterator operator--(int);//opposite of ++int

		 

	 };
	 iterator insert(const iterator& it, const T& val); //adds a node after it with the data val
	 iterator begin(); //returns iterator pointing to first node
	 iterator end(); //returns iterator pointing to the last node
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
 tList<T>::tList(const tList& other) //constructor to copy another list
 {
	 node* cur = other.head; //first creating a node for use to work with for the loop and the assignment
	 while (cur != nullptr) //loop till the other list is done
	 {
		 push_back(cur->data);//continue slapping it onto the end
		 cur=cur->next;
	 }
 }
 //destructor
 template<typename T>
 tList<T>::~tList()
 {
	 while (head != nullptr) //this will delete the list by removing each object until the head is a null pointer again
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
 void tList<T>::push_back(const T& val) //should essentially be the opposite of the push_front except using the tail and prev
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
	node* tmpNode = head; //first things first we gotta set the first temp node to the head
	node* nextNode = new node();
	node* prevNode = new node();
	while(tmpNode != nullptr)//as long as we are not at the end of the list
	{
		if(tmpNode->data == val)//this should handle edge cases since I am starting at the head and it doesn't end until tmpnode is after the tail
		{
			nextNode = tmpNode->next; //saving the next spots pointer for when we delete tmpNode, this only will be nullptr if the tmpNode is the tail
			prevNode = tmpNode->prev;
			if(tmpNode == head) //if front
			{
			//should be straight forward
				delete tmpNode; //delete the head
				nextNode->prev = nullptr; //making sure this goes right not gonna leave it up to visual studio
				head = nextNode; //head becomes the node we had saved up above
				tmpNode = nextNode; //so that we can continue with our function
			}else if(tmpNode == tail) //if end
			{
				delete tmpNode; //delete the tail
				prevNode->next = nullptr; //not leaving to vs to do nullptr
				tail = prevNode;//set the new tail
				tmpNode = nullptr; //since tmpNode was on the tail it should now be nullptr so that it can end this while loop
			}
			else //if anywhere in the middle
			{
				delete tmpNode; //deleting the one with the value
				prevNode->next = nextNode; //fix the linked list
				nextNode->prev = prevNode; //both ways
				tmpNode = nextNode; //so that we can continue with the loop
			}
		}else
		{
			tmpNode = tmpNode->next; //continue on, the only time this won't be run is if the val matched up
		}
	}
	
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
 template <typename T>
 void tList<T>::resize(size_t size)
 {
	 int origSize = getSize();  //first get our value
	 if(size>origSize)//compare the values to see what I gotta do
	 {
		 int newSize = size - origSize; //I think this works? 
		 while(newSize>0)//should iterate once for every whole number over origSize, for example if it is 5 it will go 5, 4, 3, 2, and 1
		 {
			 push_back(0);//add one default value to the end
			 newSize--;
		 }
	 }else if(size<origSize) //reverse of if statement
	 {
		 int newSize = origSize - size; //this SHOULD work
		 while(newSize>0)//should count for each of em
		 {
			 pop_back();//remove a node at the end
			 newSize--;
		 }
	 }//no need to check if the size entered is equal because it will just skip these statements and end the method no resizing needed
 }
 template <typename T>
 int tList<T>::getSize()
 {
	 if(head!=nullptr)//just to make sure I can return something
	 {
		 node* cntNode = head; //a node to count the others
		 int count = 1; //counting for the head
		while(cntNode->next !=nullptr) //if the head is the only value in here this SHOULD not even run
		{
			cntNode = cntNode->next;
			count++;
		}
		return count; //return count once we are done
	 }else
	 {
		 return 0;
	 }
 }
 template <typename T>
 void tList<T>::sort()
 {
	 //this will be null for now cause I like for loops better than while
	 node* current = nullptr; //the current node
	 node* nextNode = nullptr; //the currents next
	 T saver; //to save data when we swap, since data is type T this should be the same type as the data 100% of the time
	 //first make sure the list has something to sort
	 if (head == nullptr)
	 {
		 return; //quit if there is no list
	 }
	 else 
	 {
		 //nested for loop time, we start at the head
		 //this will save me a few times, set the current working node to the head, end this loop if it hits the end, and finally gonna increment each iteration
		 for (current = head; current->next != nullptr; current = current->next)
		 {
			 for (nextNode = current->next; nextNode != nullptr; nextNode = nextNode->next) //this will be used to check against the current node to sort the list
			 {
				 //if the current node is greater than its next node's data then I flip em around
				 if (current->data > nextNode->data)
				 {
					 saver = current->data; //time for saver to do its job save my stuff
					 current->data = nextNode->data;//the swap
					 nextNode->data = saver;//the saver finishing the swap
				 }
			 }
		 }
	 }
 }
 template <typename T>
 void tList<T>::print()
 {
	 std::cout << "" << std::endl;
	 node* current = head;
	 while(current!=nullptr)
	 {
		 std::cout << current->data; //should print only data
		 current = current->next;
	 }
 }
 template <typename T>
 tList<T>::iterator::iterator() //class, method(constructor here)
 {
	 list = NULL;
	 cur = nullptr;
 }
 template <typename T>
 tList<T>::iterator::iterator(tList *List, node *startNode)//reasonably basic constructors
 {
	 list = List; 
	 cur = startNode;
 }
 //iterator operators
 template <typename T>
 bool tList<T>::iterator::operator ==(iterator &rhs)//pretty basic returns for these first two
 {
	 return(list == rhs.list) && (cur == rhs.cur);
 }
 template <typename T>
 bool tList<T>::iterator::operator !=(iterator &rhs)
 {
	 return (list != rhs.list) || (cur != rhs.cur);
 }
 template <typename T>
 T& tList<T>::iterator::operator*() const //dereferences the node so it will return the data
 {
	 return cur->data;
 }
 template <typename T>
 typename tList<T>::iterator &tList<T>::iterator::operator++() //this feels super wack but compiller said this is how this method would be written xD
 {
	 cur = cur->next;
	 return *this; //returning the ref to the link after the current one
 }
 template <typename T>
 typename tList<T>::iterator tList<T>::iterator::operator++(int)
 {
	 iterator tmpIterator = *this; //gotta grab the ref first
	 cur = cur->next;
	 return tmpIterator; //return the ref after incrementing the current
 }
 template <typename T>
 typename tList<T>::iterator& tList<T>::iterator::operator--() //these two SHOULD just be inverses of the last two methods.
 {
	 cur = cur->prev;
	 return *this; //returning the ref to the node before the current one
 }
 template <typename T>
 typename tList<T>::iterator tList<T>::iterator::operator--(int)
 {
	 iterator tmpIterator = *this; //gotta grab the ref first
	 cur = cur->prev;
	 return tmpIterator; //return the ref after decrementing the current
 }
 template <typename T>
 typename tList<T>::iterator tList<T>::begin()
 {
	 return iterator(this, head); //all i gotta do is return head here to get first node
 }
 template <typename T>
 typename tList<T>::iterator tList<T>::end()
 {
	 return iterator(this, nullptr); //should always return nullptr
 }
 template <typename T>
 typename tList<T>::iterator tList<T>::insert(const iterator& it, const T& val) //this method length scares me
 {
	 node* beforeNode = it->cur; //nab that reference to the spot before where I gotta edit
	 node* spotNode = beforeNode->next; //to save important prev data
	 node* newNode = new node{ val, beforeNode,spotNode };//data, next, prev
	 beforeNode->next = newNode;
	 spotNode->prev = newNode;//adding in the prev/next data we need
 }


