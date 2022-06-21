#include "HuffmanCode.h"

#include <iostream>
#include <algorithm>

HuffmanCode::~HuffmanCode()
{
	destroyTree(m_root);
}

void HuffmanCode::build(const std::string text)
{
	destroyTree(m_root);

	const int nSymbols = 256;
	int* allSymbols = new int[nSymbols];
	for (auto i = 0; i < nSymbols; ++i)
	{
		allSymbols[i] = 0;
	}

	for (auto symbol : text)
	{
		++allSymbols[(unsigned char)symbol];
	}

	std::list<HNode*> nodes;
	for (int i = 0; i < nSymbols; ++i)
	{
		if (allSymbols[i])
		{
			HNode* tmp = new HNode(allSymbols[i]);
			tmp->m_key.push_back((unsigned char)i);
			nodes.push_back(tmp);
		}
	}

	nodes.sort([](const HNode* first, const HNode* second)
		{return first->m_frequency < second->m_frequency; });

	std::list<HNode*>::iterator nodesIterator;


	while (nodes.size() > 1)
	{
		HNode* firstNode = nodes.front();
		nodes.pop_front();
		HNode* secondNode = nodes.front();
		nodes.pop_front();

		HNode* newNode = new HNode(firstNode->m_frequency + secondNode->m_frequency);
		newNode->m_leftChild = firstNode;
		newNode->m_rightChild = secondNode;
		newNode->m_key += firstNode->m_key;
		newNode->m_key += secondNode->m_key;

		if (!nodes.size())
		{
			nodes.push_back(newNode);
		}
		else if (newNode->m_frequency <= nodes.front()->m_frequency)
		{
			nodes.push_front(newNode);
		}
		else if (newNode->m_frequency >= nodes.back()->m_frequency)
		{
			nodes.push_back(newNode);
		}
		else
		{
			nodesIterator = nodes.begin();

			for (auto node : nodes)
			{
				if (node->m_frequency > newNode->m_frequency)
				{
					nodes.insert(nodesIterator, newNode);
					break;
				}
				nodesIterator++;
			}
		}

		/*for (auto node : nodes)
		{
			std::cout << node->m_key << " " << node->m_frequency << std::endl;
		}*/
	}

	m_root = nodes.front();
}

void HuffmanCode::destroyTree(HNode* subTreeRoot)
{
	if (subTreeRoot)
	{
		destroyTree(subTreeRoot->m_leftChild);
		destroyTree(subTreeRoot->m_rightChild);

		if (subTreeRoot == m_root)
			m_root = nullptr;

		delete subTreeRoot;
	}
}
