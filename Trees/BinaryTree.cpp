#include "BinaryTree.h"

#include <iostream>
#include <random>
#include <vector>

BinaryTree::BinaryTree(const BinaryTree& other)
{
	copyTree(*other.m_root, m_root);
}

BinaryTree::~BinaryTree()
{
	destroy(m_root);
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

void BinaryTree::printVertical(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		std::cout << "Tree is empty" << std::endl;
		return;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	int significant = 1;
	int level = 1;
	int h = getDepth(subTreeRoot);

	while (significant != 0)
	{
		for (int i = 0; i < currentLevelNodes.size(); i++)
		{
			if (i == 0)
				for (int j = 0; j < pow(2, h - level); j++)
					std::cout << " ";
			else
				for (int j = 0; j < pow(2, h - level) + pow(2, h - level) - 1; j++)
					std::cout << " ";

			if (currentLevelNodes[i])
				std::cout << currentLevelNodes[i]->getKey();
			else
				std::cout << "X";
		}
		std::cout << std::endl;

		significant = 0;
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes) {
			if (node)
			{
				if (node->leftChild)
					significant++;
				if (node->rightChild)
					significant++;

				nextLevelNodes.push_back(node->leftChild);
				nextLevelNodes.push_back(node->rightChild);
			}
			else
			{
				nextLevelNodes.push_back(nullptr);
				nextLevelNodes.push_back(nullptr);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
		level++;
	}
}

void BinaryTree::printVertical()
{
	printVertical(m_root);
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

void BinaryTree::destroy(Node* subTreeRoot)
{
	if (subTreeRoot)
	{
		destroy(subTreeRoot->leftChild);
		destroy(subTreeRoot->rightChild);

		delete subTreeRoot;

		if (subTreeRoot == m_root)
			m_root = nullptr;
	}
}

void BinaryTree::destroyChildTrees(Node* parentNode)
{
	if (parentNode)
	{
		if (parentNode->leftChild)
			destroy(parentNode->leftChild);

		if (parentNode->rightChild)
			destroy(parentNode->rightChild);
	}
	
	parentNode->leftChild = nullptr;
	parentNode->rightChild = nullptr;
}

int BinaryTree::getDepth(const Node* subTreeRoot)
{
	if (subTreeRoot)
	{
		int left = getDepth(subTreeRoot->leftChild);
		int right = getDepth(subTreeRoot->rightChild);

		if (left > right)
			return left + 1;
		else
			return right + 1;
	}

	return 0;
}

int BinaryTree::getDepth()
{
	return getDepth(m_root);
}

Node* BinaryTree::findParentByKey(Node* subTreeRoot, const int key)
{

	if (m_root->getKey() == key)
	{
		return nullptr;
	}

	if (subTreeRoot)
	{
		if (subTreeRoot->leftChild && subTreeRoot->rightChild)
		{
			if (subTreeRoot->leftChild->getKey() == key || subTreeRoot->rightChild->getKey() == key)
			{
				return subTreeRoot;
			}
			else
			{
				Node* left = findParentByKey(subTreeRoot->leftChild, key);
				Node* right = findParentByKey(subTreeRoot->rightChild, key);

				if (left)
					return left;

				if (right)
					return right;
			}
		}
	}

	return nullptr;
}

Node* BinaryTree::findParentByKey(const int key)
{
	return findParentByKey(m_root, key);
}

bool BinaryTree::deleteNode(Node* nodeToDelete)
{
	if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
	{
		Node* parent = findParentByKey(nodeToDelete->getKey());

		if (parent)
		{
			if (parent->leftChild == nodeToDelete)
				parent->leftChild = nullptr;
			
			if (parent->rightChild == nodeToDelete)
				parent->rightChild = nullptr;
		}
		else
		{
			m_root = nullptr;
		}

		delete nodeToDelete;

		return true;
	}

	if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
	{
		Node* parent = findParentByKey(nodeToDelete->getKey());

		if (parent)
		{
			if (parent->leftChild == nodeToDelete)
				parent->leftChild = nodeToDelete->rightChild;

			if (parent->rightChild == nodeToDelete)
				parent->rightChild = nodeToDelete->rightChild;
		}
		else
		{
			m_root = nodeToDelete->rightChild;
		}

		delete nodeToDelete;

		return true;
	}

	if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
	{
		Node* parent = findParentByKey(nodeToDelete->getKey());

		if (parent)
		{
			if (parent->leftChild == nodeToDelete)
				parent->leftChild = nodeToDelete->leftChild;

			if (parent->rightChild == nodeToDelete)
				parent->rightChild = nodeToDelete->leftChild;
		}
		else
		{
			m_root = nodeToDelete->leftChild;
		}

		delete nodeToDelete;

		return true;
	}

	if (nodeToDelete->leftChild && nodeToDelete->rightChild)
	{
		Node* parent = findParentByKey(nodeToDelete->getKey());

		if (parent)
		{
			if (parent->leftChild == nodeToDelete)
			{
				///TODO
			}

			if (parent->rightChild == nodeToDelete)
			{
				///TODO
			}
		}
	}








	return false;
}

Node* BinaryTree::node(const int nodeIndex)
{
	return node(m_root, nodeIndex);
}
