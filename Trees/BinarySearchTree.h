#pragma once

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const const BinarySearchTree& other);
	~BinarySearchTree();
	
	bool addNode(const int key) override;

	int getMinimumKey() override;
	int getMaximumKey() override;

	Node* findByKey(const int key) override;

protected:
	Node* getNodeWithMinimumKey(Node* subTreeRoot) override;
	Node* getNodeWithMaximumKey(Node* subTreeRoot) override;

};

