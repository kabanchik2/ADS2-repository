// Huffman_Code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "HuffmanCode.h"
#include <Windows.h>

int HuffmanCodeTest()
{
	std::string str = "aaaaaaaa cccccccccccc bbbbb";
	std::string codedText;
	std::string decodedText;

	HuffmanCode test;
	std::cout << "Коэффициент сжатия: " << test.encode(str, codedText) << std::endl <<
		str.size() * 8 << " -> ";
	std::cout << codedText.size() << std::endl;


	std::cout << codedText << std::endl;
	
	test.decode(codedText, decodedText);
	std::cout << decodedText << std::endl;

	return 1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	return HuffmanCodeTest();
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
