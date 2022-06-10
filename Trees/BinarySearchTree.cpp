#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() : BinaryTree()
{
}

BinarySearchTree::BinarySearchTree(const const BinarySearchTree& other) : BinaryTree(other)
{
}

BinarySearchTree::~BinarySearchTree()
{
	destroy(m_root);
}

bool BinarySearchTree::addNode(const int key)
{
	if (m_root == nullptr)
	{
		m_root = new Node(key);
	}
	else
	{
		Node* tmp = m_root;
		while (tmp->leftChild && key < tmp->getKey() || tmp->rightChild && key >= tmp->getKey())
		{
			if (key < tmp->getKey())
			{
				tmp = tmp->leftChild;
			}
			else
			{
				tmp = tmp->rightChild;
			}
		}

		if (key < tmp->getKey())
		{
			Node* newLeftNode = new Node(key);
			tmp->leftChild = newLeftNode;
		}
		else
		{
			Node* newRightNode = new Node(key);
			tmp->rightChild = newRightNode;
		}
	}
	

	return true;
}

int BinarySearchTree::getMinimumKey()
{
	return getNodeWithMinimumKey(m_root)->getKey();
}

int BinarySearchTree::getMaximumKey()
{
	return getNodeWithMaximumKey(m_root)->getKey();
}

Node* BinarySearchTree::findByKey(const int key)
{
	if (m_root == nullptr)
	{
		return nullptr;
	}

	Node* tmp = m_root;
	while (tmp->leftChild && key < tmp->getKey() || tmp->rightChild && key > tmp->getKey())
	{
		if (key < tmp->getKey())
		{
			tmp = tmp->leftChild;
		}
		else
		{
			tmp = tmp->rightChild;
		}
	}

	if (key == tmp->getKey())
	{
		return tmp;
	}
	else
	{
		return nullptr;
	}
}

Node* BinarySearchTree::getNodeWithMinimumKey(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	Node* tmp = subTreeRoot;
	while (tmp->leftChild)
	{
		tmp = tmp->leftChild;
	}

	return tmp;
}

Node* BinarySearchTree::getNodeWithMaximumKey(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	Node* tmp = subTreeRoot;
	while (tmp->rightChild)
	{
		tmp = tmp->rightChild;
	}

	return tmp;
}
