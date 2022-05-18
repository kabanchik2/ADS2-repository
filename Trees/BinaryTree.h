#pragma once

#include <vector>

struct Node
{
	Node(const int key = 13, Node* leftChild = nullptr, Node* rightChild = nullptr) :
		key(key),
		leftChild(leftChild),
		rightChild(rightChild)
	{}

	int getKey() { return key; };
	int getChildsNumber()
	{
		int nChilds = 0;
		if (leftChild)
			nChilds++;
		if (rightChild)
			nChilds++;

		return nChilds;
	}

	int key = 10;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
};

class  BinaryTree
{
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();

	Node* getRoot();
	Node* addNode(Node* subTreeRoot, const int key);

	void printHorizontal();
	void printVertical();

	void printLevel(const int level);
	

	Node* node(const int nodeIndex);
	

	void copyTree(const Node& other, Node*& destination);
	void destroy(Node* subTreeRoot);
	void destroyChildTrees(Node* parentNode);

	int getDepth();

	Node* findParentByKey(const int key);

	bool deleteNode(Node* nodeToDelete);


protected:
	void printHorizontal(Node* subTreeRoot, const int level = 0);
	void printVertical(Node* subTreeRoot);

	void printLevel(Node* subTreeRoot, const int level, const int currentLevel = 0);

	Node* node(Node* subTreeRoot, int nodeIndex);

	int getDepth(const Node* subTreeRoot);

	Node* findParentByKey(Node* subTreeRoot, const int key);


private:
	Node* m_root = nullptr;

};