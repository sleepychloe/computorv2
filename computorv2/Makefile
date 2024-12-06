# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 09:51:42 by yhwang            #+#    #+#              #
#    Updated: 2024/12/06 16:43:19 by yhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computorv2
CPP = c++

ReadLine_SRC_DIR = ./ReadLine/srcs/
ReadLine_INCS_DIR = ./ReadLine/incs/

SRC_DIR = ./srcs/
INCS_DIR = ./incs/

CPPFLAGS = -Wall -Wextra -Werror -std=c++17 -g3 -I$(ReadLine_INCS_DIR) -I$(INCS_DIR)

RM = rm -f

FILES = $(ReadLine_SRC_DIR)ReadLine \
		$(SRC_DIR)main \
		$(SRC_DIR)Parse \
		$(SRC_DIR)ASTNode \
		$(SRC_DIR)AST \
		$(SRC_DIR)Utils

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
