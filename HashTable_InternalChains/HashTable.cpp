#include "HashTable.h"

#include <math.h>
#include <iostream>

HashTable::HashTable(int size)
{
	m_hashCell = new HashCell[size];
	m_size = size;

	for (int i = 0; i < size; ++i)
	{
		m_hashCell[i].m_isExists = false;
		m_hashCell[i].indexOfNext = -1;
	}
}

HashTable::~HashTable()
{
	delete[]m_hashCell;
}

bool HashTable::addKey(int key, int value)
{
	int index = hash(key, m_size);
	//int index = hash1(key);



	if (m_hashCell[index].m_isExists == false || m_hashCell[index].m_key == key)
	{
		
		m_actualSize++;
		m_hashCell[index].m_key = key;
		m_hashCell[index].m_value = value;
		m_hashCell[index].m_isExists = true;

		return true;
	}

	int current = m_size - 1;
	while (current >= 0 && m_hashCell[current].m_isExists && m_hashCell[current].m_key != key)
	{
		--current;
	}

	if (current == -1)
	{
		resize(m_size*2);
		return addKey(key, value);
	}

	m_actualSize++;
	m_hashCell[current].m_key = key;
	m_hashCell[current].m_value = value;
	m_hashCell[current].m_isExists = true;

	while (m_hashCell[index].indexOfNext != -1)
	{
		index = m_hashCell[index].indexOfNext;
	}

	m_hashCell[index].indexOfNext = current;
	

	return true;
}

void HashTable::printTable()
{
	if (m_actualSize == 0)
	{
		std::cout << "table is empty" << std::endl;
	}
	for (int i = 0; i < m_size; ++i)
	{
		if (m_hashCell[i].m_isExists)
		{
			std::cout << i << ": ";
			std::cout << m_hashCell[i].m_value;
			std::cout << std::endl;
		}
	}
}

int HashTable::getSize()
{
	return m_size;
}

int HashTable::hash(int key, int size)
{
	return (key % size + (1 + key % abs(size - 2))) % size;
}

int HashTable::hash1(int key)
{
	return key % 10;
}

void HashTable::resize(int newSize)
{
	int oldSize = m_size;
	HashCell* oldCells = m_hashCell;

	m_hashCell = new HashCell[newSize];
	m_size = newSize;
	
	for (int i = 0; i < newSize; ++i)
	{
		m_hashCell[i].m_isExists = false;
		m_hashCell[i].indexOfNext = -1;
	}

	for (int i = 0; i < oldSize; ++i)
	{
		HashCell cell = oldCells[i];
		if (cell.m_isExists)
		{
			addKey(cell.m_key, cell.m_value);
		}
	}

	delete[]oldCells;
}
