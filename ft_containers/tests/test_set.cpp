#include "test_set.hpp"

test_set::test_set(std::string out_file, std::string timing_file)
{
    m_out_file.open(out_file, std::ios::out);
    m_timing_file.open(timing_file, std::ios::out);
}

test_set::~test_set()
{
    m_out_file.close();
    m_timing_file.close();
}

void test_set::run_tests()
{
    constructors();
    operators();
    get_allocator();
    iterators();
    empty();
    size();
    clear();
    insert();
    erase();
    swap();
    count();
    find();
    equal_range();
    lower_bound();
    upper_bound();
    key_compare();
    value_comp();
}

void test_set::constructors()
{
    print_info("Set constructors.");
    print_info("Set def constructor.");
    timer_start();
    ns::set<int> st;
    timer_stop();
    print_time_info("Set def constructors.");

    print_info("Set first, last constructor.");
    st.insert(5);
    st.insert(6);
    timer_start();
    ns::set<int> st2(st.begin(), st.end());
    timer_stop();
    print_time_info("Set first, last constructor.");
    for (ns::set<int>::iterator it = st2.begin(); it != st2.end(); ++it)
    {
        m_out_file << *it << std::endl;
    }

    print_info("Set cpy constructor.");
    timer_start();
    ns::set<int> st3(st);
    timer_stop();
    print_time_info("Set cpy constructor.");
    for (ns::set<int>::iterator it = st3.begin(); it != st3.end(); ++it)
    {
        m_out_file << *it << std::endl;
    }
}

