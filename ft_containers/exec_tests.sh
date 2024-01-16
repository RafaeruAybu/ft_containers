#!/bin/bash

#build project
make

#execute tester
./tester

#map
echo "map compares"
diff out_file_map_std out_file_map
#set
echo "set compares"
diff out_file_set_std out_file_set

#vector
echo "vector compares"
diff out_file_vector_std out_file_vector

#stack
echo "stack compares"
diff out_file_stack_std out_file_stack

#clear project
make fclean
