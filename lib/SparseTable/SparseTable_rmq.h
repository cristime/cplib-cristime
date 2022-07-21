// Sparse Table to solve RMQ problem
// 2022/7/21 created by Cristime
// Licence: MIT

// ATTENTION! THE ARRAY THAT CONSTRUCTOR NEED MUST BEGIN FROM ELEMENT 1

#include <cmath> // log2
#include <vector> // vector

#ifndef SPARSETABLE_RMQ

#define SPARSETABLE_RMQ

template <typename T>
class SparseTable {
private:
    static const int MAXLOG = 25; // Maximum logarithm of the array size
    static const int MAXN = 1e5 + 10; // Maximum array size

    int num; // Number of elements in the array
    std::vector<std::vector<T>> maxv, minv; // Sparse table

public:
    // ATTENTION! THE ARRAY MUST BEGIN FROM ELEMENT 1
    SparseTable(const int _n, const T* array)
    {
        num = _n;

        // Auto resize
        maxv.resize(_n + 5);
        for (auto& el : maxv)
            el.resize(MAXLOG + 5);
        minv.resize(_n + 5);
        for (auto& el : minv)
            el.resize(MAXLOG + 5);

        // Copy items
        for (int i = 1; i <= _n; ++i)
            maxv[i][0] = minv[i][0] = array[i];
    }

    // ATTENTION! THE ARRAY MUST BEGIN FROM ELEMENT 1
    SparseTable(const std::vector<T>& vec)
    {
        num = vec.size();

        // Auto resize
        maxv.resize(num + 5);
        for (auto& el : maxv)
            el.resize(MAXLOG + 5);
        minv.resize(num + 5);
        for (auto& el : minv)
            el.resize(MAXLOG + 5);

        // Copy items
        for (int i = 1; i <= num; ++i)
            maxv[i][0] = minv[i][0] = vec[i];
    }

    // Preconfigure for the sparse table
    void Init()
    {
        for (int j = 1; j <= MAXLOG; ++j)
            for (int i = 1; i + (1 << j) - 1 <= num; ++i) {
                maxv[i][j] = std::max(
                    maxv[i][j - 1],
                    maxv[i + (1 << (j - 1))][j - 1]);
                minv[i][j] = std::min(
                    minv[i][j - 1],
                    minv[i + (1 << (j - 1))][j - 1]);
            }
    }

    // Query maximum value in the interval [s, t]
    T QueryMax(const int s, const int t)
    {
        int j = std::log2(t - s + 1);
        return std::max(maxv[s][j], maxv[t - (1 << j) + 1][j]);
    }

    // Query minimum value in the interval [s, t]
    T QueryMin(const int s, const int t)
    {
        int j = std::log2(t - s + 1);
        return std::min(minv[s][j], minv[t - (1 << j) + 1][j]);
    }
};

#endif