void test_set::operators()
{
    print_info("Set operators.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    print_info("Set operators=.");
    ns::set<int> st2;
    timer_start();
    st2 = st;
    timer_stop();
    print_time_info("Set operators=.");
    for (ns::set<int>::iterator it = st2.begin(); it != st2.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    print_info("Set operators==.");
    timer_start();
    m_out_file << "st == st2: " << (st == st2) << std::endl;
    timer_stop();
    print_time_info("Set operators==.");

    print_info("Set operators!=.");
    timer_start();
    m_out_file << "st != st2: " << (st != st2) << std::endl;
    timer_stop();
    print_time_info("Set operators!=.");

    print_info("Set operators<.");
    timer_start();
    m_out_file << "st < st2: " << (st < st2) << std::endl;
    timer_stop();
    print_time_info("Set operators<.");

    print_info("Set operators<=.");
    timer_start();
    m_out_file << "st <= st2: " << (st <= st2) << std::endl;
    timer_stop();
    print_time_info("Set operators<=.");

    print_info("Set operators>.");
    timer_start();
    m_out_file << "st > st2: " << (st > st2) << std::endl;
    timer_stop();
    print_time_info("Set operators>.");

    print_info("Set operators>=.");
    timer_start();
    m_out_file << "st >= st2: " << (st >= st2) << std::endl;
    timer_stop();
    print_time_info("Set operators>=.");
}

void test_set::get_allocator()
{
    print_info("Set get_allocator.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    timer_start();
    st.get_allocator();
    timer_stop();
    print_time_info("Set get_allocator.");
}

void test_set::iterators()
{
    print_info("Set iterators.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    print_info("Set iterators.");
    //begin
    print_info("Set begin.");
    timer_start();
    print_info(std::to_string(*st.begin()));
    timer_stop();
    print_time_info("Set begin.");

    //rbegin
    print_info("Set rbegin.");
    timer_start();
    print_info(std::to_string(*st.rbegin()));
    timer_stop();
    print_time_info("Set rbegin.");

    //end
    print_info("Set end.");
    timer_start();
    print_info(std::to_string(*st.end()));
    timer_stop();
    print_time_info("Set end.");

    //rend
    print_info("Set rend.");
    timer_start();
    print_info(std::to_string(*st.rend()));
    timer_stop();
    print_time_info("Set rend.");
}

void test_set::empty()
{
    print_info("Set estty.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    timer_start();
    print_info(std::to_string(st.empty()));
    timer_stop();
    print_time_info("Set estty.");
}

void test_set::size()
{
    print_info("Set size.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    timer_start();
    print_info(std::to_string(st.size()));
    timer_stop();
    print_time_info("Set size.");
}

void test_set::clear()
{
    print_info("Set clear.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);

    print_info("Set size before clear.");
    print_info(std::to_string(st.size()));
    timer_start();
    st.clear();
    timer_stop();
    print_time_info("Set clear.");
    print_info("Set size after clear.");
    print_info(std::to_string(st.size()));
}

void test_set::insert()
{
    print_info("Set insert.");
    print_info("Set insert: val.");
    ns::set<int> st;
    timer_start();
    st.insert(5);
    timer_stop();
    print_time_info("Set insert: val.");
    m_out_file << "size: " << st.size() << std::endl;
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    print_info("Set insert: iter, val.");
    timer_start();
    st.insert(st.begin(), 6);
    timer_stop();
    print_time_info("Set insert: val.");
    m_out_file << "size: " << st.size() << std::endl;
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    print_info("Set insert: first, last.");
    ns::set<int> st2;
    timer_start();
    st2.insert(st.begin(), st.end());
    timer_stop();
    m_out_file << "size: " << st2.size() << std::endl;
    for (ns::set<int>::iterator it = st2.begin(); it != st2.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
}

void test_set::erase()
{
    print_info("Set erase.");
    print_info("Set erase.");
    print_info("Set erase: pos.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    print_info("Set size.");
    print_info(std::to_string(st.size()));
    print_info("Set values before erase.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
    timer_start();
    st.erase(st.begin());
    timer_stop();
    print_time_info("Set erase: pos.");
    print_info("Set values after erase.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    print_info("Set erase first, second.");
    st.insert(8);
    st.insert(9);
    st.insert(10);
    st.insert(11);
    print_info("Set values before erase.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
    timer_start();
    st.erase(st.begin(), ++st.begin());
    timer_stop();
    print_time_info("Set erase first, second.");
    print_info("Set values after erase.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    print_info("Set erase key.");
    timer_start();
    st.erase(8);
    timer_stop();
    print_time_info("Set erase key.");
    print_info("Set values after erase.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
}

void test_set::swap()
{
    print_info("Set swap.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    ns::set<int> st2;
    st2.insert(7);
    st2.insert(8);
    print_info("Set st before swap.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
    print_info("Set st2 before swap.");
    for (ns::set<int>::iterator it = st2.begin(); it != st2.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }

    timer_start();
    st.swap(st2);
    timer_stop();
    print_time_info("Set swap.");

    print_info("Set st after swap.");
    for (ns::set<int>::iterator it = st.begin(); it != st.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
    print_info("Set st2 after swap.");
    for (ns::set<int>::iterator it = st2.begin(); it != st2.end(); ++it)
    {
        m_out_file << (*it) << std::endl;
    }
    print_info("POG CHUMP, OMEGALUL");
}

void test_set::count()
{
    print_info("Set count.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    timer_start();
    print_info(std::to_string(st.count(5)));
    timer_stop();
    print_time_info("Set count.");
}

void test_set::find()
{
    print_info("Set find.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    timer_start();
    *st.find(5);
    print_info(std::to_string(*st.find(5)));
    timer_stop();
    print_time_info("Set find.");
}

void test_set::equal_range()
{
    print_info("Set equal_range.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    timer_start();
    print_info(std::to_string(*st.equal_range(5).first));
    timer_stop();
    print_time_info("Set equal_range.");
}

void test_set::lower_bound()
{
    print_info("Set lower_bound.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    st.insert(7);
    timer_start();
    print_info(std::to_string(*st.lower_bound(6)));
    timer_stop();
    print_time_info("Set lower_bound.");
}

void test_set::upper_bound()
{
    print_info("Set upper_bound.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    st.insert(7);
    timer_start();
    print_info(std::to_string(*st.upper_bound(6)));
    timer_stop();
    print_time_info("Set upper_bound.");
}

void test_set::key_compare()
{
    print_info("Set key_compare.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    st.insert(7);
    timer_start();
    st.key_comp();
    timer_stop();
    print_time_info("Set key_compare.");
}

void test_set::value_comp()
{
    print_info("Set value_cost.");
    ns::set<int> st;
    st.insert(5);
    st.insert(6);
    st.insert(7);
    timer_start();
    st.value_comp();
    timer_stop();
    print_time_info("Set value_comp.");
}
