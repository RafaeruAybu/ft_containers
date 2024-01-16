#include "test_map.hpp"

test_map::test_map(std::string out_file, std::string timing_file)
{
    m_out_file.open(out_file, std::ios::out);
    m_timing_file.open(timing_file, std::ios::out);
}

test_map::~test_map()
{
    m_out_file.close();
    m_timing_file.close();
}

void test_map::run_tests()
{
    constructors();
    operators();
    get_allocator();
    at();
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

void test_map::constructors()
{
    print_info("Map constructors.");
    print_info("Map def constructor.");
    timer_start();
    ns::map<int, int> mp;
    timer_stop();
    print_time_info("Map def constructors.");

    print_info("Map first, last constructor.");
    mp.insert(ns::pair<int,int>(5,5));
    mp.insert(ns::pair<int,int>(6,6));
    timer_start();
    ns::map<int, int> mp2(mp.begin(), mp.end());
    timer_stop();
    print_time_info("Map first, last constructor.");
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).first << std::endl;
    }

    print_info("Map cpy constructor.");
    timer_start();
    ns::map<int, int> mp3(mp);
    timer_stop();
    print_time_info("Map cpy constructor.");
    for (ns::map<int, int>::iterator it = mp3.begin(); it != mp3.end(); ++it)
    {
        m_out_file << (*it).first << std::endl;
    }
}

