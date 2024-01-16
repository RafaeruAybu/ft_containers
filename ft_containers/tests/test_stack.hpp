#ifndef TESTS_TEST_STACK_HPP
#define TESTS_TEST_STACK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "../stack.hpp"
#include <chrono>
#include <ctime>

//define
# if !defined(USING_STD)
#  define ns ft
# else
#  define ns std
# endif

class test_stack
{
private:
    std::fstream m_out_file;
    std::fstream m_timing_file;

public:
    test_stack(std::string out_file, std::string timing_file);
    ~test_stack();
    void run_tests();

private:
    //todo test foos here
    void constructors();
    void top();
    void empty();
    void size();
    void push();
    void pop();
    void operators();

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

#endif //TESTS_TEST_STACK_HPP
