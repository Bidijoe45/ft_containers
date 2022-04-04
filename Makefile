NAME = ft_containers
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
all: $(NAME)

$(NAME) : $(OBJS)
	clang++ $(OBJS) -o $(NAME) #-g -fsanitize=address

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
