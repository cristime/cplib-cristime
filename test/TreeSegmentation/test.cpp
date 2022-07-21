#include "../../lib/TreeSegmentation/TreeSegmentation.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    vector<TreeSegmentation::T> w(n + 1);
    vector<pair<int, int>> edge(n + 1);

    for (int i = 1; i <= n; ++i)
        fin >> w[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        fin >> u >> v;
        edge[i] = { u, v };
    }

    TreeSegmentation::Init(n, w, edge);

    TreeSegmentation::dfs1(1, 0);
    TreeSegmentation::dfs2(1, 1);
    SegTree::build(TreeSegmentation::w, TreeSegmentation::rnk, 1, 1, n);

    for (int i = 1; i <= m; ++i) {
        int op, u, v;
        TreeSegmentation::T delta;
        fin >> op;
        if (op == 1) {
            fin >> u >> v >> delta;
            TreeSegmentation::UpdateChain(u, v, delta);
        } else if (op == 2) {
            fin >> u >> v;
            fout << TreeSegmentation::QueryChain(u, v) << endl;
        } else if (op == 3) {
            fin >> u >> delta;
            TreeSegmentation::UpdateSubTree(u, delta);
        } else {
            fin >> u;
            fout << TreeSegmentation::QuerySubTree(u) << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}