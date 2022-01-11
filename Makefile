NAME = ft_containers
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	clang++ $(OBJS) -o $(NAME) -std=c++98 -g3 -fsanitize=address

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
