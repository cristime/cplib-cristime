#include "../Testlib/testlib.h"
#include <fstream>
#include <vector>

using namespace std;

const int MAXADD = 30, MAXN = 1e5 + 10; // Maximum add value and maximum array size
int n, m, stretch;
vector<int> w;
vector<pair<int, int>> edge;
vector<vector<int>> operations;

void GenTree()
{
    // Generate vertices weight with random numbers
    w.resize(n + 10);
    for (int i = 1; i <= n; i++)
        w[i] = rnd.next(-MAXADD, MAXADD);

    // Generate edges
    vector<int> fa(MAXN);
    for (int i = 1; i <= n; i++)
        fa[i] = rnd.wnext(i, stretch);

    vector<int> perm(MAXN);
    for (int i = 1; i <= n; i++)
        perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    for (int i = 1; i < n; i++)
        if (rnd.next(2))
            edge.push_back(make_pair(perm[i], perm[fa[i]]));
        else
            edge.push_back(make_pair(perm[fa[i]], perm[i]));
    shuffle(edge.begin(), edge.end());
}

void GenOperations()
{
    vector<int> tmp; // Store the operation
    for (int i = 1; i <= m; i++) {
        tmp.clear();
        int op = rnd.next(1, 4);
        tmp.push_back(op);

        int u, v, addnum;

        switch (op) {
        case 1: // Update chain
            u = rnd.next(1, n), v = rnd.next(1, n),
            addnum = rnd.next(-MAXADD, MAXADD);
            tmp.push_back(u);
            tmp.push_back(v);
            tmp.push_back(addnum);
            break;
        case 2: // Query chain
            u = rnd.next(1, n), v = rnd.next(1, n);
            tmp.push_back(u);
            tmp.push_back(v);
        case 3: // Update subtree
            u = rnd.next(1, n), addnum = rnd.next(-MAXADD, MAXADD);
            tmp.push_back(u);
            tmp.push_back(addnum);
            break;
        case 4: // Query subtree
            u = rnd.next(1, n);
            tmp.push_back(u);
            break;
        default:
            break;
        }

        operations.push_back(tmp);
    }
}

void WriteToFile(char* filename)
{
    // Write to file
    std::ofstream outfile;
    outfile.open(filename);
    outfile << n << " " << m << std::endl;
    for (int i = 1; i <= n; i++)
        outfile << w[i] << " ";
    outfile << std::endl;
    for (auto& el : edge)
        outfile << el.first << " " << el.second << std::endl;
    for (auto& el : operations) {
        for (auto& el2 : el)
            outfile << el2 << " ";
        outfile << std::endl;
    }
    outfile.close();
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    stretch = atoi(argv[3]);

    GenTree();
    GenOperations();
    WriteToFile(argv[4]);

    return 0;
}