void test_map::operators()
{
    print_info("Map operators.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map operators=.");
    ns::map<int, int> mp2;
    timer_start();
    mp2 = mp;
    timer_stop();
    print_time_info("Map operators=.");
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).second << std::endl;
    }

    m_out_file << mp[5] << std::endl;

    print_info("Map operators[].");
    m_out_file << "size: " << mp.size() << std::endl;
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    timer_start();
    m_out_file << "mp[1]: " << mp[0] << std::endl;
    timer_stop();
    print_time_info("Map operators[].");

    print_info("Map operators==.");
    timer_start();
    m_out_file << "mp == mp2: " << (mp == mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators==.");

    print_info("Map operators!=.");
    timer_start();
    m_out_file << "mp != mp2: " << (mp != mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators!=.");

    print_info("Map operators<.");
    timer_start();
    m_out_file << "mp < mp2: " << (mp < mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators<.");

    print_info("Map operators<=.");
    timer_start();
    m_out_file << "mp <= mp2: " << (mp <= mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators<=.");

    print_info("Map operators>.");
    timer_start();
    m_out_file << "mp > mp2: " << (mp > mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators>.");

    print_info("Map operators>=.");
    timer_start();
    m_out_file << "mp >= mp2: " << (mp >= mp2) << std::endl;
    timer_stop();
    print_time_info("Map operators>=.");
}

void test_map::get_allocator()
{
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map get_allocator.");
    timer_start();
    mp.get_allocator();
    timer_stop();
    print_time_info("Map get_allocator.");
}

void test_map::at()
{
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map at.");
    timer_start();
    print_info(std::to_string(mp.at(5)));
    timer_stop();
    print_time_info("Map at.");
    //todo do const test
}

void test_map::iterators()
{
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map iterators.");
    //begin
    print_info("Map begin.");
    timer_start();
    print_info(std::to_string(mp.begin()->second));
    timer_stop();
    print_time_info("Map begin.");

    //rbegin
    print_info("Map rbegin.");
    timer_start();
    print_info(std::to_string(mp.rbegin()->second));
    timer_stop();
    print_time_info("Map rbegin.");

    //end
    print_info("Map end.");
    timer_start();
    print_info(std::to_string(mp.end()->second));
    timer_stop();
    print_time_info("Map end.");

    //rend
    print_info("Map rend.");
    timer_start();
    print_info(std::to_string(mp.rend()->second));
    timer_stop();
    print_time_info("Map rend.");

}

void test_map::empty()
{
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map empty.");
    timer_start();
    print_info(std::to_string(mp.empty()));
    timer_stop();
    print_time_info("Map empty.");
}

void test_map::size()
{
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map size.");
    timer_start();
    print_info(std::to_string(mp.size()));
    timer_stop();
    print_time_info("Map size.");
}

void test_map::clear()
{
    print_info("Map clear.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));

    print_info("Map size before clear.");
    print_info(std::to_string(mp.size()));
    timer_start();
    mp.clear();
    timer_stop();
    print_time_info("Map clear.");
    print_info("Map size after clear.");
    print_info(std::to_string(mp.size()));
}

void test_map::insert()
{
    print_info("Map insert.");
    print_info("Map insert: val.");
    ns::map<int, int> mp;
    timer_start();
    mp.insert(ns::pair<int,int>(5,55));
    timer_stop();
    print_time_info("Map insert: val.");
    m_out_file << "size: " << mp.size() << std::endl;
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }

    print_info("Map insert: iter, val.");
    timer_start();
    mp.insert(mp.begin(), ns::pair<int,int>(5,55));
    timer_stop();
    print_time_info("Map insert: val.");
    m_out_file << "size: " << mp.size() << std::endl;
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }

    print_info("Map insert: first, last.");
    ns::map<int, int> mp2;
    timer_start();
    mp2.insert(mp.begin(), mp.end());
    timer_stop();
    m_out_file << "size: " << mp2.size() << std::endl;
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
}

void test_map::erase()
{
    print_info("Map erase.");
    print_info("Map erase: pos.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    print_info("Map size.");
    print_info(std::to_string(mp.size()));
    print_info("Map values before erase.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    timer_start();
    mp.erase(mp.begin());
    timer_stop();
    print_time_info("Map erase: pos.");
    print_info("Map values after erase.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }

    print_info("Map erase first, second.");
    mp.insert(ns::pair<int,int>(8,88));
    mp.insert(ns::pair<int,int>(9,99));
    mp.insert(ns::pair<int,int>(10,1010));
    mp.insert(ns::pair<int,int>(11,1111));
    print_info("Map values before erase.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    timer_start();
    mp.erase(mp.begin(), ++mp.begin());
    timer_stop();
    print_time_info("Map erase first, second.");
    print_info("Map values after erase.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }

    print_info("Map erase key.");
    timer_start();
    mp.erase(8);
    timer_stop();
    print_time_info("Map erase key.");
    print_info("Map values after erase.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
}

void test_map::swap()
{
    print_info("Map swap.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    ns::map<int, int> mp2;
    mp2.insert(ns::pair<int,int>(7,77));
    mp2.insert(ns::pair<int,int>(8,88));
    print_info("Map mp before swap.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    print_info("Map mp2 before swap.");
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }

    timer_start();
    mp.swap(mp2);
    timer_stop();
    print_time_info("Map swap.");

    print_info("Map mp after swap.");
    for (ns::map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    print_info("Map mp2 after swap.");
    for (ns::map<int, int>::iterator it = mp2.begin(); it != mp2.end(); ++it)
    {
        m_out_file << (*it).first << ":" << (*it).second << std::endl;
    }
    print_info("POG CHUMP, OMEGALUL");
}

void test_map::count()
{
    print_info("Map count.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    timer_start();
    print_info(std::to_string(mp.count(5)));
    timer_stop();
    print_time_info("Map count.");
}

void test_map::find()
{
    print_info("Map find.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    timer_start();
    print_info(std::to_string(mp.find(5)->second));
    timer_stop();
    print_time_info("Map find.");
}

void test_map::equal_range()
{
    print_info("Map equal_range.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    timer_start();
    print_info(std::to_string(mp.equal_range(5).first->second));
    timer_stop();
    print_time_info("Map equal_range.");
}

void test_map::lower_bound()
{
    print_info("Map lower_bound.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    mp.insert(ns::pair<int,int>(7,77));
    timer_start();
    print_info(std::to_string(mp.lower_bound(6)->first));
    timer_stop();
    print_time_info("Map lower_bound.");
}

void test_map::upper_bound()
{
    print_info("Map upper_bound.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    mp.insert(ns::pair<int,int>(7,77));
    timer_start();
    print_info(std::to_string(mp.upper_bound(6)->first));
    timer_stop();
    print_time_info("Map upper_bound.");
}

void test_map::key_compare()
{
    print_info("Map key_compare.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    mp.insert(ns::pair<int,int>(7,77));
    timer_start();
    mp.key_comp();
    timer_stop();
    print_time_info("Map key_compare.");
}

void test_map::value_comp()
{
    print_info("Map value_comp.");
    ns::map<int, int> mp;
    mp.insert(ns::pair<int,int>(5,55));
    mp.insert(ns::pair<int,int>(6,66));
    mp.insert(ns::pair<int,int>(7,77));
    timer_start();
    mp.value_comp();
    timer_stop();
    print_time_info("Map value_comp.");
}
