#pragma once
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

		bool hasLeft() const; //checks if there is a left node
		bool hasRight() const; //checks if there is a right node
		vertex();//default constructor
		vertex(T data);
	};

	tBinaryTree(); //tree constructor
	tBinaryTree(const tBinaryTree& other); //copy constructor
	~tBinaryTree();//tree deconstructor

	void insert(const T& val); //inserts the element as a leaf, unless there is a duplicate number on the tree

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
tBinaryTree<T>::tBinaryTree(const tBinaryTree &other)
{
	root = nullptr; //same as normal constructor

	std::vector<vertex> copy;
    std::vector<vertex*> check;
}
template<typename T>
tBinaryTree<T>::~tBinaryTree()
{
	if(root !=nullptr)
	{
		delete root; //gonna need something to go through the tree and delete the vertices
	}
}




