#include <iostream>
#include <fstream>
#include <string>

#include "Files_Operations.h"

void spliting(std::fstream* A, std::ofstream* F)
{
    int x1, x2;
    int n = 0;
    *A >> x1;

    while (!A->eof())
    {
        F[n] << x1 << ' ';

        *A >> x2;
        if (x1 > x2) 
            n = 1 - n;

        x1 = x2;
    }
}

void merging(std::ifstream* S, std::ofstream* F)
{
    int x[2], y[2];
    int n = 0, m = 0;

    S[0] >> x[0];
    S[1] >> x[1];


    while (!S[0].eof() && !S[1].eof())
    {
        if (x[m] > x[1 - m])
            m = 1 - m;

        F[n] << x[m] << ' ';

        S[m] >> y[m];
        if (S[m].eof() || x[m] > y[m])
        {
            m = 1 - m;
            F[n] << x[m] << ' ';

            S[m] >> y[m];
            while (!S[m].eof() && x[m] <= y[m])
            {
                x[m] = y[m];
                F[n] << x[m] << ' ';
                S[m] >> y[m];
            }

            x[1 - m] = y[1 - m];
            n = 1 - n;
        }

        x[m] = y[m];
    }

    while (!S[0].eof())
    {
        F[n] << x[0] << ' ';

        S[0] >> y[0];
        if (x[0] > y[0])
        {
            n = 1 - n;
        }
        
        x[0] = y[0];
    }

    while (!S[1].eof())
    {
        F[n] << x[1] << ' ';

        S[1] >> y[1];
        if (x[1] > y[1])
        {
            n = 1 - n;
        }

        x[1] = y[1];
    }
}

void sort(const std::string fileName)
{
    std::fstream* A = new std::fstream;
    std::ifstream* S = new std::ifstream[2];
    std::ofstream* F = new std::ofstream[2];

    A->open(fileName, std::fstream::in);
    F[0].open("f0.txt");
    F[1].open("f1.txt");

    spliting(A, F);

    F[0].close();
    F[1].close();
    A->close();

    int i = 0;
    while (true)
    {  
        std::cout << i << std::endl;
        S[1].open("f1.txt");
        if (S[1].eof())
        {
            S[1].close();
            return;
        }
        S[1].close();
        

        S[0].open("f0.txt");
        S[1].open("f1.txt");
        F[0].open("s0.txt");
        F[1].open("s1.txt");
        merging(S, F);

        F[0].close();
        F[1].close();
        S[0].close();
        S[1].close();

        S[1].open("f1.txt");
        if (S[1].eof())
        {
            S[1].close();
            return;
        }
        S[1].close();

        S[0].open("s0.txt");
        S[1].open("s1.txt");
        F[0].open("f0.txt");
        F[1].open("f1.txt");
        merging(S, F);

        F[0].close();
        F[1].close();
        S[0].close();
        S[1].close();

        ++i;
    }  

    F[0].close();
    F[1].close();
    S[0].close();
    S[1].close();
}


int main()
{
    const std::string fileName("A.txt");
    const int numbersCount = 20;
    const int maxNumberValue = 30;
    createFileWithNumbers(fileName, numbersCount, maxNumberValue);

    sort(fileName);

    std::cout << "end " << std::endl;
}