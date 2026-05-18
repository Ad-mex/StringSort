#pragma once

#include "sorter.h"
#include <random>

template <class String>
class StringQuickSorter : public Sorter<String> {
private:
    mutable std::mt19937 rnd;
private:
    void inner_sort(std::vector<String>& v, int l, int r, int d = 0) const {
        if(r - l <= 1) return;
        
        int i = l, j = l, k = r - 1;
        
        int ind = rnd() % (r - l) + l;
        auto ch = (d < v[ind].size()) ? v[ind][d] : static_cast<String::value_type>(0);
        
        while (j <= k) {
            auto cur = (d < v[j].size()) ? v[j][d] : static_cast<String::value_type>(0);
            
            if (cur < ch) {
                v[i++].swap(v[j++]);
            } else if (cur > ch) {
                v[j].swap(v[k--]);
            } else {
                j++;
            }
        }
        
        inner_sort(v, l, i, d);
        
        if (ch) {
            inner_sort(v, i, k + 1, d + 1);
        }
        
        inner_sort(v, k + 1, r, d);
    }
public:
    void sort(std::vector<String>& v, int l = 0, int r = -1) const override{
        if(r == -1) r = v.size();
        inner_sort(v, l, r);
    }
};


template <class String>
class QuickSorter : public Sorter<String> {
private:
    mutable std::mt19937 rnd;
private:
    void inner_sort(std::vector<String>& v, int l, int r) const {
        if(r - l <= 1) return;
        int ind = rnd() % (r - l) + l;
        v[ind].swap(v[l]);
        int i = l + 1, j = r - 1;
        while (i <= j) {
            while (i <= j && v[i] <= v[l]) i++;
            while (i <= j && v[j] > v[l]) j--;
            if (i < j) v[i].swap(v[j]);
        }
        v[l].swap(v[j]);
        
        inner_sort(v, l, j);
        inner_sort(v, j + 1, r);
    }
public:
    void sort(std::vector<String>& v, int l = 0, int r = -1) const override{
        if(r == -1) r = v.size();
        inner_sort(v, l, r);
    }
};
