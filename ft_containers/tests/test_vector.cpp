#include "test_vector.hpp"

test_vector::test_vector(std::string out_file, std::string timing_file)
{
    m_out_file.open(out_file, std::ios::out);
    m_timing_file.open(timing_file, std::ios::out);
}

test_vector::~test_vector()
{
    m_out_file.close();
    m_timing_file.close();
}

void test_vector::run_tests()
{
    constructors();
    operators();
    iterators();
    sizes();
    assigns();
    inserts();
    push_pop();
    erases();
    swap();
}

void test_vector::constructors()
{
    print_info("Vector constructors.");
    print_info("Vector def constructor.");
    timer_start();
    ns::vector<int> lel;
    timer_stop();
    print_time_info("Vector def constructor.");
    print_info("Vector size: " + std::to_string(lel.size()) + ".");

    print_info("Vector \"N\" constructor.");
    timer_start();
    ns::vector<int> first(200);
    timer_stop();
    print_time_info("Vector \"N\" constructor.");
    print_info("Vector size: " + std::to_string(first.size()) + ".");

    print_info("Vector \"iterator\" constructor.");
    first.insert(first.begin(), 150, 5);
    timer_start();
    ns::vector<int> second(first.begin(), first.end());
    timer_stop();
    print_time_info("Vector \"iterator\" constructor.");
    print_info("Vector size: " + std::to_string(second.size()) + ".");

    print_info("Vector \"other\" constructor.");
    timer_start();
    ns::vector<int> third(second);
    timer_stop();
    print_time_info("Vector \"other\" constructor.");
}

void test_vector::operators() {
    print_info("Vector =.");
    ns::vector<int> first(200);
    for (int i = 0; i < 200; i++)
    {
        first.push_back(i);
    }

    ns::vector<int> second;
    timer_start();
    second = first;
    timer_stop();
    print_time_info("Vector = result.");
    for (int i = 0; i < (int)second.size(); i++)
    {
        m_out_file << second[i] << std::endl;
    }

    print_info("Vector [].");
    timer_start();
    for (int i = 0; i < (int)first.size(); i++)
    {
        m_out_file << first[i] << std::endl;
    }
    timer_stop();
    print_time_info("Vector [].");

    print_info("Vector ==.");
    ns::vector<int> one;
    for (int i = 0; i < 200; i++)
    {
        one.push_back(i);
    }
    ns::vector<int> two;
    for (int i = 0; i < 199; i++)
    {
        two.push_back(i);
    }
    two.push_back(999);
    bool res;
    timer_start();
    res = one == two;
    timer_stop();
    print_info("Vector == res:" + std::to_string(res) + ".");
    print_time_info("Vector ==.");

    print_info("Vector <.");
    timer_start();
    res = one < two;
    timer_stop();
    print_info("Vector < res:" + std::to_string(res) + ".");
    print_time_info("Vector <.");
}

void test_vector::iterators()
{
    print_info("Vector iterators.");
    ns::vector<int> one;
    for (int i = 0; i < 200; i++)
    {
        one.push_back(i);
    }

    print_info("Vector begin.");
    timer_start();
    ns::vector<int>::iterator iter = one.begin();
    timer_stop();
    print_info("Vector begin." + std::to_string(*iter));
    print_time_info("Vector begin.");

    print_info("Vector end.");
    timer_start();
    iter = one.end();
    timer_stop();
    print_info("Vector end." + std::to_string(*iter));
    print_time_info("Vector end.");

    print_info("Vector rbegin.");
    timer_start();
    ns::vector<int>::reverse_iterator r_iter = one.rbegin();
    timer_stop();
    print_info("Vector rbegin." + std::to_string(*r_iter));
    print_time_info("Vector rbegin.");

    print_info("Vector rend.");
    timer_start();
    r_iter = one.rend();
    timer_stop();
    print_info("Vector rend." + std::to_string(*r_iter));
    print_time_info("Vector rend.");

    print_info("Vector at.");
    timer_start();
    ns::vector<int>::reference ref = one.at(2);
    timer_stop();
    print_info("Vector rend." + std::to_string(ref));
    print_time_info("Vector at.");

    print_info("Vector front.");
    timer_start();
    ref = one.front();
    timer_stop();
    print_info("Vector front." + std::to_string(ref));
    print_time_info("Vector front.");

    print_info("Vector back.");
    timer_start();
    ref = one.back();
    timer_stop();
    print_info("Vector back." + std::to_string(ref));
    print_time_info("Vector back.");

    print_info("Vector data.");
    timer_start();
    ns::vector<int>::pointer data = one.data();
    timer_stop();
    print_info("Vector data." + std::to_string(*data));
    print_time_info("Vector data.");
}

