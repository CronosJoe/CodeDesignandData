#include "BinaryTree.h"
#include <iostream>
int main()
{
	tBinaryTree<int> test = tBinaryTree<int>();
	test.insert(3);
	test.insert(5);
	test.insert(2);
	test.insert(4);
	test.insert(6);

	int testInt = test.root->right->data;
	std::cout << testInt << std::endl;
	test.remove(test.root->right);
	testInt = test.root->right->data;
	std::cout << testInt << std::endl;
	return 0;
}