NAME	= tester
SRC		= tests/main.cpp \
          tests/test_map.cpp \
          tests/test_set.cpp \
          tests/test_stack.cpp \
          tests/test_vector.cpp
HDRS    = tests/test_map.hpp \
          tests/test_set.hpp \
          tests/test_stack.hpp \
          tests/test_vector.hpp
CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
OBJ		= $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
