#include <iostream>
#include <fstream>

#include <string>
#include <random>


bool createFileWithNumbers(std::string fileName, const int numbersCount, const int maxNumberValue)
{
    srand(time(NULL));
    std::ofstream writer(fileName);
    if (!writer.is_open())
    {
        std::cerr << "can't open " << fileName << std::endl;
        return false;
    }

    writer << numbersCount << std::endl;
    for (int i = 0; i < numbersCount; ++i)
    {
        writer << rand() % (maxNumberValue + 1) << ' ';
    }

    writer.close();

    return true;
}

bool isFileContainsSortedArray(std::string fileName)
{
    std::ifstream reader(fileName);

    if (!reader.is_open())
    {
        std::cerr << "can't open 'test.txt'!" << std::endl;
        return false;
    }
    
    int numbersCount;
    int previousNumber;
    int currentNumber;

    reader >> numbersCount;
    reader >> previousNumber;
    for (int i = 0; i < numbersCount; ++i)
    {
        reader >> currentNumber;
        if (currentNumber < previousNumber)
        {
            return false;
        }
    }

    reader.close();
    return true;
}

void createFileWithNumbersTest()
{
    std::string fileName("test.txt");
    const int numbersCount = 15;
    const int maxNumberValue = 25;
    bool test = createFileWithNumbers(fileName, numbersCount, maxNumberValue);
    std::cout << test << std::endl;
}


int main()
{
    //fstreamFileWriteReadTest();
    createFileWithNumbersTest();

}