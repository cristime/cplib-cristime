#include "../../lib/BinaryIndexedTree/BinaryIndexedTree.h"
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    std::vector<int> arr;

    fin >> n >> m;
    arr.resize(n + 1);
    for (int i = 1; i <= n; i++)
        fin >> arr[i];

    BinaryIndexedTree<int> bit(arr);

    for (int i = 1, op, x, y; i <= m; i++) {
        fin >> op >> x >> y;
        if (op == 1)
            bit.AddNum(x, y);
        else
            fout << bit.QuerySum(x, y) << endl;
    }

    fin.close();
    fout.close();
    return 0;
}