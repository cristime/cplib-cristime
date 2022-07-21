#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, MAXLOG = 25;
int n, m;
int maxv[MAXN][MAXLOG], minv[MAXN][MAXLOG];
int logn[MAXN];

inline int QueryMax(int l, int r)
{
    int k = log2(r - l + 1);
    return max(maxv[l][k], maxv[r - (1 << k) + 1][k]);
}

inline int QueryMin(int l, int r)
{
    int k = log2(r - l + 1);
    return min(minv[l][k], minv[r - (1 << k) + 1][k]);
}

int main(int argc, char* argv[])
{
    // Preconfig IOs
    ios::sync_with_stdio(false);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fin >> maxv[i][0];
        minv[i][0] = maxv[i][0];
    }
    for (int j = 1; j <= MAXLOG; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            maxv[i][j] = max(maxv[i][j - 1], maxv[i + (1 << (j - 1))][j - 1]);
            minv[i][j] = min(minv[i][j - 1], minv[i + (1 << (j - 1))][j - 1]);
        }
    for (int i = 1; i <= m; i++) {
        int op, l, r;
        fin >> op >> l >> r;
        if (op == 1)
            fout << QueryMax(l, r) << endl;
        else
            fout << QueryMin(l, r) << endl;
    }

    fin.close();
    fout.close();

    return 0;
}