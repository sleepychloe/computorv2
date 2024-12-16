/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputConvertor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:08:15 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 20:18:44 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/InputConvertor.hpp"

InputConvertor::InputConvertor()
{
}

InputConvertor::InputConvertor(std::string str): _str(str)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i', 'I'};
	this->_set_vector_matrix = { '[', ']', ',', ';'};
	this->_set_operator = {'+', '-', '*', '/', '%', '^'};
	this->_set_other = {'(', ')','^', '=', '?'};
	this->_set_space = {' ', '\t'};
}

InputConvertor::InputConvertor(const InputConvertor& convertor)
{
	*this = convertor;
}

InputConvertor& InputConvertor::operator=(const InputConvertor& convertor)
{
	if (this == &convertor)
		return (*this);
	this->_str = convertor._str;
	this->_set_alphabet = convertor._set_alphabet;
	this->_set_number = convertor._set_number;
	this->_set_vector_matrix = convertor._set_vector_matrix;
	this->_set_operator = convertor._set_operator;
	this->_set_other = convertor._set_other;
	this->_set_space = convertor._set_space;
	this->_struct_error = convertor._struct_error;
	return (*this);
}

InputConvertor::~InputConvertor()
{
}

std::string	InputConvertor::convert(std::string str)
{
	if (!(is_equation_form(str) && check_invalid_character(str) && check_number(str)))
		return ("");
	convert_to_standard_form(str);
	return (this->_str);
}

void	InputConvertor::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "InputConvertor.cpp";
	this->_struct_error.cat = "input error";
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

int	InputConvertor::check_equal_sign(std::string str)
{
	int	flag = 0;
	size_t	i = 0;
	
	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		if (flag > 1)
			throw_err_msg("InputConvertor::check_equal_sign(std::string str)",
				"equal(=) sign used multiple times", i);
		i++;
	}
	if (!flag)
		throw_err_msg("InputConvertor::check_equal_sign(std::string str)",
			"equal(=) sign is missing", i);
	return (1);
}

int 	InputConvertor::check_each_term(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '=')
			throw_err_msg("InputConvertor::check_each_term(std::string str)",
				"invalid equation form: left term does not exist", i);

		while (str[i] != '=')
			i++;
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			break ;
		else
			throw_err_msg("InputConvertor::check_each_term(std::string str)",
				"invalid equation form: right term does not exist", i);
	}
	return (1);
}

int	InputConvertor::is_equation_form(std::string str)
{
	return (check_equal_sign(str) && check_each_term(str));
}

int	InputConvertor::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(is_element_of_set(this->_set_alphabet, str[i])
			|| is_element_of_set(this->_set_number, str[i])
			|| is_element_of_set(this->_set_vector_matrix, str[i])
			|| is_element_of_set(this->_set_operator, str[i])
			|| is_element_of_set(this->_set_other, str[i])
			|| is_element_of_set(this->_set_space, str[i])))
			throw_err_msg("InputConvertor::check_invalid_character(std::string str)",
				"invalid character exists", i);
		i++;
	}
	return (1);
}

int	InputConvertor::check_float_point(std::string str)
{
	size_t	i = 0;
	int	point;
	int	digit;

	while (i < str.length())
	{
		point = 0;
		digit = 0;
		if (str[i] == '.')
		{
			point++;
			i++;
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				if (str[i] == '.')
					point++;
				else
					digit++;
				if (digit > 5)
					throw_err_msg("InputConvertor::check_float_point(std::string str)",
						"incorrect use of floating point: supports up to the fifth decimal place", i);
				if (point > 1)
					throw_err_msg("InputConvertor::check_float_point(std::string str)",
							"incorrect use of floating point: used multiple times in one number", i);
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	InputConvertor::check_number(std::string str)
{
	size_t	i = 0;
	int	space = 0;

	while (i < str.length())
	{
		space = 0;
		if ('0' <= str[i] && str[i] <= '9')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
			{
				space++;
				i++;
			}
			if (space && ('0' <= str[i] && str[i] <= '9'))
				throw_err_msg("InputConvertor::check_number(std::string str)",
					"no operator between numbers", i - 1);
		}
		if (str[i] == '.')
		{
			if (!((str[i - 1] && ('0' <= str[i - 1] && str[i - 1] <= '9'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
				throw_err_msg("InputConvertor::check_number(std::string str)",
					"incorrect location of floating point", i);
		}
		i++;
	}
	return (check_float_point(str));
}

void	InputConvertor::remove_space(std::string &str)
{
	size_t		i = 0;
	std::string	new_str = "";

	while (i < str.size())
	{
		if (str[i] != ' ' && str[i] != '\t')
			new_str += str[i];
		i++;
	}
	str = new_str;
}

void	InputConvertor::convert_to_lower_case(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::tolower(str[i]);
}

void	InputConvertor::convert_to_standard_form(std::string &str)
{
	std::string	front;
	std::string	back;
	size_t		i = 0;

	remove_space(str);
	convert_to_lower_case(str);

	if (str[i] == '+')
		str = str.substr(1, std::string::npos);
	else if (str[i] == '-')
		str = "-1*" + str.substr(1, std::string::npos);

	/* standard form: ax to a*x, af(x) to a*f(x), a is number */
	while (i < str.length())
	{
		if (is_element_of_set(this->_set_number, str[i])
			&& str[i + 1]
			&& !is_element_of_set(this->_set_number, str[i + 1])
			&& is_element_of_set(this->_set_alphabet, str[i + 1]))
		{
			i++;
			front = str.substr(0, i);
			back = str.substr(i, std::string::npos);
			str = front + "*" + back;
		}
		i++;
	}
	this->_str = str;
}
