#pragma once

#include "sorter.h"
#include <algorithm>

template <class String>
class StringMergeSorter : public Sorter<String> {
private:
    
    std::pair<int, int> lcp_compare(const String& a, const String& b, int start) const {
        int i = start;
        int min_len = std::min(a.size(), b.size());
        while (i < min_len && a[i] == b[i]) i++;
        if (i == min_len) {
            if (a.size() == b.size()) return {0, i};
            if (a.size() < b.size()) return {-1, i};
            return {1, i};
        }
        if (a[i] < b[i]) return {-1, i};
        return {1, i};
    }
    
    void merge_with_lcp(std::vector<String>& v, std::vector<int>& lcp, int l, int m, int r, int shift) const {
        std::vector<String> temp_v;
        std::vector<int> temp_lcp;
        temp_v.reserve(r - l);
        temp_lcp.reserve(r - l);
        
        int i = l, j = m;
        while(i < m && j < r) {
            if (lcp[i - shift] > lcp[j - shift]) {
                temp_v.push_back(std::move(v[i]));
                temp_lcp.push_back(lcp[i - shift]);
                i++;
            } else if (lcp[i - shift] < lcp[j - shift]) {
                temp_v.push_back(std::move(v[j]));
                temp_lcp.push_back(lcp[j - shift]);
                j++;
            } else {
                auto [cmp, h] = lcp_compare(v[i], v[j], lcp[i - shift]);
                if (cmp < 0) {
                    temp_v.push_back(std::move(v[i]));
                    temp_lcp.push_back(lcp[i - shift]);
                    i++;
                    lcp[j - shift] = h;
                } else {
                    temp_v.push_back(std::move(v[j]));
                    temp_lcp.push_back(lcp[j - shift]);
                    j++;
                    lcp[i - shift] = h;
                }
            }
        }
        
        for (; i < m; i++) {
            temp_v.push_back(std::move(v[i]));
            temp_lcp.push_back(lcp[i - shift]);
        }
        
        for (; j < r; j++) {
            temp_v.push_back(std::move(v[j]));
            temp_lcp.push_back(lcp[j - shift]);
        }
        
        for (int idx = 0; idx < temp_v.size(); idx++) {
            v[l + idx] = std::move(temp_v[idx]);
            lcp[l - shift + idx] = temp_lcp[idx];
        }
        
        lcp[l - shift] = 0;
    }
    
    void inner_sort(std::vector<String>& v, std::vector<int>& lcp, int l, int r, int shift = 0) const {
        if (r - l <= 1) return;
        
        int m = l + (r - l) / 2;
        inner_sort(v, lcp, l, m, shift);
        inner_sort(v, lcp, m, r, shift);

        merge_with_lcp(v, lcp, l, m, r, shift);
    }
    
public:
    void sort(std::vector<String>& v, int l = 0, int r = -1) const override {
        if(r == -1) r = v.size();
        std::vector<int> lcp(r - l);
        inner_sort(v, lcp, l, r, l);
    }
};


template <class String>
class MergeSorter : public Sorter<String> {
private:
    void merge(std::vector<String>& v, int l, int m, int r) const {
        std::vector<String> temp(r - l);
        int i = l, j = m, k = 0;
        while (i < m && j < r) {
            if (v[i] <= v[j]) {
                temp[k++] = v[i++];
            } else {
                temp[k++] = v[j++];
            }
        }
        while (i < m) {
            temp[k++] = v[i++];
        }
        while (j < r) {
            temp[k++] = v[j++];
        }
        for (int idx = 0; idx < k; idx++) {
            v[l + idx] = temp[idx];
        }
    }

    void inner_sort(std::vector<String>& v, int l, int r) const {
        if (r - l <= 1) return;
        
        int m = l + (r - l) / 2;
        inner_sort(v, l, m);
        inner_sort(v, m, r);

        merge(v, l, m, r);
    }
    
public:
    void sort(std::vector<String>& v, int l = 0, int r = -1) const override {
        if(r == -1) r = v.size();
        inner_sort(v, l, r);
    }
};