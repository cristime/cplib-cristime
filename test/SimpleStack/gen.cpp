// Operators:
// 1. Get Size
// 2. Get Top
// 3. Pop
// 4. Push
#include "../Testlib/testlib.h"
#include <fstream>
#include <vector>

const int MAXOP = 4, MAXVAL = 10000;

std::vector<std::vector<int>> ops;
static int opnum;

void genOps()
{
    for (int i = 1, op = 0; i <= opnum; ++i) {
        op = rnd.next(1, MAXOP);
        if (op <= 3) {
            ops.push_back({ op });
            continue;
        }
        ops.push_back({ op, rnd.next(-MAXVAL, MAXVAL) });
    }
}

void WriteToFile(char* filename)
{
    std::ofstream outfile(filename);
    outfile << opnum << std::endl;
    for (auto& eachVec : ops) {
        for (auto& eachEle : eachVec)
            outfile << eachEle << " ";
        outfile << std::endl;
    }
    outfile.close();
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    opnum = opt<int>(1);

    genOps();
    WriteToFile(argv[2]);

    return 0;
}