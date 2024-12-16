/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorChecker.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:03:28 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 16:39:36 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/OperatorChecker.hpp"

OperatorChecker::OperatorChecker()
{
}

OperatorChecker::OperatorChecker(std::string str): _str(str)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_operator = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};
}

OperatorChecker::OperatorChecker(const OperatorChecker& checker)
{
	*this = checker;
}

OperatorChecker& OperatorChecker::operator=(const OperatorChecker& checker)
{
	if (this == &checker)
		return (*this);
	this->_str = checker._str;
	this->_set_alphabet = checker._set_alphabet;
	this->_operator = checker._operator;
	this->_struct_error = checker._struct_error;
	return (*this);
}

OperatorChecker::~OperatorChecker()
{
}

int	OperatorChecker::check(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_operator(LEFT_STR, left_str)
		&& check_operator(RIGHT_STR, right_str)
		&& check_operator_near_brackets(LEFT_STR, left_str)
		&& check_operator_near_brackets(RIGHT_STR, right_str)))
		return (0);
	return (1);
}

void	OperatorChecker::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "OperatorChecker.cpp";
	this->_struct_error.cat = "syntax error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	this->_struct_error.pos = pos;

	this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.pos_str += "\t\t  ";
	this->_struct_error.pos_str += RED;
	if (pos != std::string::npos && pos >= 1)
	{
		for (size_t i = 0; i < pos - 1; i++)
			this->_struct_error.pos_str += "~";
	}
	this->_struct_error.pos_str += "^";
	this->_struct_error.pos_str += BLACK;
	throw (Error::ParseException(this->_struct_error));
}

int	OperatorChecker::check_first_sign(std::string str, size_t pos)
{
	size_t	i = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;
	if (is_key_of_map(this->_operator, str[i]))
		throw_err_msg("OperatorChecker::check_operator(int str_type, std::string str)",
			"invalid use of operator: expect number before using operator", pos + i);
	if (is_key_of_map(this->_operator, str[str.length() - 1]))
		throw_err_msg("OperatorChecker::check_operator(int str_type, std::string str)",
			"invalid use of operator: expect number after using operator", pos + str.length() - 1);
	return (i);
}

int	OperatorChecker::check_operator_bracket_str(std::string str, size_t i, size_t pos)
{
	std::string	sub_str;

	sub_str = str.substr(i + 1, skip_bracket(ROUND_BRACKET, str, i) - i - 1);
	check_operator(pos + i + 1, sub_str);
	i = skip_bracket(ROUND_BRACKET, str, i);
	return (i);
}

int	OperatorChecker::check_operator(int str_type, std::string str)
{
	size_t		pos = 0;
	size_t		i = 0;

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;
	if (!(str_type == LEFT_STR || str_type == RIGHT_STR))
		pos = str_type;

	i = check_first_sign(str, pos);
	while (i < str.length())
	{
		if (str[i] == '(' && !is_bracket_for_function(str, i))
			i = check_operator_bracket_str(str, i, pos);
		if (is_key_of_map(this->_operator, str[i]))
		{
			i++;
			if (is_key_of_map(this->_operator, str[i]))
				throw_err_msg("OperatorChecker::check_operator(int str_type, std::string str)",
					"invalid use of operator: expect number before using operator", pos + i);
		}
		i++;
	}
	return (1);
}

void	OperatorChecker::check_before_open_bracket(std::string str, size_t open_idx, size_t pos)
{
	if (open_idx > 0)
	{
		if (open_idx == 1 && (str[0] == '+' || str[0] == '-'))
			return ;
		if (!(str[open_idx - 1] == '('
			|| is_key_of_map(this->_operator, str[open_idx - 1])))
		{
			if (str[open_idx] == '(' || str[open_idx] == ROUND_OPEN)
				throw_err_msg("OperatorChecker::check_before_open_bracket(std::string str, size_t open_idx, size_t pos)",
					"invalid use of operator: expect operator before opening round bracket", pos - 1);
			else
				throw_err_msg("OperatorChecker::check_before_open_bracket(std::string str, size_t open_idx, size_t pos)",
					"invalid use of operator: expect operator before opening square bracket", pos - 1);
		}
	}
}

void	OperatorChecker::check_after_close_bracket(std::string str, size_t close_idx, size_t pos)
{
	if (close_idx < str.length() - 1)
	{
		if (!(str[close_idx + 1] == '\0'
			|| str[close_idx + 1] == ')'
			|| is_key_of_map(this->_operator, str[close_idx + 1])))
		{
			if (str[close_idx] == ')' || str[close_idx] == ROUND_CLOSE)
				throw_err_msg("OperatorChecker::check_after_close_bracket(std::string str, size_t close_idx, size_t pos)",
					"invalid use of operator: expect operator after closing round bracket", pos + 1);
			else
				throw_err_msg("OperatorChecker::check_after_close_bracket(std::string str, size_t close_idx, size_t pos)",
					"invalid use of operator: expect operator after closing square bracket", pos + 1);
		}
	}
}

int	OperatorChecker::check_for_vector_matrix(std::string &str, size_t i, size_t pos)
{
	size_t	close = skip_bracket(SQUARE_BRACKET, str, i);

	check_before_open_bracket(str, i, pos + i);
	check_after_close_bracket(str, close, pos + close);

	while (i <= close)
	{
		if (str[i] == '[')
			str[i] = SQUARE_OPEN;
		if (str[i] == ']')
			str[i] = SQUARE_CLOSE;
		i++;
	}
	return (close);
}

int	OperatorChecker::check_for_function(std::string &str, size_t i, size_t pos)
{
	while (str[i] != ')')
	{
		if (str[i] == '(')
			str[i] = ROUND_OPEN;
		i++;
	}
	str[i] = ROUND_CLOSE;
	check_after_close_bracket(str, i, pos + i);
	return (i);
}

int	OperatorChecker::check_for_round_brackets(std::string str, size_t pos)
{
	std::string	front;
	std::string	back;
	std::string	bracket;

	while (1)
	{
		bracket = get_bracket_str(str);
		if (bracket == "")
			return (1) ;
		front = str.substr(0, str.find(bracket));
		back = str.substr(str.find(bracket) + bracket.length(), std::string::npos);

		check_before_open_bracket(str, front.length(), pos + front.length());
		check_after_close_bracket(str, front.length() + bracket.length() - 1, pos + front.length() + bracket.length() - 1);

		str = front + std::string(1, ROUND_OPEN)
			+ bracket.substr(1, bracket.length() - 2)
			+ std::string(1, ROUND_CLOSE) + back;
	}
	return (1);
}

int	OperatorChecker::check_operator_near_brackets(int str_type, std::string str)
{
	size_t		pos = 0;
	size_t		i = 0;

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	while (i < str.length())
	{
		if (str[i] == '[')
			i = check_for_vector_matrix(str, i, pos);
		else if (str[i] == '(' && is_bracket_for_function(str, i))
			i = check_for_function(str, i, pos);
		i++;
	}
	return (check_for_round_brackets(str, pos));
}
