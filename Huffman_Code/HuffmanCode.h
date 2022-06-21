#pragma once

#include <string>
#include <list>

class HuffmanCode
{
public:
	class HNode
	{
	public:

		HNode() = default;
		HNode(int frequency = 0, std::string key = std::string(),
			HNode* left = nullptr, HNode* right = nullptr) :
			m_frequency(frequency),
			m_key(key),
			m_leftChild(left),
			m_rightChild(right)
		{}

		~HNode() = default;

		int m_frequency = 0;
		std::string m_key;
		HNode* m_leftChild = nullptr;
		HNode* m_rightChild = nullptr;

	};

	HuffmanCode() = default;
	~HuffmanCode();

	void build(const std::string text);





	void destroyTree(HNode* subTreeRoot);

private:
	HNode* m_root;
};

