#include "HuffmanCode.h"

HNode::HNode(std::string key, int frequency, HNode* left, HNode* right)
{
	m_key = key;
	m_frequency = frequency;
	m_left = left;
	m_right = right;
}

