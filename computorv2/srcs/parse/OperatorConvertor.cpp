/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorConvertor.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:59:54 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:55:13 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/OperatorConvertor.hpp"

OperatorConvertor::OperatorConvertor()
{
}

OperatorConvertor::OperatorConvertor(std::string str): _str(str)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i', 'I'};
	this->_set_operator = {'+', '-', '*', '/', '%', '^'};
	this->_set_other = {'(', ')','^', '=', '?'};
}

OperatorConvertor::OperatorConvertor(const OperatorConvertor& convertor)
{
	*this = convertor;
}

OperatorConvertor& OperatorConvertor::operator=(const OperatorConvertor& convertor)
{
	if (this == &convertor)
		return (*this);
	this->_str = convertor._str;
	this->_set_alphabet = convertor._set_alphabet;
	this->_set_number = convertor._set_number;
	this->_set_operator = convertor._set_operator;
	this->_set_other = convertor._set_other;
	this->_struct_error = convertor._struct_error;
	return (*this);
}

OperatorConvertor::~OperatorConvertor()
{
}
std::string	OperatorConvertor::convert(std::string str)
{
	return (convert_operator(str));
}

void	OperatorConvertor::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "OperatorConvertor.cpp";
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

int	OperatorConvertor::skip_vector_matrix(std::string str,
				std::string &new_str, size_t i, size_t pos)
{
	if (str[i] != '[')
		return (i);

	std::string		bracket;
	size_t			start = i;

	i = skip_bracket(SQUARE_BRACKET, str, i);
	bracket = str.substr(start, i - start + 1);

	VectorMatrixChecker	checker(this->_str, pos);

	if (bracket.find("[", 1) == std::string::npos)
		checker.vector_check(bracket);
	else
		checker.matrix_check(bracket);

	new_str += bracket;
	i++;
	return (i);
}

int	OperatorConvertor::skip_function(std::string str, std::string &new_str, size_t i)
{
	new_str += str.substr(i, skip_bracket(ROUND_BRACKET, str, i) - i + 1);
	i = skip_bracket(ROUND_BRACKET,  str, i) + 1;
	return (i);
}

int	OperatorConvertor::skip_vector_matrix_function(std::string str,
				std::string &new_str, size_t i, size_t pos)
{
	i = skip_vector_matrix(str, new_str, i, pos + i);
	if (!(is_element_of_set(this->_set_alphabet, str[i])
		|| is_element_of_set(this->_set_number, str[i])
		|| is_element_of_set(this->_set_operator, str[i])
		|| is_element_of_set(this->_set_other, str[i])
		|| str[i] == '\0'))
		throw_err_msg("OperatorConvertor::skip_vector_matrix_function(std::string str, std::string &new_str, size_t i, size_t pos)",
			"invalid character exists", pos + i);
	if (str[i] == '(' && is_bracket_for_function(str, i))
		i = skip_function(str, new_str, i);
	return (i);
}

char	OperatorConvertor::do_convert(std::string str, size_t &i)
{
	std::unordered_map<char, int> op = {{'+', OP_ADD}, {'-', OP_SUB},
					{'*', OP_MUL}, {'/', OP_DIV},
					{'%', OP_MODULO}, {'^', OP_POWER}};
	if (str[i] == '+' || str[i] == '-')
	{
		if (i > 1 && (str[i - 1] == '(' || str[i - 1] == '^' || str[i - 1] == '='
					|| str[i - 1] == OP_MUL || str[i - 1] == OP_MAT_MUL
					|| str[i - 1] == OP_DIV || str[i - 1] == OP_MODULO))
			return (str[i]);
	}
	else if (str[i] == '*')
	{
		if (str[i + 1] && str[i + 1] == '*')
		{
			i = i + 1;
			return (OP_MAT_MUL);
		}
	}
	return (op[str[i]]);
}

std::string	OperatorConvertor::convert_operator(std::string str)
{
	std::string	new_str = "";
	size_t		pos = 0;
	size_t		i = 0;

	if (str[i] == '+' || str[i] == '-')
	{
		new_str += str[i];
		i++;
	}

	while (i < str.length())
	{
		i = skip_vector_matrix_function(str, new_str, i, pos);
		if (i >  str.length() - 1)
			break ;
		if (is_element_of_set(this->_set_operator, str[i]))
			new_str += do_convert(str, i);
		else
			new_str += str[i];
		i++;
	}
	return (new_str);
}
