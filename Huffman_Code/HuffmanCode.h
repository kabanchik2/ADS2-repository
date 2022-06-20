#pragma once

#include <string>
class HNode
{
public:

	HNode() = default;
	HNode(std::string key, int frequency, HNode* left = nullptr, HNode* right = nullptr);

private:
	int m_frequency;
	std::string m_key;
	HNode* m_left;
	HNode* m_right;

};



class HuffmanCode
{
};