void test_vector::sizes()
{
    print_info("Vector sizes.");
    ns::vector<int> one;
    for (int i = 0; i < 200; i++)
    {
        one.push_back(i);
    }

    print_info("Vector size.");
    timer_start();
    print_info("Vector size " + std::to_string(one.size()));
    timer_stop();
    print_time_info("Vector size.");

    print_info("Vector max_size.");
    timer_start();
    print_info("Vector size " + std::to_string(one.max_size()));
    timer_stop();
    print_time_info("Vector max_size.");

    print_info("Vector resize.");

    print_info("Vector size before resize.");
    print_info("Vector size " + std::to_string(one.size()));
    timer_start();
    one.resize(4);
    print_info("Vector size after resize.");
    print_info("Vector size " + std::to_string(one.size()));
    timer_stop();
    print_time_info("Vector resize.");

    print_info("Vector reserve.");
    timer_start();
    one.reserve(5);
    timer_stop();
    print_info("Vector size " + std::to_string(one.size()));
    print_time_info("Vector reserve.");

    print_info("Vector empty.");
    timer_start();
    one.empty();
    timer_stop();
    print_info("Vector size " + std::to_string(one.size()));
    print_time_info("Vector empty.");

    print_info("Vector capacity.");
    timer_start();
    one.capacity();
    timer_stop();
    print_info("Vector capacity " + std::to_string(one.capacity()));
    print_time_info("Vector capacity.");
}

void test_vector::assigns()
{
    print_info("Vector resize.");

    ns::vector<int> one;
    for (int i = 0; i < 200; i++)
    {
        one.push_back(i);
    }
    ns::vector<int> two;
    print_info("Vector assign: it1, it2.");
    print_info("Vector two before assign size " + std::to_string(one.size()));
    timer_start();
    two.assign(one.begin(), one.end());
    timer_stop();
    print_time_info("Vector assign: it1, it2.");
    print_info("Vector two after assign size " + std::to_string(one.size()));


    print_info("Vector assign: size, val.");
    timer_start();
    one.assign(5,5);
    timer_stop();
    print_time_info("Vector assign: size, val.");
}

void test_vector::inserts()
{
    print_info("Vector insert.");

    ns::vector<int> one;
    for (int i = 0; i < 200; i++)
    {
        one.push_back(i);
    }

    ns::vector<int> two;
    for (int i = 200; i > 0; i--)
    {
        two.push_back(i);
    }

    print_info("Vector insert: position, value.");
    timer_start();
    one.insert(one.begin(), 5);
    timer_stop();
    print_time_info("Vector insert: position, value.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector insert: position, n, value.");
    timer_start();
    one.insert(one.begin(), 5, 9);
    timer_stop();
    print_time_info("Vector insert: position, n, value.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector insert: position, first, last.");
    timer_start();
    one.insert(one.begin(), 5);
    timer_stop();
    print_time_info("Vector insert: position, first, last.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }
}

void test_vector::push_pop()
{
    print_info("Vector insert.");
    ns::vector<int> one;
    for (int i = 200; i > 0; i--)
    {
        one.push_back(i);
    }
    print_info("Vector before push_back.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector after push_back.");
    timer_start();
    one.push_back(4);
    timer_stop();
    print_time_info("Vector push_back.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector pop.");
    timer_start();
    one.pop_back();
    timer_stop();
    print_time_info("Vector pop_back.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }
}

void test_vector::erases()
{
    print_info("Vector erases.");

    ns::vector<int> one;
    for (int i = 200; i > 0; i--)
    {
        one.push_back(i);
    }

    print_info("Vector erases before any erases.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector erase position.");
    timer_start();
    one.erase(one.begin());
    timer_stop();
    print_time_info("Vector erase position.");
    print_info("Vector erases after erase position.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

    print_info("Vector erase first last.");
    timer_start();
    one.erase(one.begin(), --one.end());
    timer_stop();
    print_time_info("Vector erase first last.");
    print_info("Vector erases after first last.");
    for (int i = 0; i < (int)one.size(); i++)
    {
        m_out_file << one[i] << std::endl;
    }

}

void test_vector::clear()
{
    print_info("Vector clear.");
    ns::vector<int> one;
    for (int i = 200; i > 0; i--)
    {
        one.push_back(i);
    }
    print_info("Vector before clear.");
    timer_start();
    one.clear();
    timer_stop();
    print_time_info("Vector clear.");
    print_info("Vector after clear.");
}

void test_vector::get_allocator()
{
    print_info("Vector get_allocator.");
    ns::vector<int> one;
    for (int i = 200; i > 0; i--)
    {
        one.push_back(i);
    }

    one.get_allocator();

}

void test_vector::swap()
{
    print_info("Vector swap.");
    ns::vector<int> first;
    ns::vector<int> second;
    for (int i = 0; i < 5; i++)
    {
        first.push_back(i);
    }
    for (int i = 5; i > 0; i--)
    {
        second.push_back(i);
    }
    print_info("Before swap.");
    for (int i = 0; i < 5; i++)
    {
        m_out_file << first[i] << std::endl;
    }
    timer_start();
    first.swap(second);
    timer_stop();
    print_time_info("Vector swap.");
    print_info("After swap.");
    for (int i = 0; i < 5; i++)
    {
        m_out_file << first[i] << std::endl;
    }
}
