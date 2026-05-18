#pragma once

#include "sorter.h"
#include "quick_sort.h"

template <class String, int THRESHOLD = 0, int BASE = 128>
class MsdRadixSorter : public Sorter<String> {
private:
    StringQuickSorter<String> quickSorter;
    
private:
    inline int char_at(const String& s, int d) const {
        if (d < s.size()) return (unsigned char)s[d] + 1;
        return 0;
    }
    
    void msd_sort(std::vector<String>& v, int l, int r, int d) const {
        if (r - l <= 1) return;
        
        if constexpr (THRESHOLD > 0) {
            if (r - l <= THRESHOLD) {
                quickSorter.sort(v, l, r);
                return;
            }
        }
    
        std::vector<int> count(BASE + 2, 0);
        
        for (int i = l; i < r; i++) {
            int c = char_at(v[i], d);
            count[c + 1]++;
        }
        
        for (int i = 0; i < BASE + 1; i++) {
            count[i + 1] += count[i];
        }
        
        std::vector<String> temp(r - l);
        
        for (int i = l; i < r; i++) {
            int c = char_at(v[i], d);
            temp[count[c]++] = std::move(v[i]);
        }
        
        for (int i = l; i < r; i++) {
            v[i] = std::move(temp[i - l]);
        }
        
        for (int i = 0; i < BASE; i++) {
            msd_sort(v, l + count[i], l + count[i + 1], d + 1);
        }
    }
    
public:
    void sort(std::vector<String>& v, int l = 0, int r = -1) const override {
        if(r == -1) r = v.size();
        msd_sort(v, l, r, 0);
    }
};