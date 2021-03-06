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

bool BinaryTree::addNode(const int key)
{
	return addNode(m_root, key) != nullptr;
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
			cout << "error printHorizontal: Tree is empty" << endl;
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
		std::cout << "error printVertical: Tree is empty" << std::endl;
		return;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	int significant = 1;
	int level = 1;
	int h = getHeight(subTreeRoot);

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
		else
		{
			cout << "X ";
		}
		return;
	}

	if (currentLevel == level) 
	{
		cout << subTreeRoot->key << " ";
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

void BinaryTree::destroy()
{
	destroy(m_root);
}

void BinaryTree::destroy(Node* subTreeRoot)
{
	if (subTreeRoot)
	{
		destroy(subTreeRoot->leftChild);
		destroy(subTreeRoot->rightChild);

		if (subTreeRoot == m_root)
			m_root = nullptr;

		delete subTreeRoot;

		
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

int BinaryTree::getHeight(const Node* subTreeRoot)
{
	if (subTreeRoot)
	{
		int left = getHeight(subTreeRoot->leftChild);
		int right = getHeight(subTreeRoot->rightChild);

		if (left > right)
			return left + 1;
		else
			return right + 1;
	}

	return 0;
}

int BinaryTree::getNumberOfNodes(const Node* subTreeRoot)
{
	int count = 0;
	if (subTreeRoot)
	{
		count++;
		count += getNumberOfNodes(subTreeRoot->leftChild);
		count += getNumberOfNodes(subTreeRoot->rightChild);
	}

	return count;
}

Node* BinaryTree::getNodeWithMinimumKey(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		std::cerr << "error min: Tree is empty";
		return nullptr;
	}

	Node* min = subTreeRoot;
	if (subTreeRoot->leftChild)
	{
		Node* minL = getNodeWithMinimumKey(subTreeRoot->leftChild);
		if (min->getKey() > minL->getKey())
		{
			min = minL;
		}
	}

	if (subTreeRoot->rightChild)
	{
		Node* minR = getNodeWithMinimumKey(subTreeRoot->rightChild);
		if (min->getKey() > minR->getKey())
		{
			min = minR;
		}
	}

	return min;
}

Node* BinaryTree::getNodeWithMaximumKey(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		std::cerr << "error max: Tree is empty";
		return nullptr;
	}

	Node* max = subTreeRoot;
	if (subTreeRoot->leftChild)
	{
		Node* maxL = getNodeWithMinimumKey(subTreeRoot->leftChild);
		if (max->getKey() < maxL->getKey())
		{
			max = maxL;
		}
	}

	if (subTreeRoot->rightChild)
	{
		Node* maxR = getNodeWithMinimumKey(subTreeRoot->rightChild);
		if (max->getKey() < maxR->getKey())
		{
			max = maxR;
		}
	}

	return max;
}

int BinaryTree::getHeight()
{
	return getHeight(m_root);
}

int BinaryTree::getNumberOfNodes()
{
	return getNumberOfNodes(m_root);
}

int BinaryTree::getMinimumKey()
{
	Node* node = getNodeWithMinimumKey(m_root);
	if (node)
		return node->getKey();

	return -1;
}

int BinaryTree::getMaximumKey()
{
	Node* node = getNodeWithMaximumKey(m_root);
	if (node)
		return node->getKey();

	return -1;
}

Node* BinaryTree::findParentByKey(Node* subTreeRoot, const int key)
{

	if (m_root->getKey() == key && m_root)
	{
		return nullptr;
	}

	if (subTreeRoot)
	{
		if (subTreeRoot->leftChild || subTreeRoot->rightChild)
		{
			if ((subTreeRoot->leftChild && subTreeRoot->leftChild->getKey() == key) || (subTreeRoot->rightChild && subTreeRoot->rightChild->getKey() == key))
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

Node* BinaryTree::findByKey(Node* subTreeRoot, const int key)
{
	if (subTreeRoot)
	{
		if (subTreeRoot->getKey() == key)
		{
			return subTreeRoot;
		}
		else
		{
			Node* left = findByKey(subTreeRoot->leftChild, key);
			Node* right = findByKey(subTreeRoot->rightChild, key);

			if (left && left->getKey() == key)
			{
				return left;
			}

			if (right && right->getKey() == key)
			{
				return right;
			}

			return nullptr;
		}
	}

	return nullptr;
}

bool BinaryTree::findAndDeleteByKey(Node* subTreeRoot, const int key)
{
	Node* toDelete = findByKey(subTreeRoot, key);
	Node* parent = findParentByKey(subTreeRoot, key);
	return deleteNode(toDelete, parent);
}

Node* BinaryTree::getNodeWithEmptyChild(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		std::cerr << "error getNodeWithEmptyChild: Tree is empty";
	}
	else
	{
		if (subTreeRoot->leftChild == nullptr || subTreeRoot->rightChild == nullptr)
		{
			return subTreeRoot;
		}
		else
		{
			int heightLeft = getHeight(subTreeRoot->leftChild);
			int heightRight = getHeight(subTreeRoot->rightChild);

			if (heightLeft < heightRight)
			{
				return getNodeWithEmptyChild(subTreeRoot->leftChild);
			}
			else if (heightLeft > heightRight)
			{
				return getNodeWithEmptyChild(subTreeRoot->rightChild);
			}
			else
			{
				int countLeft = getNumberOfNodes(subTreeRoot->leftChild);
				int countRight = getNumberOfNodes(subTreeRoot->rightChild);

				if (countLeft < countRight)
				{
					return getNodeWithEmptyChild(subTreeRoot->leftChild);
				}
				else
				{
					return getNodeWithEmptyChild(subTreeRoot->rightChild);
				}
			}
		}
	}
	
}

std::vector<int> BinaryTree::getAllKeys(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return std::vector<int>();

	std::vector<int> keys;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	keys.push_back(subTreeRoot->getKey());
	
	while (currentLevelNodes.size() != 0)
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				nextLevelNodes.push_back(node->leftChild);
				keys.push_back(node->leftChild->getKey());
			}
			
			if (node->rightChild)
			{
				nextLevelNodes.push_back(node->rightChild);
				keys.push_back(node->rightChild->getKey());
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return keys;
}

Node* BinaryTree::findParentByKey(const int key)
{
	return findParentByKey(m_root, key);
}

Node* BinaryTree::findByKey(const int key)
{
	return findByKey(m_root, key);
}

bool BinaryTree::deleteNode(Node* nodeToDelete, Node* parent)
{
	if (nodeToDelete == nullptr)
	{
		std::cerr << "error deleteNode: empty node" << std::endl;
		return false;
	}

	if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
	{
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
		if (parent)
		{
			if (parent->leftChild == nodeToDelete)
			{
				parent->leftChild = nodeToDelete->leftChild;
				Node* nodeToAdd = getNodeWithEmptyChild(parent);

				if (nodeToAdd->rightChild == nullptr)
				{
					nodeToAdd->rightChild = nodeToDelete->rightChild;
				}
				else
				{
					nodeToAdd->leftChild = nodeToDelete->rightChild;
				}
			}

			if (parent->rightChild == nodeToDelete)
			{
				parent->rightChild = nodeToDelete->rightChild;
				Node* nodeToAdd = getNodeWithEmptyChild(parent);

				if (nodeToAdd->leftChild == nullptr)
				{
					nodeToAdd->leftChild = nodeToDelete->leftChild;
				}
				else
				{
					nodeToAdd->rightChild = nodeToDelete->leftChild;
				}
			}
		}
		else
		{
			m_root = nodeToDelete->leftChild;
			Node* nodeToAdd = getNodeWithEmptyChild(m_root);
			if (nodeToAdd->rightChild == nullptr)
			{
				nodeToAdd->rightChild = nodeToDelete->rightChild;
			}
			else
			{
				nodeToAdd->leftChild = nodeToDelete->rightChild;
			}
		}
		delete nodeToDelete;

		return true;
	}





	return false;
}

bool BinaryTree::findAndDeleteByKey(const int key)
{
	return findAndDeleteByKey(m_root, key);
}

bool BinaryTree::isEmpty()
{
	return m_root == nullptr;
}

std::vector<int> BinaryTree::getAllKeys()
{
	return getAllKeys(m_root);
}

Node* BinaryTree::node(const int nodeIndex)
{
	return node(m_root, nodeIndex);
}
