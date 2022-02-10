#include <iostream>
#include <fstream>

#include <string>
#include <random>

bool fstreamFileWriteReadTest()
{
    std::ofstream writer("test.txt");
    std::ifstream reader;

    if (!writer.is_open())
    {
        std::cerr << "can't open 'test.txt'!" << std::endl;
        return false;
    }

    writer << "test";
    writer.close();

    reader.open("test2.txt");
    if (!reader.is_open())
    {
        std::cerr << "can't open 'test2.txt'!" << std::endl;
        reader.open("test.txt");

        if (!reader.is_open())
        {
            std::cerr << "can't open 'test.txt'!" << std::endl;
            return false;
        }
    }

    std::string fileContent;
    reader >> fileContent;
    std::cout << "test.txt content: " << std::endl;
    std::cout << fileContent << std::endl;
    reader.close();


    return true;
}

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

void createFileWithNumbersTest()
{
    std::string fileName("test.txt");
    const int numbersCount = 15;
    const int maxNumberValue = 25;
    bool test = createFileWithNumbers(fileName, numbersCount, maxNumberValue);
    std::cout << test << std::endl;
}

bool isFileContainsSortedArray(std::string fileName);



int main()
{
    //fstreamFileWriteReadTest();
    createFileWithNumbersTest();

}