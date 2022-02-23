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

void merging(std::fstream* S, std::fstream* F)
{
    int x[2], y[2];
    int n = 0, m = 0;

    S[0] >> x[0];
    S[1] >> x[1];

    while (!S[0].eof() && !S[1].eof())
    {
        if (x[m] > x[1 - m])
            m = 1 - m;

        F[n] << x[m];

        S[m] >> y[m];
        if (S[m].eof() || x[m] > y[m])
        {
            m = 1 - m;
            F[n] << x[m];

            S[m] >> y[m];
            while (!S[m].eof() && x[m] <= y[m])
            {
                x[m] = y[m];
                F[n] << x[m];
                S[m] >> y[m];
            }

            x[1 - m] = y[1 - m];
            n = 1 - n;
        }

        x[m] = y[m];
    }

    while (!S[0].eof())
    {
        F[n] << x[0];

        S[0] >> y[0];
        if (x[0] > y[0])
        {
            n = 1 - n;
        }
        
        x[0] = y[0];
    }

    while (!S[1].eof())
    {
        F[n] << x[1];

        S[1] >> y[1];
        if (x[1] > y[1])
        {
            n = 1 - n;
        }

        x[1] = y[1];
    }
}



int main()
{
    std::cout << "Hello World!\n";
}