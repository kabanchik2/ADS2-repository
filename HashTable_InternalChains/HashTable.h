#pragma once

struct HashCell
{
	bool m_isExists;
	int m_key;
	int m_value;

	int indexOfNext;
};


class HashTable
{
public:
	HashTable(int size);
	~HashTable();

	bool addKey(int key, int value);
	bool findKey(int key);
	HashCell* findCellWithKey(int key);
	bool deleteKey(int key);

	void printTable();

	int getSize();

private:
	int hash(int key, int size);
	int hash1(int key);
	void resize(int newSize);

	HashCell* m_hashCell;
	int m_actualSize = 0;
	int m_size;
};