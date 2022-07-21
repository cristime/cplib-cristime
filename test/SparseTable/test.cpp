#include "../../lib/SparseTable/SparseTable_rmq.h"
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    int n, m;
    std::vector<int> vec;

    fin >> n >> m;
    vec.resize(n + 1);
    for (int i = 1; i <= n; i++)
        fin >> vec[i];

    SparseTable<int> st(vec);
    st.Init();

    for (int i = 1; i <= m; i++) {
        int op, l, r;
        fin >> op >> l >> r;
        if (op == 1)
            fout << st.QueryMax(l, r) << std::endl;
        else
            fout << st.QueryMin(l, r) << std::endl;
    }

    fin.close();
    fout.close();

    return 0;
}