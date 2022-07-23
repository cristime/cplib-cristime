#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int a[MAXN], t[MAXN];
int n, m;
inline int lowbit(const int x) { return x & (-x); }
void add(int k, int v)
{
    for (; k <= n; k += lowbit(k))
        t[k] += v;
}
int sum(int k)
{
    int s = 0;
    for (; k > 0; k -= lowbit(k))
        s += t[k];
    return s;
}
int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    ;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> m;
    for (int i = 1; i <= n; i++)
        fin >> a[i];
    for (int i = 1; i <= n; i++)
        add(i, a[i]);
    for (int i = 0, op, x, y; i < m; i++) {
        fin >> op >> x >> y;
        if (op == 1)
            add(x, y);
        else
            fout << sum(y) - sum(x - 1) << endl;
    }

    fin.close();
    fout.close();
    return 0;
}