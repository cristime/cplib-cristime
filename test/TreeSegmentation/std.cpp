#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int MAXN = 1e5 + 10;
int n, m, s, cnt;
int w[MAXN], dfn[MAXN], rnk[MAXN], fa[MAXN], sn[MAXN], sz[MAXN], dep[MAXN], top[MAXN];
vector<int> e[MAXN];

struct SegTree {
    int sum[MAXN << 2], tag[MAXN << 2];

    inline int lson(const int k) { return k << 1; }
    inline int rson(const int k) { return k << 1 | 1; }

    inline void pushup(const int k) { sum[k] = sum[lson(k)] + sum[rson(k)]; }
    inline void pushdown(const int k, const int l, const int r)
    {
        int mid = l + (r - l >> 1);
        sum[lson(k)] = (sum[lson(k)] + tag[k] * (mid - l + 1));
        sum[rson(k)] = (sum[rson(k)] + tag[k] * (r - mid));
        tag[lson(k)] = (tag[lson(k)] + tag[k]);
        tag[rson(k)] = (tag[rson(k)] + tag[k]);
        tag[k] = 0LL;
    }

    void build(int k, int l, int r)
    {
        if (l == r) {
            sum[k] = w[rnk[l]];
            return;
        }
        int mid = l + (r - l >> 1);
        build(lson(k), l, mid);
        build(rson(k), mid + 1, r);
        pushup(k);
    }

    void update(int s, int t, int delta, int k, int l, int r)
    {
        if (s <= l && r <= t) {
            sum[k] = (sum[k] + delta * (r - l + 1));
            tag[k] = (tag[k] + delta);
            return;
        }
        pushdown(k, l, r);
        int mid = l + (r - l >> 1);
        if (s <= mid)
            update(s, t, delta, lson(k), l, mid);
        if (t > mid)
            update(s, t, delta, rson(k), mid + 1, r);
        pushup(k);
    }

    int query(int s, int t, int k, int l, int r)
    {
        if (s <= l && r <= t)
            return sum[k];
        pushdown(k, l, r);
        int mid = l + (r - l >> 1), ans = 0LL;
        if (s <= mid)
            ans = (ans + query(s, t, lson(k), l, mid));
        if (t > mid)
            ans = (ans + query(s, t, rson(k), mid + 1, r));
        return ans;
    }
} st;

void dfs1(int u, int pre)
{
    sz[u] = 1;
    for (auto& v : e[u]) {
        if (v == pre)
            continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[sn[u]])
            sn[u] = v;
    }
}

void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (sn[u])
        dfs2(sn[u], t);
    for (auto& v : e[u])
        if (v != fa[u] && v != sn[u])
            dfs2(v, v);
}

void update1(int u, int v, int delta)
{
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) {
            st.update(dfn[top[u]], dfn[u], delta, 1LL, 1LL, n);
            u = fa[top[u]];
        } else {
            st.update(dfn[top[v]], dfn[v], delta, 1LL, 1LL, n);
            v = fa[top[v]];
        }
    }
    if (dep[u] < dep[v])
        st.update(dfn[u], dfn[v], delta, 1LL, 1LL, n);
    else
        st.update(dfn[v], dfn[u], delta, 1LL, 1LL, n);
}

int query1(int u, int v)
{
    int ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) {
            ret = (ret + st.query(dfn[top[u]], dfn[u], 1LL, 1LL, n));
            u = fa[top[u]];
        } else {
            ret = (ret + st.query(dfn[top[v]], dfn[v], 1LL, 1LL, n));
            v = fa[top[v]];
        }
    }
    return dep[u] < dep[v]
        ? (ret + st.query(dfn[u], dfn[v], 1LL, 1LL, n))
        : (ret + st.query(dfn[v], dfn[u], 1LL, 1LL, n));
}

void update2(int u, int delta)
{
    st.update(dfn[u], dfn[u] + sz[u] - 1, delta, 1LL, 1LL, n);
}

int query2(int u)
{
    return st.query(dfn[u], dfn[u] + sz[u] - 1, 1LL, 1LL, n);
}

signed main(signed argc, char* argv[])
{
    ios::sync_with_stdio(false);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> m;
    s = 1;
    for (int i = 1; i <= n; ++i)
        fin >> w[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        fin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    dfs1(s, 0);
    dfs2(s, s);
    st.build(1LL, 1LL, n);

    while (m--) {
        int op, u, v, delta;
        fin >> op;
        if (op == 1LL) {
            fin >> u >> v >> delta;
            update1(u, v, delta);
        } else if (op == 2LL) {
            fin >> u >> v;
            fout << query1(u, v) << endl;
        } else if (op == 3LL) {
            fin >> u >> delta;
            update2(u, delta);
        } else {
            fin >> u;
            fout << query2(u) << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}