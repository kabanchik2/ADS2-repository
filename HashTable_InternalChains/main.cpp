// HashTable_InternalChains.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "HashTable.h"

int main()
{
    HashTable table(10);

    table.addKey(10, 100);
    table.addKey(11, 101);
    table.addKey(12, 102);
    table.addKey(13, 130);
    table.addKey(14, 140);
    table.addKey(15, 1514);
    table.addKey(16, 16346);
    table.addKey(17, 17123);
    table.addKey(18, 145);
    table.addKey(19, 19563);
    table.addKey(44, 4134344);
    table.addKey(55, 5345);

    table.printTable();
    std::cout << std::endl;
    
    /*int key;
    do
    {
        std::cout << "enter key: ";
        std::cin >> key;
        std::cout << table.findKey(key) << std::endl;
    } while (key != -1);*/

    int key;
    do
    {
        std::cout << "enter key: ";
        std::cin >> key;
        std::cout << std::endl;
        //std::cout << table.deleteKey(key) << std::endl;
        table.deleteKey(key);
        table.printTable();
    } while (key != -1);

    
   
    //std::cout << table.getSize() << std::endl;
    
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
