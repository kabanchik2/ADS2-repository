#include <iostream>
#include <fstream>
#include <string>

#include "Files_Operations.h"

void spliting(std::fstream* A, std::fstream* F, const int p)
{
    int x1, x2;
    int n = 0;
    *A >> x1;

    while (!A->eof())
    {
        F[n] << x1;

        *A >> x2;
        if (x1 > x2) 
            n = 1 - n;

        x1 = x2;
    }
}







int main()
{
    std::cout << "Hello World!\n";
}