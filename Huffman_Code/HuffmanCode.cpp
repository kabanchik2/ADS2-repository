#include "HuffmanCode.h"


#include <iostream>
#include <algorithm>
#include <map>

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

	//std::cout << allSymbols[97] << std::endl;

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


	while (nodes.size() != 1)
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
	}

	m_root = nodes.front();
}

double HuffmanCode::encode(const std::string originalText, std::string& codedText)
{
	if (originalText.empty())
	{
		return -1;
	}
	if (!m_root)
	{
		build(originalText);
	}

	double oldLenght = originalText.size() * 8;

	if (m_root->m_leftChild == nullptr && m_root->m_rightChild == nullptr)
	{
		codedText = std::string(m_root->m_frequency, '1');
		double newLenght = codedText.size();
		return (oldLenght / newLenght);
	}

	std::map<std::string, std::string> codes;

	storeCodes(m_root, "", codes);
	//printCodes(m_root, "", codes);

	for (auto i : originalText)
	{
		std::string s;
		s.push_back(i);
		codedText += codes[s];
		s.clear();
	}
		
	//std::cout << codedText << std::endl;

	//std::cout << oldLenght << " " << codedText.size() << " " << ((double)codedText.size() / oldLenght) << std::endl;
	double newLenght = codedText.size();
	return (oldLenght / newLenght);
}

bool HuffmanCode::decode(const std::string codedText, std::string& decodedText)
{

	if (m_root == nullptr)
	{
		return false;
	}

	if (m_root->m_leftChild == nullptr && m_root->m_rightChild == nullptr)
	{
		for (int i = 0; i < m_root->m_frequency; ++i)
		{
			decodedText += m_root->m_key;
		}

		return true;
	}
	else
	{
		HNode* tmp = m_root;
	
		for (int i = 0; i < codedText.size(); ++i)
		{
			if (codedText[i] == '0')
				tmp = tmp->m_leftChild;
			else
				tmp = tmp->m_rightChild;

			if (tmp->m_leftChild == nullptr && tmp->m_rightChild == nullptr)
			{
				decodedText += tmp->m_key;
				tmp = m_root;
			}
		}


		return true;
	}
	
	return false;
}

void HuffmanCode::printCodes(HNode* node, std::string str, std::map<std::string, std::string>& codes) const
{
	if (!node)
		return;

	if (!str.empty())
		std::cout << node->m_key << ": " << str << "\n";

	printCodes(node->m_leftChild, str + "0", codes);
	printCodes(node->m_rightChild, str + "1", codes);
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

void HuffmanCode::storeCodes(HNode* node, std::string str, std::map<std::string, std::string>& codes) const
{
	if (node == nullptr)
		return;

	if (!str.empty())
		codes[node->m_key] = str;

	storeCodes(node->m_leftChild, str + "0", codes);
	storeCodes(node->m_rightChild, str + "1", codes);
}

