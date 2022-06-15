// Trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//#include "BinaryTree.h"
#include "BinarySearchTree.h"

bool testSearchTree(int size)
{
	int failedCase = 0;
	BinarySearchTree searchTree;
	std::vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTree.addNode(i);
		nodesKeys.push_back(i);
	}


	int index, key;


	while (nodesKeys.size()) {
		//	index = rand() % nodesKeys.size();
		//	nodesKeys.erase(nodesKeys.begin() + index);
		//	if (!searchTree.deleteKnot(searchTree.getRoot(), index)) {
		//		failedCase = 1;
		//		break;
		//	}


			/*if (testSearchTree(searchTree, nodesKeys.size())) {
				failedCase = 2;
				break;
			}*/


		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTree.findAndDeleteByKey(key)) {
				failedCase = 3;
				break;
			}


			/*if (testSearchTree(searchTree, nodesKeys.size())) {
				failedCase = 4;
				break;
			}*/
		}
	}

	if (failedCase || !searchTree.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}


		std::cout << size << " " << searchTree.getNumberOfNodes() << std::endl;
		searchTree.printHorizontal();
		std::cout << std::endl;
		std::cout << std::endl;




	}
	return (failedCase == 0);
}

bool testSearchTreeAsBinaryTree(int size)
{
	int failedCase = 0;
	BinarySearchTree searchTree;
	BinaryTree& searchTreeRef = searchTree;
	std::vector<int> nodesKeys;


	for (int i = 0; i < size; ++i) {
		searchTreeRef.addNode(i);
		nodesKeys.push_back(i);
	}


	int index, key;


	while (nodesKeys.size()) {
		/*index = rand() % nodesKeys.size();
		nodesKeys.erase(nodesKeys.begin() + index);
		if (!searchTreeRef.deleteKnot(searchTreeRef.getRoot(), index)) {
			failedCase = 1;
			break;
		}*/


		/*if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
			failedCase = 2;
			break;
		}*/


		if (nodesKeys.size()) {
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			if (!searchTreeRef.findAndDeleteByKey(key)) {
				failedCase = 3;
				break;
			}


			/*if (testSearchTreeAsBinaryTree(searchTreeRef, nodesKeys.size())) {
				failedCase = 4;
				break;
			}*/
		}
	}


	if (failedCase || !searchTreeRef.isEmpty()) {
		if (!failedCase) {
			failedCase = -1;
		}


		std::cout << size << " " << searchTreeRef.getNumberOfNodes() << std::endl;
		searchTreeRef.printHorizontal();
		std::cout << std::endl;
		std::cout << std::endl;




	}
	return (failedCase == 0);
}



int main()
{
	srand(time(0));

	BinarySearchTree bst;

	/*int key;
	for (int i = 0; i < 10; i++)
	{
		key = 1 + rand() % 15;
		bst.addNode(key);
	}*/

	//

	/*bst.addNode(5);
	bst.addNode(2);
	bst.addNode(8);
	bst.addNode(1);
	bst.addNode(3);
	bst.addNode(6);
	bst.addNode(10);
	bst.addNode(9);
	bst.addNode(10);

	bst.printVertical();*/

	//bst.findAndDeleteByKey(5);

	//bst.printVertical();

	std::cout << std::endl;
	std::cout << "min: " << bst.getMinimumKey() << 
				" max: " << bst.getMaximumKey() << std::endl;

	//BinaryTree* tree = &bst;

	//tree->destroy();

	//tree->addNode(5);
	//tree->addNode(2);
	//tree->addNode(8);
	//tree->addNode(1);
	//tree->addNode(3);
	//tree->addNode(6);
	//tree->addNode(10);
	//tree->addNode(9);
	//tree->addNode(10);

	//tree->printVertical();

	//tree->findAndDeleteByKey(8);

	//tree->printVertical();

	return testSearchTree(150) &&
	testSearchTreeAsBinaryTree(150);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
