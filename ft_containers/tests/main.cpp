#include "test_vector.hpp"
#include "test_stack.hpp"
#include "test_map.hpp"
#include "test_set.hpp"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    {
        test_vector test_v("./out_file_vector", "./timing_file_vector");
        test_v.run_tests();

        test_stack test_st("./out_file_stack", "./timing_file_stack");
        test_st.run_tests();

        test_map test_m("./out_file_map", "./timing_file_map");
        test_m.run_tests();

        test_set test_set("./out_file_set", "./timing_file_set");
        test_set.run_tests();
    }

    {
        #define USING_STD
        test_vector test_v("./out_file_vector_std", "./timing_file_vector_std");
        test_v.run_tests();

        test_stack test_st("./out_file_stack_std", "./timing_file_stack_std");
        test_st.run_tests();

        test_map test_m("./out_file_map_std", "./timing_file_map_std");
        test_m.run_tests();

        test_set test_set("./out_file_set_std", "./timing_file_set_std");
        test_set.run_tests();
    }
    return 0;
}
