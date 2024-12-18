/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExponentSimplifier.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:35:32 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 21:05:28 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute/ExponentSimplifier.hpp"

ExponentSimplifier::ExponentSimplifier()
{
	this->_operator = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
}

ExponentSimplifier::ExponentSimplifier(const ExponentSimplifier& simplifier)
{
	*this = simplifier;
}

ExponentSimplifier& ExponentSimplifier::operator=(const ExponentSimplifier& simplifier)
{
	if (this == &simplifier)
		return (*this);
	//
	return (*this);
}

ExponentSimplifier::~ExponentSimplifier()
{
}

std::string	ExponentSimplifier::calculate(std::string str)
{
	this->_str = revert_str(this->_operator, this->_str);

	str = check_exponent(str);
	return (str);
}

void	ExponentSimplifier::throw_err_msg(std::string function,
				std::string err_msg, size_t pos_start, size_t pos_end)
{
	pos_start++;
	pos_end++;
	this->_struct_error.file_name = "ExponentSimplifier.cpp";
	this->_struct_error.cat = "exponent error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;

	this->_struct_error.term_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.term_str += "\t\t  ";
	this->_struct_error.term_str += RED;
	if (pos_start != std::string::npos && pos_start >= 1)
	{
		for (size_t i = 0; i < pos_start - 1; i++)
			this->_struct_error.term_str += " ";
	}
	for (size_t i = 0; i < pos_end - pos_start + 1; i++)
		this->_struct_error.term_str += "~";
	this->_struct_error.term_str += BLACK;
	throw (ExecuteError::ExecuteException(this->_struct_error));
}

std::string	ExponentSimplifier::get_base(std::string str, size_t i)
{
	size_t	base = i - 1;
	size_t	bracket = 0;

	if (str[base] != ')')
	{
		while (base && !is_key_of_map(this->_operator, str[base]))
			base--;
	}
	else
	{
		while (base &&  str[base] != '(')
		{
			base--;
			if (str[base] == ')')
				bracket++;
		}
		while (bracket && base)
		{
			base--;
			if (str[base] == '(')
				bracket--;
		}
	}
	return (str.substr(base, i - base));
}

std::string	ExponentSimplifier::get_power(std::string str, size_t &i)
{
	std::string	res;
	size_t		power = i + 1;

	while (str[power] != is_key_of_map(this->_operator, str[power])
		&& str[power] != '=' && str[power] != '\0')
		power++;
	power--;
	res = str.substr(i + 1, power - i);
	i = power + 1;
	return (res);
}

std::string	ExponentSimplifier::check_exponent(std::string str)
{
	std::string	base;
	std::string	power;
	size_t		i = 0;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			base = get_base(str, i);
			power = get_power(str, i);
			std::cout << "base: " << revert_str(this->_operator, base) << std::endl;
			std::cout << "power: " << revert_str(this->_operator, power) << std::endl;
			//remove bracket, check base and power
		}
		i++;
	}
	return (str);
}