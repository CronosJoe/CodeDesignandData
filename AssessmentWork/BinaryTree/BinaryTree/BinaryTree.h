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
		
		bool hasLeft() const; //checks if there is a left node
		bool hasRight() const; //checks if there is a right node
		
	};
	//need to fix implemented wrong last time
	void remove(vertex* target); //removes a vertex at the target
	void insert(const T& val); //inserts the element as a leaf, unless there is a duplicate number on the tree
	bool search(const T& value, vertex*& found); //looks for a vertex and adds it to found then returns if it found the vertex or not
	vertex* minValueNode(vertex* startNode); //finds the leftmost node starting at a specified point
	tBinaryTree(); //tree constructor
	tBinaryTree(const tBinaryTree& other); //copy constructor, need to be implmented
	~tBinaryTree();//tree deconstructor

	tBinaryTree& operator=(const tBinaryTree& other); //need to add
	void destroyTree(vertex* point); //deletes everything under a specific vertex
	vertex* root;
private:
	std::vector<vertex*>  vertices; //a vector of pointers to vertices

	
	vertex* cur; //making this for the remove/insert/search
};

template <typename T>
bool tBinaryTree<T>::vertex::hasLeft() const
{
	return this->left != NULL; //pretty basic it will return true if there is a vertex on the left and false if there isn't
}
template <typename T>
bool tBinaryTree<T>::vertex::hasRight() const
{
	return this->right != NULL; //reverse of the left one
}

