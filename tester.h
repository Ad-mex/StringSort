#pragma once
#include "generator.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include <chrono>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>


class StringSortTester {
private:

    struct CounterChar {
        char value;

        static inline unsigned long long counter = 0;
        
        constexpr CounterChar() = default;
        constexpr CounterChar(const char& c) noexcept : value(c) {}
        
        template <typename T>
        operator T() const { return value; }
        
        template<typename T>
        friend auto operator<=>(CounterChar a, T b) {
            counter++;
            return a.value <=> b;
        }
        
        template<typename T>
        friend bool operator==(CounterChar a, T b) {
            counter++;
            return a.value == b;
        }

        template<typename T>
        friend bool operator!=(CounterChar a, T b) {
            counter++;
            return a.value != b;
        }
    };

    using String = std::basic_string<char>;
    template <class T> using RadixQuickSorter = MsdRadixSorter<T, 74>;
    
    class CounterString : public std::basic_string<CounterChar> {
    public:

        CounterString() = default;

        CounterString(const std::string& s) 
        : std::basic_string<CounterChar>(s.begin(), s.end()) {}
        
        CounterString(const char* s) 
            : std::basic_string<CounterChar>(s, s + strlen(s)) {}
    };

public:
    template<template<typename> class SpecificSorter, typename GenFunc>
    static void test_on(GenFunc gen_func) {
        SpecificSorter<CounterString> CounterSorter;
        SpecificSorter<String> Sorter;

        std::vector<double> times;
        std::vector<double> counts;
        for(int sz = 100; sz <= 3000; sz += 100) {

            long long all_time_ns = 0;
            long long all_count = 0;

            for(int _ = 0; _ < 50; _++) {

                std::vector<String> time_v = gen_func(sz);
                std::vector<CounterString> counter_v = std::vector<CounterString>(time_v.begin(), time_v.end());

                auto begin = std::chrono::high_resolution_clock::now();
                Sorter.sort(time_v);
                auto end = std::chrono::high_resolution_clock::now();

                all_time_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

                CounterChar::counter = 0;
                CounterSorter.sort(counter_v);
                all_count += CounterChar::counter;
            }

            std::cout << "Size:\t" << sz << '\n' << "Time(mcs):\t" << all_time_ns / 1000. / 50 << ' ' << "Cnt:\t" << all_count / 50. << std::endl;
            times.push_back(all_time_ns / 1000. / 50);
            counts.push_back(all_count / 50.);
        }

        std::cout << std::endl;

        std::cout << "Times: \n";
        for(auto t: times) std::cout << t << ' ';
        std::cout << std::endl;

        std::cout << "Counts: \n";
        for(auto c: counts) std::cout << c << ' ';
        std::cout << std::endl;

        std::cout << "===============================" << std::endl;
    }

    template<template<typename> class SpecificSorter>
    static void test_specific() {
        std::cout << "Рандомные строки:\n";
        test_on<SpecificSorter>(StringGenerator::generate);
        std::cout << "Обратно упорядоченные строки:\n";
        test_on<SpecificSorter>(StringGenerator::generate_reverse_sorted_array);
        std::cout << "Почти упорядоченные строки:\n";
        test_on<SpecificSorter>(StringGenerator::generate_almost_sorted_array);
    }

    static void test_all() {
        std::cout << "Base QuickSort:\n" << std::endl;
        test_specific<QuickSorter>();

        std::cout << "Base MergeSort:\n" << std::endl;
        test_specific<MergeSorter>();

        std::cout << "String QuickSort:\n" << std::endl;
        test_specific<StringQuickSorter>();

        std::cout << "String MergeSort:\n" << std::endl;
        test_specific<StringMergeSorter>();

        std::cout << "RadixSort:\n" << std::endl;
        test_specific<MsdRadixSorter>();

        std::cout << "RadixSort with Threshold:\n" << std::endl;
        test_specific<RadixQuickSorter>();
    }
};
