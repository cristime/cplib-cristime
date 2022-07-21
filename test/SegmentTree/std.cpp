#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

ifstream fin;
ofstream fout;

namespace SegTree
{
    const int MAXN = 1e5 + 10;
    int tree[MAXN << 2], tag[MAXN << 2];

    inline int lson(const int k) { return k << 1; }
    inline int rson(const int k) { return (k << 1) + 1; }
    inline void pushup(const int k) { tree[k] = tree[lson(k)] + tree[rson(k)]; }
    inline void pushdown(const int k, const int l, const int r)
    {
        const int mid = l + (r - l >> 1);
        tree[lson(k)] += tag[k] * (mid - l + 1);
        tree[rson(k)] += tag[k] * (r - mid);
        tag[lson(k)] += tag[k];
        tag[rson(k)] += tag[k];
        tag[k] = 0;
    }

    void build(int k, int l, int r)
    {
        if (l == r)
        {
            fin >> tree[k];
            return;
        }
        int mid = l + (r - l >> 1);
        build(lson(k), l, mid);
        build(rson(k), mid + 1, r);
        pushup(k);
    }

    void update(int s, int t, int d, int k, int l, int r)
    {
        if (s <= l && r <= t)
        {
            tree[k] += d * (r - l + 1);
            tag[k] += d;
            return;
        }
        pushdown(k, l, r);
        int mid = l + (r - l >> 1);
        if (s <= mid)
            update(s, t, d, lson(k), l, mid);
        if (t > mid)
            update(s, t, d, rson(k), mid + 1, r);
        pushup(k);
    }

    int query(int s, int t, int k, int l, int r)
    {
        if (s <= l && r <= t)
            return tree[k];
        pushdown(k, l, r);
        int mid = l + (r - l >> 1), sum = 0;
        if (s <= mid)
            sum += query(s, t, lson(k), l, mid);
        if (t > mid)
            sum += query(s, t, rson(k), mid + 1, r);
        return sum;
    }
};

signed main(signed argc, char *argv[])
{
    ios::sync_with_stdio(false);
    string inputfile = argv[1];
    string outputfile = argv[2];

    fin.open(inputfile);
    fout.open(outputfile);

    int n, m;
    fin >> n >> m;
    SegTree::build(1, 1, n);
    while (m--)
    {
        int op, l, r, d;
        fin >> op >> l >> r;
        if (op == 1)
        {
            fin >> d;
            SegTree::update(l, r, d, 1, 1, n);
        }
        else
            fout << SegTree::query(l, r, 1, 1, n) << endl;
    }

    fin.close();
    fout.close();

    return 0;
}