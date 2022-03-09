#pragma once

#include <vector>

struct Node
{
	Node(const int key = 13, Node* leftChild = nullptr, Node* rightChild = nullptr) :
		key(key),
		leftChild(leftChild),
		rightChild(rightChild)
	{}

	int key = 10;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
};

class  BinaryTree
{
public:
	BinaryTree() = default;

	Node* getRoot();
	Node* addNode(Node* subTreeRoot, const int key);

	void printHorizontal();
	void printHorizontal(Node* subTreeRoot, const int level = 0);

	void printLevel(const int level);
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0);

	Node* node(Node *subTreeRoot, int nodeIndex);
	Node* node(const int nodeIndex);

private:
	Node* m_root = nullptr;
};