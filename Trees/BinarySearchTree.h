#pragma once

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const const BinarySearchTree& other);
	~BinarySearchTree() override = default;
	
	bool addNode(const int key) override;

	Node* findByKey(const int key) override;

	bool findAndDeleteByKey(const int key) override;

protected:
	Node* getNodeWithMinimumKey(Node* subTreeRoot) override;
	Node* getNodeWithMaximumKey(Node* subTreeRoot) override;

	Node* findByKey(Node* subTreeRoot, const int key) override;

	bool deleteNode(Node* nodeToDelete, Node* parent) override;
	bool findAndDeleteByKey(Node* subTreeRoot, const int key) override;

	Node* findParentByKey(Node* subTreeRoot, const int key) override;

	Node* getParentOfMinimalNode(Node* subTreeRoot);
};

