#pragma once
#include <string>
#include <random>
#include <algorithm>

class StringGenerator {
private:
    static std::mt19937& get_rng() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }
    
    static std::string generate_string() {
        static const std::string symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
        static std::uniform_int_distribution<int> len_dist{10, 200};
        int len = len_dist(get_rng());
        std::string result;
        for (int i = 0; i < len; i++) {
            result += symbols[get_rng()() % symbols.size()];
        }
        return result;
    }
    
public:
    static std::vector<std::string> generate(int size) {
        std::vector<std::string> result(size);
        for (int i = 0; i < size; i++) {
            result[i] = generate_string();
        }
        return result;
    }
    
    static std::vector<std::string> generate_reverse_sorted_array(int size) {
        auto arr = generate(size);
        std::sort(arr.rbegin(), arr.rend());
        return arr;
    }
    
    static std::vector<std::string> generate_almost_sorted_array(int size) {
        auto arr = generate(size);
        std::sort(arr.begin(), arr.end());
        
        int swaps = std::max(1, size / 50);
        
        for (int i = 0; i < swaps; i++) {
            std::swap(arr[get_rng()() % size], arr[get_rng()() % size]);
        }
        
        return arr;
    }
};