//constructors
template <typename T>
tBinaryTree<T>::vertex::vertex()
{
	//since there is no data in there yet lets just NULL the two vertices and just leave the data be until we add our first real node
	left = NULL;
	right = NULL;
}
template <typename T>
tBinaryTree<T>::vertex::vertex(T nData)
{
	data = nData;
	left = NULL;
	right = NULL;
}
template <typename T>
tBinaryTree<T>::tBinaryTree()
{
	root = NULL; //pretty basic since this is the only variable until we actually have vertices
}
template<typename T>
tBinaryTree<T>::tBinaryTree(const tBinaryTree &other)//constructor for copying another binary tree into this one
{
	//I should be able to do this by getting the values out of the other tree and just let my insert method handle the rest
}
template<typename T>
tBinaryTree<T>::~tBinaryTree()//this will deconstruct the tree
{
	if(root !=NULL)
	{
		destroyTree(root); //this should eliminate the entire tree if I did it correctly
	}
}
template<typename T>
void tBinaryTree<T>::insert(const T& val)//time to drop in the vals
{
	if(cur == NULL)//this will only be true on the original call of this method
	{
		cur = root;
	}
	if(root == NULL) //if there is no value set this as the root.
	{
		vertex* newRoot = new vertex(val);
		root = newRoot;
		return;
	}
	if(val==cur->data)//if it matches somewhere on the tree we return out
	{
		return;
	}
	else if(val<cur->data) //left side
	{
		if(!cur->hasLeft())//check if something is there
		{
			vertex* tmp = new vertex;
			cur->left = tmp;//make the new vertex and shove everything into it
			tmp->data = val;
			tmp->left = NULL;//nulling these cause they will be empty to start
			tmp->right = NULL;
			vertices.push_back(tmp);//add them to vertices when I make them
			
		}else
		{
			cur = cur->left;
			this->insert(val);//continue down the line, this doesn't work cause there is no way to tell the cur
		}
	}
	else if(val> cur->data)//right side
	{
		if (!cur->hasRight())//check if something is there
		{
			vertex* tmp = new vertex;
			cur->right = tmp;//make the new vertex and shove everything into it
			tmp->data = val;
			tmp->left = NULL;//nulling these cause they will be empty to start
			tmp->right = NULL;
			vertices.push_back(tmp);//I should update this idea but tbh I haven't at all
		}
		else
		{
			cur = cur->right;
			this->insert(val);//continue down the line
		}
	}
	cur = NULL; //reset the entire system
	return; //because the entire thing is if else statements once they return to this iteration of the recursion they will simply exit their if and all end up here
}
template <typename T>
void tBinaryTree<T>::remove(vertex* target)
{
	//we also have to assume the target exists or this entire method's logic doesn't work
	//very first edge case
	if(root->data == target->data)
	{
		delete target;
		root = NULL; //we have to set root back to NULL to avoid annoying error
		return;
	}
	cur = root;//this will us resolve the error by not leaving any empty pointers not null
	vertex* tmp = new vertex();
	int savingInt = -1;//at -1 something went wrong
	while (cur != NULL)//a psuedo search function
	{
		//the only thing this loop will check
		if(cur->data < target->data)//go to the right side
		{
			if(cur->right->data == target->data)
			{
				tmp = cur;//save the parent of the child about to be deleted
				savingInt = 1;//for right side
				cur = NULL;//end the loop
			}else
			{
				cur = cur->right;//continue the search
			}
		}
		else if (cur->data > target->data) //go to the left side
		{
			if (cur->left->data == target->data)
			{
				tmp = cur;//save the parent of the child about to be deleted
				savingInt = 2;//for left side
				cur = NULL;//end the loop
			}
			else
			{
				cur = cur->left;//continue the search
			}
		}
		
	}
	//THE ACTUAL REMOVE FUNCTION
	//first check for children
	if (target->hasLeft() && target->hasRight())//if this comes out to true then we need to do the difficult solution of finding the smallest leftmost node and bringing it up
	{
		//okay first we gotta find the left most node on the right side so that the tree still works
		vertex* temp = minValueNode(target->right);
		//now that we have our node we just replace and delete just like if we had 1 child node
		T tmpData = temp->data;
		remove(temp); //delete that leftmost node now that we have moved its data
		target->data = tmpData; //replace
		
	}
	else if (target->hasLeft())//has one child on the left
	{
		vertex* leftSidePnt = target->left;//save the left node to a pointer for easy transfer
		if (tmp->data < target->data)
		{
			tmp->right = leftSidePnt;
		}
		else
		{
			tmp->left = leftSidePnt;
		}
		delete target; //remove the old child since this one now has that data
	}
	/*
	insert 5
	insert 8
	insert 6

						5
									8
								6		9
	*/
	else if (target->hasRight())//has one child on the right
	{
		vertex* rightSidePnt = target->right;//save the right node to a pointer for easy transfer
		if(tmp->data<target->data)
		{
			tmp->right = rightSidePnt;
		}else
		{
			tmp->left = rightSidePnt;
		}
		delete target; //remove the old child since this one now has that data
	}
	else//no child easy peasy
	{
		delete target;
		switch(savingInt)//right = 1, left = 2
		{
		case 1:
			tmp->right = NULL;
			break;
		case 2:
			tmp->left = NULL;
			break;
		}
	}
}
template <typename T>
bool tBinaryTree<T>::search(const T& value, vertex*& found)
{
	if(root == NULL)//if this activates I'll just return false, not much else I can do there
	{
		return false;
	}
	if (cur == NULL)//setting the current
	{
		cur = root;
	}
	while(cur!=NULL) //if I make it to the end this will become NULL cause it can hit a point where there is nothing else in tree
	{
		if(cur->data==value) //once it has found the value this if will activate
		{
			found = cur;//seting found to the current vertex
			cur = NULL;//remember to do this
			return true;
		}
		else if(cur->data<value) //goes to right
		{
			if(cur->hasRight())
			{
				cur = cur->right; //setting this up for next loop iteration
			}
			else//to get here it has to have hit the bottom of the tree
			{
				cur = NULL; //ending the loop so it can return false
			}
		}
		else//cur data would have to be more than the value to reach this point
		{
			//goes to left
			if (cur->hasLeft())
			{
				cur = cur->left; //setting this up for next loop iteration
			}
			else//to get here it has to have hit the bottom of the tree
			{
				cur = NULL; //ending the loop so it can return false
			}
		}
	}
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
	 if(point!=NULL)
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
 typename tBinaryTree<T>::vertex* tBinaryTree<T>::minValueNode(vertex* startNode)
 {
	 //I only need to get the data here since this is a leftmost node which means it will have no children
	 vertex* current = startNode; //getting a good easy node to work from

	 //looping down to find the leftmost
	 while(current && current->left !=NULL)
	 {
		 current = current->left;
	 }
	 return current; //return the data
 }


