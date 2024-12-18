/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxChecker.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:55:54 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 23:26:26 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/SyntaxChecker.hpp"

SyntaxChecker::SyntaxChecker()
{
}

SyntaxChecker::SyntaxChecker(std::string str): _str(str)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_set_operator = {'+', '-', '*', '/', '%'};
}

SyntaxChecker::SyntaxChecker(const SyntaxChecker& checker)
{
	*this = checker;
}

SyntaxChecker& SyntaxChecker::operator=(const SyntaxChecker& checker)
{
	if (this == &checker)
		return (*this);
	this->_str = checker._str;
	this->_set_alphabet = checker._set_alphabet;
	this->_set_operator = checker._set_operator;
	this->_struct_error = checker._struct_error;
	return (*this);
}

SyntaxChecker::~SyntaxChecker()
{
}

int	SyntaxChecker::check_each_str(int str_type, std::string str)
{
	if (!(check_question_mark(str_type, str)
		&& check_caret(str_type, str)
		&& check_brackets(str_type, ROUND_BRACKET, str)
		&& check_brackets(str_type, SQUARE_BRACKET, str)))
		return (0);
	return (1);
}

std::string 	SyntaxChecker::check(std::string str)
{
	std::string	str_cpy = str;

	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_each_str(LEFT_STR, left_str)
		&& check_each_str(RIGHT_STR, right_str)))
		return ("");

	OperatorConvertor	convertor(str);
	str = convertor.convert(str);

	OperatorChecker		checker(str_cpy);
	if (!checker.check(str))
		return ("");

	return (str);
}

void	SyntaxChecker::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "StntaxChecker.cpp";
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
	throw (ParseError::ParseException(this->_struct_error));
}

int	SyntaxChecker::check_question_mark(int str_type, std::string str)
{
	if (str.find("?") == std::string::npos)
		return (1);

	if (str_type == LEFT_STR && str.find("?") != std::string::npos)
	{
		throw_err_msg("SyntaxChecker::check_question_mark(std::string str)",
			"invalid use of question mark(?)", str.find("?"));
	}

	size_t pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	if (str.find("?") != str.length() - 1
		|| str.find("?", str.find("?") + 1) != std::string::npos)
		throw_err_msg("SyntaxChecker::check_question_mark(std::string str)",
			"invalid use of question mark(?)", pos + str.find("?"));
	return (1);
}

int	SyntaxChecker::check_caret_base(std::string str, size_t i, size_t pos)
{
	if (i == 0
		// || !(std::isdigit(str[i - 1])
		// || is_element_of_set(this->_set_alphabet, str[i - 1])
		// || str[i - 1] == ')'))
		|| is_element_of_set(this->_set_operator, str[i - 1]))
		throw_err_msg("SyntaxChecker::check_caret_base(std::string str, size_t i, size_t pos)",
			"incorrect location of caret(^): base is missed" , pos + i);
	return (1);
}

int	SyntaxChecker::skip_caret_power(std::string str, size_t i)
{
	if (str[i] == '(')
	{
		i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
	}
	while (str[i] == '('
		|| std::isdigit(str[i])
		|| is_element_of_set(this->_set_alphabet, str[i])
		|| str[i] == ')' || str[i] == ']')
		i++;
	return (i);
}

int	SyntaxChecker::check_caret_power(std::string str, size_t &i, size_t pos)
{
	if (i == str.length() - 1)
		throw_err_msg("SyntaxChecker::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect location of caret(^): power is missed", pos + str.length() - 1);

	i++;
	i = skip_caret_power(str, i);
	if (str[i] == '\0')
		return (1);

	if (str[i - 1] == '^')
		throw_err_msg("SyntaxChecker::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect location of caret(^): power is missed", pos + i - 1);
	if (str[i] == '^')
		throw_err_msg("SyntaxChecker::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect use of caret(^): used multiple times", pos + i);
	if (!is_element_of_set(this->_set_operator, str[i]))
		throw_err_msg("SyntaxChecker::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect power of caret(^): supports only int value for power", pos + i);
	return (1);
}

int	SyntaxChecker::check_caret(int str_type, std::string str)
{
	size_t	pos = 0;
	size_t	i = 0;

	if (str.find("^") == std::string::npos)
		return (1);

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			if (str[i + 1] && str[i + 1] == '^')
				throw_err_msg("SyntaxChecker::check_caret(std::string str)",
					"incorrect use of caret(^): used multiple times", pos + i + 1);
			if (!check_caret_base(str, i, pos))
				return (0);
			if (!check_caret_power(str, i, pos))
				return (0);
		}
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_brackets(int str_type, int bracket_type, std::string str)
{
	std::stack<char>	stack;
	char			bracket[2];
	size_t			pos = 0;
	size_t			i = 0;

	bracket[OPEN] = (bracket_type == ROUND_BRACKET) ? '(' : '[';
	bracket[CLOSE] = (bracket_type == ROUND_BRACKET) ? ')' : ']';

	if (str.find(std::string(1, bracket[CLOSE])) == std::string::npos
		&& str.find(std::string(1, bracket[OPEN])) == std::string::npos)
		return (1);

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;
	while (i < str.length())
	{
		if (str[i] == bracket[OPEN])
			stack.push(str[i]);
		if (str[i] == bracket[CLOSE])
		{
			
			if (str[i - 1] && str[i - 1] == bracket[OPEN])
				throw_err_msg("SyntaxChecker::check_brackets(int str_type, int bracket_type, std::string str)",
					"incorrect use of brackets: no character in the brackets", pos + i);
			if (stack.empty())
				throw_err_msg("SyntaxChecker::check_brackets(int str_type, int bracket_type, std::string str)",
					"incorrect use of brackets: bracket(s) not pair", pos + i);
			stack.pop();
		}
		i++;
	}
	if (!stack.empty())
		throw_err_msg("SyntaxChecker::check_brackets(int str_type, int bracket_type, std::string str)",
			"incorrect use of brackets: bracket(s) not pair", pos + i - 1);
	return (1);
}
