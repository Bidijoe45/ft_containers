NAME = ft_containers
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -std=c++98 -Wall -Werror -Wextra -Wpedantic 
all: $(NAME)

$(NAME) : $(OBJS)
	clang++ $(OBJS) -o $(NAME) #-g -fsanitize=address

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
