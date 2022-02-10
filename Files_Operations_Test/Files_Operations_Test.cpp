#include <iostream>
#include <fstream>

#include <string>

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

bool createFileWithNumbers(std::string fileName, const int numbersCount, int maxNumberValue);

bool isFileContainsSortedArray(std::string fileName);



int main()
{
    fstreamFileWriteReadTest();
}