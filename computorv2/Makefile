# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 09:51:42 by yhwang            #+#    #+#              #
#    Updated: 2024/12/16 15:36:19 by yhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computorv2
CPP = c++

READLINE_SRC_DIR = ./ReadLine/srcs/
READLINE_INCS_DIR = ./ReadLine/incs/

MATRIX_INCS_DIR = ./matrix/incs/

SRC_DIR = ./srcs/
INCS_DIR = ./incs/
SRC_PARSE_DIR = ./srcs/parse/
INCS_PARSE_DIR = ./incs/parse/
SRC_EXECUTE_DIR = ./srcs/execute/
INCS_EXECUTE_DIR = ./incs/execute/

CPPFLAGS = -Wall -Wextra -Werror -std=c++17 -g3 \
		-I$(READLINE_INCS_DIR) -I$(MATRIX_INCS_DIR) \
		-I$(INCS_DIR) -I$(INCS_PARSE_DIR) -I$(INCS_EXECUTE_DIR)

RM = rm -f

FILES = $(READLINE_SRC_DIR)ReadLine \
		$(SRC_DIR)main \
		$(SRC_PARSE_DIR)Parse \
		$(SRC_PARSE_DIR)InputConvertor \
		$(SRC_PARSE_DIR)SyntaxChecker \
		$(SRC_PARSE_DIR)OperatorConvertor \
		$(SRC_PARSE_DIR)OperatorChecker \
		$(SRC_PARSE_DIR)VectorMatrixChecker \
		$(SRC_PARSE_DIR)VariableConvertor \
		$(SRC_EXECUTE_DIR)ASTNode \
		$(SRC_EXECUTE_DIR)AST \
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
