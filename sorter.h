#pragma once
#include <vector>

template<class String>
class Sorter {
public:
    virtual ~Sorter() = default;
    virtual void sort(std::vector<String>& v, int l, int r) const = 0;
};