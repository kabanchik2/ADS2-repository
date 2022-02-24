#include <iostream>
#include <fstream>
#include <string>

#include "Files_Operations.h"

void spliting(std::fstream* A, std::ofstream* F)
{
    if (!A->is_open() || !F[0].is_open() || !F[1].is_open())
    {
        std::cerr << "can't open file in 'merging' " << std::endl;
        return;
    }

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
    if (!S[0].is_open() || !S[1].is_open() || !F[0].is_open() || !F[1].is_open())
    {
        std::cerr << "can't open file in 'merging' " << std::endl;
        return;
    }

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

    while (true)
    {  

        S[1].open("f1.txt");
        if (S[1].peek() == EOF)
        {
            S[1].close();
            break;
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
        if (S[1].peek() == EOF)
        {
            S[1].close();
            break;
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

    }  

    A->open(fileName, std::fstream::out);
    std::ifstream file("f0.txt");
    int x;
    while (!file.eof())
    {
        file >> x;
        *A << x << ' ';
    }

    file.close();
    A->close();
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithNumbers(fileName, numbersCount, maxNumberValue))
    {
        return -1;
    }

    sort(fileName);

    if (!isFileContainsSortedArray(fileName))
    {
        return -2;
    }
    
    return 1;
}

void testSort()
{
    std::string fileName = "A.txt";
    const int numbersCount = 30;
    const int maxNumberValue = 1000;

    for (int i = 0; i < 10; i++)
    {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }
    }
}

int main()
{
    testSort();

   /* std::string fileName = "A.txt";
    const int numbersCount = 30;
    const int maxNumberValue = 50;

    createFileWithNumbers(fileName, numbersCount, maxNumberValue);
    sort(fileName);*/
}