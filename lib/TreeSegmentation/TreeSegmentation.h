// Tree Segmentation for sums
// 2022/6/5 created by Cristime
// Licence: MIT

#ifndef TREESEGMENTATION
#define TREESEGMENTATION

#include <vector>  // Store edges

// Basic data structure: Segment Tree
namespace SegTree {
// Definitions and conventions
#define ls (k << 1)             // Left child
#define rs (k << 1 | 1)         // Right child
#define mid (l + (r - l) >> 1)  // Middle of the interval

typedef int T;              // Data type stored in SegTree
const int maxn = 1e5 + 10;  // Maximum array size

static T sum[maxn << 2];  // SegTree sum
static T tag[maxn << 2];  // Lazy tag

inline void pushup(const int k)  // Push up and update sums
{
  sum[k] = sum[ls] + sum[rs];
}

inline void pushdown(const int k, const int l, const int r)  // Pushdown tags
{
  if (!tag[k])
    return;  // If tag is empty, doing the following staff is useless.

  // Add sum values
  sum[ls] += tag[k] * (mid - l + 1);
  sum[rs] += tag[k] * (r - mid);

  // Update tags
  tag[ls] += tag[k];
  tag[rs] += tag[k];
  tag[k] = T(0);
}

void build(T *origin, int *rnk, const int k, const int l,
           const int r)  // Build tree from an array
{
  // If it's a leaf node
  if (l == r) {
    sum[k] = origin[rnk[l]];
    return;
  }

  // Build trees for every sons.
  build(origin, rnk, ls, l, mid);
  build(origin, rnk, rs, mid + 1, r);

  // Maintain SegTree
  pushup(k);
}

// Update an certain interval in the array.
void update(const int s, const int t, const T v, const int k, const int l,
            const int r) {
  // Included in this interval
  if (s <= l && r <= t) {
    sum[k] += v * (r - l + 1);
    tag[k] += v;
    return;
  }

  // Pushdown tags
  pushdown(k, l, r);

  // Update SegTree for every sons.
  if (s <= mid) update(s, t, v, ls, l, mid);
  if (t > mid) update(s, t, v, rs, mid + 1, r);

  // Maintain SegTree
  pushup(k);
}

// Query sums in the table.
T query(const int s, const int t, const int k, const int l, const int r) {
  // Included in this interval
  if (s <= l && r <= t) return sum[k];

  // Define a new variable to store return values.
  T ans = 0;
  if (s <= mid) ans += query(s, t, ls, l, mid);
  if (t > mid) ans += query(s, t, rs, mid + 1, r);

  // Return value
  return ans;
}

}  // namespace SegTree

namespace TreeSegmentation {
typedef int T;  // Using int as data type

std::vector<int> edge[SegTree::maxn];  // Store edges
T w[SegTree::maxn];                    // Store weights

int n, m;                // Number of vertices and edges
int cnt;                 // Count the depth-first-search order
int rnk[SegTree::maxn];  // Rank of vertices
int dfn[SegTree::maxn];  // Depth-first-search order
int son[SegTree::maxn];  // Son with the biggest weight
int fa[SegTree::maxn];   // Father of the vertex
int dep[SegTree::maxn];  // Depth of the vertex
int sz[SegTree::maxn];   // Size of the vertex
int top[SegTree::maxn];  // Top of the vertex

// First depth-first-search
void dfs1(int u, int pre) {
  sz[u] = 1;  // Init size of the vertex
  for (auto &v : edge[u]) {
    if (v == pre) continue;              // Skip the father
    fa[v] = u;                           // Init father of the vertex
    dep[v] = dep[u] + 1;                 // Init depth of the vertex
    dfs1(v, u);                          // DFS
    sz[u] += sz[v];                      // Update size of the vertex
    if (sz[v] > sz[son[u]]) son[u] = v;  // Update son with the biggest weight
  }
}

// Second depth-first-search
void dfs2(int u, int t) {
  top[u] = t;                   // Init top of the vertex
  dfn[u] = ++cnt;               // Init depth-first-search order
  rnk[cnt] = u;                 // Init rank of the vertex
  if (son[u]) dfs2(son[u], t);  // DFS
  for (auto &v : edge[u])
    if (v != fa[u] && v != son[u]) dfs2(v, t);  // DFS
}

// Update chain in the tree
void UpdateChain(int u, int v, const T &delta) {
  while (top[u] != top[v])  // Update chain in the tree
  {
    if (dep[top[u]] > dep[top[v]]) std::swap(u, v);  // Select the deeper vertex
    SegTree::update(dfn[top[u]], dfn[u], delta, 1, 1, n);  // Update the chain
    u = fa[top[u]];                                        // Update the vertex
  }
  if (dep[u] > dep[v]) std::swap(u, v);  // Select the shallower vertex
  SegTree::update(dfn[u], dfn[v], delta, 1, 1, n);  // Update the last chain
}

// Query the sum of the chain
T QueryChain(int u, int v) {
  T ans = 0;
  while (top[u] != top[v])  // Query the sum of the chain
  {
    if (dep[top[u]] > dep[top[v]]) std::swap(u, v);  // Select the deeper vertex
    ans += SegTree::query(dfn[top[u]], dfn[u], 1, 1, n);  // Query the chain
    v = fa[top[v]];                                       // Update the vertex
  }
  if (dep[u] > dep[v]) std::swap(u, v);  // Select the shallower vertex
  return ans + SegTree::query(dfn[u], dfn[v], 1, 1, n);  // Query the last chain
}

// Update the subtree
void UpdateSubTree(int u, const T &delta) {
  SegTree::update(dfn[u], dfn[u] + sz[u] - 1, delta, 1, 1,
                  n);  // Update the subtree
}

// Query the sum of the subtree
T QuerySubTree(int u) {
  return SegTree::query(dfn[u], dfn[u] + sz[u] - 1, 1, 1,
                        n);  // Query the subtree
}

}  // namespace TreeSegmentation

#endif