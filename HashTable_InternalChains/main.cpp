// HashTable_InternalChains.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "HashTable.h"

int main()
{
    HashTable table(10);

    table.addKey(10, 1000);
    table.addKey(11, 100);
    table.addKey(12, 200);
    table.addKey(13, 300);
    table.addKey(14, 400);
    table.addKey(15, 500);
    table.addKey(16, 600);
    table.addKey(17, 700);
    table.addKey(18, 800);
    table.addKey(19, 900);
    table.addKey(44, 333);
    table.addKey(55, 12225);

    table.printTable();
    std::cout << table.getSize() << std::endl;

    //std::cout << ((1 % 10 + (1 + 1 % abs(10 - 2))) % 10);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
