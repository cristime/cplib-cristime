// Simple stack implemention
// 2022/12/23 created by Cristime
// Licence: MIT

#include <vector>

#ifndef SIMPLESTACK
#define SIMPLESTACK

template <class T>
class SimpleStack {
private:
    std::vector<T> stackData; // Data in the stack
    unsigned stackSize; // Stack Size

public:
    SimpleStack() { stackSize = 0; }
    SimpleStack(T initElement)
    {
        stackData.emplace_back(initElement);
        stackSize = 1;
    }
    SimpleStack(const std::vector<T>& array)
    {
        for (auto&& i : array)
            stackData.push_back(i);
        stackSize = array.size();
    }

    unsigned size() { return stackSize; }

    void push(T& newElement)
    {
        stackData.emplace_back(newElement);
        ++stackSize;
    }

    T top() { return stackData[stackSize]; }

    bool pop()
    {
        if (!stackSize)
            return false;
        --stackSize;
        return true;
    }
};

#endif