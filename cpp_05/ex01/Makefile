NAME = Form

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = main.cpp Form.cpp Bureaucrat.cpp

all:$(NAME)
$(NAME):$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean re