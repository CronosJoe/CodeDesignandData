#pragma once
#include <vector>

template <typename T>
class tBinaryTree
{
public:
	struct vertex
	{
		//store the data of current vertex
		T data;
		//left side
		vertex* left;
		//right side
		vertex* right;

		vertex();//default constructor
		vertex(T data);
		void remove(vertex* target); //removes a vertex at the target
		void insert(const T& val); //inserts the element as a leaf, unless there is a duplicate number on the tree
		bool search(const T& value, vertex*& found); //looks for a vertex and adds it to found then returns if it found the vertex or not
		bool hasLeft() const; //checks if there is a left node
		bool hasRight() const; //checks if there is a right node
		vertex* minValueNode(vertex* startNode); //finds the leftmost node starting at a specified point
	};

	tBinaryTree(); //tree constructor
	tBinaryTree(const tBinaryTree& other); //copy constructor, need to be implmented
	~tBinaryTree();//tree deconstructor

	tBinaryTree& operator=(const tBinaryTree& other); //need to add
	void destroyTree(vertex* point); //deletes everything under a specific vertex
private:
	std::vector<vertex*>  vertices; //a vector of pointers to vertices

	vertex* root;
};

template <typename T>
bool tBinaryTree<T>::vertex::hasLeft() const
{
	return left != nullptr; //pretty basic it will return true if there is a vertex on the left and false if there isn't
}
template <typename T>
bool tBinaryTree<T>::vertex::hasRight() const
{
	return right != nullptr; //reverse of the left one
}

//constructors
template <typename T>
tBinaryTree<T>::vertex::vertex()
{
	//since there is no data in there yet lets just null the two vertices and just leave the data be until we add our first real node
	left = nullptr;
	right = nullptr;
}
template <typename T>
tBinaryTree<T>::vertex::vertex(T nData)
{
	data = nData
	left = nullptr;
	right = nullptr;
}
template <typename T>
tBinaryTree<T>::tBinaryTree()
{
	root = nullptr; //pretty basic since this is the only variable until we actually have vertices
}
template<typename T>
tBinaryTree<T>::tBinaryTree(const tBinaryTree &other)//constructor for copying another binary tree into this one
{
	//need to implement
}
template<typename T>
tBinaryTree<T>::~tBinaryTree()//this will deconstruct the tree
{
	if(root !=nullptr)
	{
		destroyTree(root); //this should eliminate the entire tree if I did it correctly
	}
}
template<typename T>
void tBinaryTree<T>::vertex::insert(const T& val)//time to drop in the vals
{
	if(val==data)//if it matches somewhere on the tree we return out
	{
		return;
	}
	else if(val<data) //left side
	{
		if(!hasLeft())//check if something is there
		{
			vertex* tmp = new vertex;
			left = tmp;//make the new vertex and shove everything into it
			left->data = val;
			left->left = nullptr;//nulling these cause they will be empty to start
			left->right = nullptr;
			vertices.push_back(left);//add them to vertices when I make them
		}else
		{
			left->insert(val);//continue down the line
		}
	}
	else if(val>data)//right side
	{
		if (!hasRight())//check if something is there
		{
			vertex* tmp = new vertex;
			right = tmp;//make the new vertex and shove everything into it
			right->data = val;
			right->left = nullptr;//nulling these cause they will be empty to start
			right->right = nullptr;
			vertices.push_back(right);
		}
		else
		{
			right->insert(val);//continue down the line
		}
	}
	return;//because the entire thing is if else statements once they return to this iteration of the recursion they will simply exit their if and all end up here
}
template <typename T>
void tBinaryTree<T>::vertex::remove(vertex* target)
{
	//assuming target is not null
	//first check for children
	if(target->hasLeft() && target->hasRight())//if this comes out to true then we need to do the difficult solution of finding the smallest leftmost node and bringing it up
	{
		//okay first we gotta find the left most node on the right side so that the tree still works
		vertex* temp = minValueNode(target->right); 
		//now that we have our node we just replace and delete just like if we had 1 child node
		target->data = temp->data; //replace
		delete temp; //delete that leftmost node now that we have deleted it
	}
	else if(target->hasLeft())//has one child or none since last check failed
	{
		vertex* temp = target->left;//save the left node to a pointer for easy transfer
		target = temp; //overwrite the target effectively deleting it, since this is saving as a node this should also say the left/right if the child had any
		delete target->left; //remove the old child since this one now has that data

	}
	else if(target->hasRight())//has one child
	{
		vertex* temp = target->right;//save the right node to a pointer for easy transfer
		target = temp; //overwrite the target effectively deleting it
		delete target->right; //remove the old child since this one now has that data
	}
	else//no child easy peasy
	{
		delete target;
	}
}
template <typename T>
bool tBinaryTree<T>::vertex::search(const T& value, vertex*& found)
{
	//first our basic if else
	if(value == data) //this will be our determining check
	{
		found = *this;//change the found to the current vertex since this will become a recursive function
		return true; //return true that we found it
	}
	else if(value<data)
	{
		if(hasLeft())//if it fails this check it will simply exit this if statement and return at bottom since this is an if else
		{
			return left->search(value, found);
		}
	}
	else if(value>data)
	{
		if(hasRight())//refer to left check for logic behind this
		{
			return right->search(value, found);
		}
	}
	//this is the bottom of the method if it never finds the value it will simply return false here
	return false;
}
template <typename T>
 tBinaryTree<T> &tBinaryTree<T>::operator=(const tBinaryTree& other)
{
	 //need to implment
}
 template <typename T>
 void tBinaryTree<T>::destroyTree(vertex* point)
 {
	 if(point!=nullptr)
	 {
		 if (point->hasLeft()) //first check if a left exists don't want to call a method for a point that doesn't exist
		 {
			 destroyTree(point->left);//recall this method to remove the entire tree under our starting point
		 }
		 if(point->hasRight())//same as left but with right
		 {
			 destroyTree(point->right);
		 }
		 delete point;//finally remove the current called node
	 }
 }
 template <typename T>
 tBinaryTree<T>::vertex* tBinaryTree<T>::vertex::minValueNode(vertex* startNode)
 {
	 //I only need to get the data here since this is a leftmost node which means it will have no children
	 vertex* cur = node; //getting a good easy node to work from

	 //looping down to find the leftmost
	 while(cur && cur->left !=nullptr)
	 {
		 cur = cur->left;
	 }
	 return cur; //return the data
 }


