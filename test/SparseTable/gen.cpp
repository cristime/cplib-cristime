#include "../Testlib/testlib.h"
#include <fstream>
#include <vector>

const int MAXVALUE = 100; // Maximum init value

int arraySize, operNum;
std::vector<int> origin; // Array to be tested
std::vector<std::vector<int>> ops; // Operations to be tested

void GenerateArray()
{
    // Generate an array with random numbers
    for (int i = 0; i < arraySize; i++)
        origin.push_back(rnd.next(-MAXVALUE, MAXVALUE));
}

void GenerateOps()
{
    for (int i = 0; i < operNum; i++) {
        int op = rnd.next(1, 2);
        int left = rnd.next(1, arraySize);
        int right = rnd.next(left, arraySize);
        ops.push_back({ op, left, right });
    }
}

void WriteToFile(char* fileName)
{
    // Write to file
    std::ofstream outfile(fileName);
    outfile << arraySize << " " << operNum << std::endl;
    for (auto& el : origin)
        outfile << el << " ";
    for (auto& el : ops) {
        for (auto& el2 : el)
            outfile << el2 << " ";
        outfile << std::endl;
    }
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    arraySize = atoi(argv[1]);
    operNum = atoi(argv[2]);

    GenerateArray();
    GenerateOps();
    WriteToFile(argv[3]);

    return 0;
}