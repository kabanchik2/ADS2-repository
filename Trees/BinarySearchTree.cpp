#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() : BinaryTree()
{
}

BinarySearchTree::BinarySearchTree(const const BinarySearchTree& other) : BinaryTree(other)
{
}

BinarySearchTree::~BinarySearchTree()
{
	destroy(this->getRoot());
}

