// Segment Tree for sums
// 2022/6/5 created by Cristime
// Licence: MIT
#pragma once

#ifndef SEGTREE_SUM
#define SEGTREE_SUM

// Type definitions
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

namespace SegTree
{
// Definitions and conventions
#define ls (k << 1)       // Left child
#define rs ((k << 1) + 1) // Right child
#define mid (l + r >> 1)  // Middle of the interval

    typedef ll T;              // Data type stored in SegTree
    const int maxn = 1e5 + 10; // Maximum array size

    static T sum[maxn << 2]; // SegTree sum
    static T tag[maxn << 2]; // Lazy tag

    inline void pushup(const int k) // Push up and update sums
    {
        sum[k] = sum[ls] + sum[rs];
    }

    inline void pushdown(const int k, const int l, const int r) // Pushdown tags
    {
        if (!tag[k])
            return; // If tag is empty, doing the following staff is useless.

        // Add sum values
        sum[ls] += tag[k] * (mid - l + 1);
        sum[rs] += tag[k] * (r - mid);

        // Update tags
        tag[ls] += tag[k];
        tag[rs] += tag[k];
        tag[k] = T(0);
    }

    void build(T *origin, const int k, const int l, const int r) // Build tree from an array
    {
        // If it's a leaf node
        if (l == r)
        {
            sum[k] = origin[l];
            return;
        }

        // Build trees for every sons.
        build(origin, ls, l, mid);
        build(origin, rs, mid + 1, r);

        // Maintain SegTree
        pushup(k);
    }

    // Update an certain interval in the array.
    void update(const int s, const int t, const T v, const int k, const int l, const int r)
    {
        // Included in this interval
        if (s <= l && r <= t)
        {
            sum[k] += v * (r - l + 1);
            tag[k] += v;
            return;
        }

        // Pushdown tags
        pushdown(k, l, r);

        // Update SegTree for every sons.
        if (s <= mid)
            update(s, t, v, ls, l, mid);
        if (t > mid)
            update(s, t, v, rs, mid + 1, r);

        // Maintain SegTree
        pushup(k);
    }

    // Query sums in the table.
    T query(const int s, const int t, const int k, const int l, const int r)
    {
        // Included in this interval
        if (s <= l && r <= t)
            return sum[k];

        // Pushdown
        pushdown(k, l, r);

        // Define a new variable to store return values.
        T ans = 0;
        if (s <= mid)
            ans += query(s, t, ls, l, mid);
        if (t > mid)
            ans += query(s, t, rs, mid + 1, r);

        // Return value
        return ans;
    }

} // namespace SegTree

#endif