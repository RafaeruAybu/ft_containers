#ifndef FT_CONTAINERS2_TEST_VECTOR_HPP
#define FT_CONTAINERS2_TEST_VECTOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vector.hpp"
#include <chrono>
#include <ctime>

//define
# if !defined(USING_STD)
#  define ns ft
# else
#  define ns std
# endif

class test_vector
{
private:
    std::fstream m_out_file;
    std::fstream m_timing_file;

public:
    test_vector(std::string out_file, std::string timing_file);
    ~test_vector();
    void run_tests();

private:
    void constructors();
    void operators();
    void iterators();
    void sizes();
    void assigns();
    void inserts();
    void push_pop();
    void erases();
    void clear();
    void get_allocator();
    void swap();

    long long int time_start;
    long long int time_stop;
    long long int time_delta;

    void timer_start()
    {
        time_start = std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::system_clock::system_clock::now().time_since_epoch()).count();
    }

    void timer_stop()
    {
        time_stop = std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::system_clock::system_clock::now().time_since_epoch()).count();
        time_delta = time_stop - time_start;
    }

    void print_info(std::string info)
    {
        m_out_file << info << std::endl;
    }

    void print_time_info(std::string info)
    {
        m_timing_file << info << " " << time_delta << " microseconds." << std::endl;
    }
};

#endif //FT_CONTAINERS2_TEST_VECTOR_HPP
