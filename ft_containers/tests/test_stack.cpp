#include "test_stack.hpp"

test_stack::test_stack(std::string out_file, std::string timing_file)
{
    m_out_file.open(out_file, std::ios::out);
    m_timing_file.open(timing_file, std::ios::out);
}

test_stack::~test_stack()
{
    m_out_file.close();
    m_timing_file.close();
}

void test_stack::run_tests()
{
    constructors();
    top();
    empty();
    size();
    push();
    pop();
    operators();
}

void test_stack::constructors()
{
    print_info("Stack constructors.");
    print_info("Stack def constructors.");
    timer_start();
    ns::stack<int> st;
    timer_stop();
    print_time_info("Stack def constructor.");

    print_info("Stack cpy constructors.");
    timer_start();
    ns::stack<int> st2(st);
    timer_stop();
    print_time_info("Stack cpy constructor.");
}

void test_stack::top()
{
    print_info("Stack top.");
    ns::stack<int> st;
    st.push(5);
    timer_start();
    print_info("Stack top: " + std::to_string(st.top()));
    timer_stop();
    print_time_info("Stack top.");
}

void test_stack::empty()
{
    print_info("Stack empty.");
    ns::stack<int> st;
    timer_start();
    print_info("Stack top: " + std::to_string(st.empty()));
    timer_stop();
    print_time_info("Stack empty.");
}

void test_stack::size()
{
    print_info("Stack size.");
    ns::stack<int> st;
    st.push(5);
    st.push(333);
    timer_start();
    print_info("Stack size: " + std::to_string(st.size()));
    timer_stop();
    print_time_info("Stack size.");
}

void test_stack::push()
{
    print_info("Stack push.");
    ns::stack<int> st;
    print_info("Stack before push.");
    print_info("Stack size: " + std::to_string(st.size()));
    timer_start();
    st.push(5);
    timer_stop();
    print_info("Stack after push.");
    print_info("Stack size: " + std::to_string(st.size()));
    print_time_info("Stack push.");
}

void test_stack::pop()
{
    print_info("Stack pop.");
    ns::stack<int> st;
    st.push(5);
    print_info("Stack before pop.");
    print_info("Stack top: " + std::to_string(st.top()));

    timer_start();
    st.pop();
    timer_stop();
    print_time_info("Stack pop.");

    print_info("Stack after pop.");
    print_info("Stack top: " + std::to_string(st.top()));
}

void test_stack::operators()
{
    print_info("Stack operators.");
    ns::stack<int> st;
    st.push(5);
    st.push(333);

    ns::stack<int> st2;
    st2.push(4);
    st2.push(1);

    timer_start();
    print_info("Stack ==: " + std::to_string(st == st2));
    print_info("Stack !=: " + std::to_string(st != st2));
    print_info("Stack <: " + std::to_string(st < st2));
    print_info("Stack >: " + std::to_string(st > st2));
    print_info("Stack <=: " + std::to_string(st <= st2));
    print_info("Stack >=: " + std::to_string(st >= st2));
    timer_stop();
    print_time_info("Stack operators.");
}
