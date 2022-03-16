#include "BinaryTree.h"

#include <iostream>
#include <random>
#include <vector>

BinaryTree::BinaryTree(const BinaryTree& other)
{
	copyTree(*other.m_root, m_root);
}

Node* BinaryTree::getRoot()
{
	return m_root;
}

Node* BinaryTree::addNode(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
	{
		if (m_root == nullptr)
		{
			m_root = new Node(key);
			return m_root;
		}
		else
		{
			return nullptr;
		}
	}

	if (subTreeRoot->leftChild == nullptr)
	{
		subTreeRoot->leftChild = new Node(key);
		return subTreeRoot->leftChild;
	}
	else if (subTreeRoot->rightChild == nullptr)
	{
		subTreeRoot->rightChild = new Node(key);
		return subTreeRoot->rightChild;
	}
	else
	{
		if (rand() % 2)
		{
			return addNode(subTreeRoot->leftChild, key);
		}
		else
		{
			return addNode(subTreeRoot->rightChild, key);
		}
	}
}

void BinaryTree::printHorizontal()
{
	printHorizontal(m_root);
}

void BinaryTree::printHorizontal(Node* subTreeRoot, const int level)
{
	using std::cout;
	using std::endl;

	if (subTreeRoot == nullptr) 
	{
		if (subTreeRoot == m_root) 
		{
			cout << "Tree is empty" << endl;
		}
		return;
	}

	printHorizontal(subTreeRoot->rightChild, level + 1);

	for (int i = 0; i < level; i++)
		cout << "   ";

	cout << subTreeRoot->key << endl;

	printHorizontal(subTreeRoot->leftChild, level + 1);
}

void BinaryTree::printLevel(const int level)
{
	printLevel(m_root, level, 0);
}

void BinaryTree::printLevel(Node* subTreeRoot, const int level, const int currentLevel)
{
	using std::cout;
	using std::endl;

	if (subTreeRoot == nullptr) 
	{
		if (subTreeRoot == m_root)
		{
			cout << "Tree is empty" << endl;
		}
		return;
	}

	if (currentLevel == level) 
	{
		cout << subTreeRoot->key << "   ";
	}
	else if (currentLevel < level) 
	{
		printLevel(subTreeRoot->leftChild, level, currentLevel + 1);
		printLevel(subTreeRoot->rightChild, level, currentLevel + 1);
	}
}

Node* BinaryTree::node(Node* subTreeRoot, int nodeIndex)
{
	if (nodeIndex == 0)
	{
		return subTreeRoot;
	}
	else if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0 && nodeIndex >= currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				nextLevelNodes.push_back(node->rightChild);
			}
		}

		nodeIndex -= currentLevelNodes.size();
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (currentLevelNodes.size() == 0)
	{
		return nullptr;
	}
	else
	{
		return currentLevelNodes[nodeIndex];
	}
}

void BinaryTree::copyTree(const Node& other, Node*& destination)
{
	if (&other == nullptr)
	{
		destination = nullptr;
	}
	else
	{
		destination = new Node(other.key);
		copyTree(*other.leftChild, destination->leftChild);
		copyTree(*other.rightChild, destination->rightChild);
	}
}

Node* BinaryTree::node(const int nodeIndex)
{
	return node(m_root, nodeIndex);
}
