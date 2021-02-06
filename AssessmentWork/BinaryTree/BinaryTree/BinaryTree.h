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
		void remove(vertex* target); //removes a vertex at the target, need to add
		void insert(const T& val); //inserts the element as a leaf, unless there is a duplicate number on the tree
		bool search(const T& value, vertex*& found); //looks for a vertex and adds it to found then returns if it found the vertex or not
		bool hasLeft() const; //checks if there is a left node
		bool hasRight() const; //checks if there is a right node
	};

	tBinaryTree(); //tree constructor
	tBinaryTree(const tBinaryTree& other); //copy constructor, need to be implmented
	~tBinaryTree();//tree deconstructor

	tBinaryTree& operator=(const tBinaryTree& other);
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
{}
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


