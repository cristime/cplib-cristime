#include "../Testlib/testlib.h"
#include <fstream>
#include <string>
#include <vector>

const int MAXADD = 100; // Maximum add value

int n, m;
std::vector<int> arr; // Generated array
std::vector<std::vector<int>> ops; // Generated operations
std::string outfile; // Output file name

void GenerateArray()
{
    for (int i = 0; i < n; i++) {
        arr.push_back(rnd.next(-MAXADD, MAXADD));
    }
}

void GenerateOps()
{
    /*
    Operations:
    1. Add number k to arr[x]
    2. Query sum of arr[x] to arr[y]
    */

    for (int i = 0; i < m; i++) {
        int op = rnd.next(1, 2);
        if (op == 1) {
            int x = rnd.next(1, n),
                k = rnd.next(-MAXADD, MAXADD);
            ops.push_back({ op, x, k });
        } else {
            int x = rnd.next(1, n),
                y = rnd.next(x, n);
            ops.push_back({ op, x, y });
        }
    }
}

void WriteToFile()
{
    std::ofstream out(outfile);
    out << n << " " << m << std::endl;
    for (auto& el : arr)
        out << el << " ";
    out << std::endl;
    for (auto& el : ops) {
        for (auto& el2 : el)
            out << el2 << " ";
        out << std::endl;
    }
    out.close();
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1); // Register the generator

    n = opt<int>(1); // Length of the array
    m = opt<int>(2); // Number of operations
    outfile = opt<std::string>(3); // Output file name

    GenerateArray();
    GenerateOps();
    WriteToFile();

    return 0;
}