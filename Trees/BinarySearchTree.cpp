#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() : BinaryTree()
{
}

BinarySearchTree::BinarySearchTree(const const BinarySearchTree& other) : BinaryTree(other)
{
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

Node* BinarySearchTree::findByKey(const int key)
{
	return findByKey(m_root, key);
}

bool BinarySearchTree::findAndDeleteByKey(const int key)
{
	return findAndDeleteByKey(m_root, key);
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

Node* BinarySearchTree::findByKey(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	Node* tmp = subTreeRoot;
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

bool BinarySearchTree::deleteNode(Node* nodeToDelete, Node* parent)
{
	if (nodeToDelete == nullptr)
	{
		return false;
	}

	if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
	{
		if (parent && parent->leftChild == nodeToDelete)
		{
			parent->leftChild = nullptr;
		}

		if (parent && parent->rightChild == nodeToDelete)
		{
			parent->rightChild = nullptr;
		}
		
		if (!parent)
			m_root = nullptr;

		delete nodeToDelete;

		return true;
	}

	if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
	{
		if (parent && parent->leftChild == nodeToDelete)
		{
			parent->leftChild = nodeToDelete->rightChild;
		}

		if (parent && parent->rightChild == nodeToDelete)
		{
			parent->rightChild = nodeToDelete->rightChild;
		}

		if (!parent)
			m_root = nodeToDelete->rightChild;

		delete nodeToDelete;

		return true;
	}

	if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
	{
		if (parent && parent->leftChild == nodeToDelete)
		{
			parent->leftChild = nodeToDelete->leftChild;
		}

		if (parent && parent->rightChild == nodeToDelete)
		{
			parent->rightChild = nodeToDelete->leftChild;
		}

		if (!parent)
			m_root = nodeToDelete->leftChild;

		delete nodeToDelete;

		return true;
	}

	//ѕодсасываем на место удал€емого самый маленький элемент с правой части дерева
	if (nodeToDelete->leftChild && nodeToDelete->rightChild)
	{
		Node* toAdd = getNodeWithMinimumKey(nodeToDelete->rightChild);
		Node* parentToAdd = getParentOfMinimalNode(nodeToDelete->rightChild);

		if (parentToAdd)
		{
			parentToAdd->leftChild = toAdd->rightChild;
			toAdd->leftChild = nodeToDelete->leftChild;
			toAdd->rightChild = nodeToDelete->rightChild;
		}
		else
		{
			toAdd->leftChild = nodeToDelete->leftChild;
			toAdd->rightChild = nullptr;
		}

		if (parent && parent->leftChild == nodeToDelete)
			parent->leftChild = toAdd;

		if (parent && parent->rightChild == nodeToDelete)
			parent->rightChild = toAdd;

		if (!parent)
			m_root = toAdd;

		delete nodeToDelete;

		return true;
	}

	return false;
}

bool BinarySearchTree::findAndDeleteByKey(Node* subTreeRoot, const int key)
{
	Node* toDelete = findByKey(subTreeRoot, key);
	Node* parent = findParentByKey(subTreeRoot, key);
	return deleteNode(toDelete, parent);
}

Node* BinarySearchTree::findParentByKey(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
		return nullptr;

	if ((subTreeRoot->leftChild && subTreeRoot->leftChild->getKey() == key) || (subTreeRoot->rightChild && subTreeRoot->rightChild->getKey() == key))
	{
		return subTreeRoot;
	}
	else
	{
		Node* left = nullptr;
		Node* right = nullptr;

		if (subTreeRoot->leftChild && key < subTreeRoot->getKey())
		{
			left = findParentByKey(subTreeRoot->leftChild, key);
		}
		else if (subTreeRoot->rightChild)
		{
			right = findParentByKey(subTreeRoot->rightChild, key);
		}

		if (left)
			return left;

		if (right)
			return right;
	}

	return nullptr;
}

Node* BinarySearchTree::getParentOfMinimalNode(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr || subTreeRoot->rightChild == nullptr)
		return nullptr;

	Node* tmp = subTreeRoot;
	while (tmp->leftChild && tmp->leftChild->leftChild)
		tmp = tmp->leftChild;

	return tmp;
}
