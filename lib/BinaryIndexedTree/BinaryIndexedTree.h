// Binary Indexed Tree for sums
// 2022/7/22 created by Cristime
// Licence: MIT

// ATTENTION! THE ARRAY THAT CONSTRUCTOR NEED MUST BEGIN FROM ELEMENT 1

#include <vector>

#ifndef BINARYINDEXEDTREE_H
#define BINARYINDEXEDTREE_H

template <typename T>
class BinaryIndexedTree {
private:
    std::vector<T> arr; // Array
    int num; // Number of elements in the array

    inline int lowbit(int x) { return x & (-x); } // Get the lowest bit with 1 of x

public:
    // ATTENTION! THE ARRAY THAT CONSTRUCTOR NEED MUST BEGIN FROM ELEMENT 1
    BinaryIndexedTree(std::vector<T>&);
    BinaryIndexedTree(const int, const T*);

    void AddNum(const int, const T);
    T QuerySum(const int, const int);
    T QuerySum(const int);
};

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree(std::vector<T>& vec)
{
    num = vec.size() - 1;
    arr.resize(num + 5);
    // O(n) Build tree
    for (int i = 1; i <= num; ++i) {
        arr[i] += vec[i];
        int j = i + lowbit(i);
        if (j <= num)
            arr[j] += arr[i];
    }
}

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree(const int _n, const T* array)
{
    num = _n;
    arr.resize(num + 5);
    // O(n) Build tree
    for (int i = 1; i <= num; ++i) {
        arr[i] += array[i];
        int j = i + lowbit(i);
        if (j <= _n)
            arr[j] += arr[i];
    }
}

// Single element update
template <typename T>
void BinaryIndexedTree<T>::AddNum(const int i, const T val)
{
    for (int _i = i; _i <= num; _i = _i + lowbit(_i))
        arr[_i] += val;
}

// Query sum of [1, i]
template <typename T>
T BinaryIndexedTree<T>::QuerySum(const int i)
{
    T sum = 0;
    for (int _i = i; _i > 0; _i = _i - lowbit(_i))
        sum += arr[_i];
    return sum;
}

// Query sum of [l, r]
template <typename T>
T BinaryIndexedTree<T>::QuerySum(const int l, const int r)
{
    return QuerySum(r) - QuerySum(l - 1);
}

#endif