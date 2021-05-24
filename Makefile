NAME		= container

SRCDIR		= ./srcs/
INCDIR		= ./includes/

SRC			= main.cpp vector.cpp
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.cpp=.o)

INCDIR	= ./includes/

CC		= clang++
CCFLAG	= -std=c++98 -g -fsanitize=address -Wall -Wextra -Werror
RM		= rm -f

%.o:		%.cpp
			$(CC) $(CCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CCFLAG) -I$(INCDIR) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
