/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VariableConvertor.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:34 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:59:23 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/VariableConvertor.hpp"

VariableConvertor::VariableConvertor()
{
}

VariableConvertor::VariableConvertor(std::string str, std::map<std::string,
				std::string> var, std::map<std::string, std::string> func)
				: _str(str), _var(var), _func(func)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_operator = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};
}

VariableConvertor::VariableConvertor(const VariableConvertor& convertor)
{
	*this = convertor;
}

VariableConvertor& VariableConvertor::operator=(const VariableConvertor& convertor)
{
	if (this == &convertor)
		return (*this);
	this->_str = convertor._str;
	this->_set_alphabet = convertor._set_alphabet;
	this->_operator = convertor._operator;
	this->_var = convertor._var;
	this->_func = convertor._func;
	return (*this);
}

VariableConvertor::~VariableConvertor()
{
}

std::string	VariableConvertor::convert(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	return (convert_val_func(left_str) + "=" + convert_val_func(right_str));
}

std::vector<std::string>	VariableConvertor::split_term(std::string str)
{
	std::vector<std::string>	term;
	size_t				i = 0;
	std::string			tmp;

	while (1)
	{
		i = 0;
		while (!is_key_of_map(this->_operator, str[i])
			&& str[i] != '?' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		if (str.substr(0, i) != "")
			term.push_back(str.substr(0, i));
		if (str[i] != '?')
			term.push_back(std::string(1, str[i]));
		else
			term.push_back(std::string(1, str[i]));
		str = str.substr(i + 1, std::string::npos);
	}
	if (str != "")
		term.push_back(str);
	return (term);
}

void	VariableConvertor::process_variable_term(std::string &term)
{
	term = "(" + this->_var[term] + ")";
}

std::string	VariableConvertor::convert_func_variable(std::string term,
				std::string var_key, std::string var_value)
{
	std::string	name = get_function_name(term);
	std::string	variable = get_function_variable(term);
	std::string	front;
	std::string	back;

	if (variable == var_key)
		term = name + "(" + var_value + ")";
	else if (variable.find(var_key) != std::string::npos)
	{
		front = variable.substr(0, variable.find(var_key));
		back = variable.substr(variable.find(var_key) + var_key.length(), std::string::npos);

		if ((front == "" || !is_element_of_set(this->_set_alphabet, front[front.length() - 1]))
			&& !is_element_of_set(this->_set_alphabet, back[0]))
			term = name + "(" + front + "(" + var_value + ")" + back + ")";
	}
	return (term);
}

std::string	VariableConvertor::convert_func_name(std::string term,
				std::string func_key, std::string func_value)
{
	std::string	function;
	std::string	front;
	std::string	back;
	size_t		i = 0;

	if (get_function_name(term) == func_key)
	{
		function = func_value;
		while (i < function.length())
		{
			if (function[i] == 'x')
			{
				front = function.substr(0, i);
				back = function.substr(i + 1, std::string::npos);
				term = front + "(" + get_function_variable(term) + ")" + back;
				i = front.length() + get_function_variable(term).length() + 2;
			}
			else
				i++;
		}
	}
	term = "(" + term + ")";
	return (term);
}

void	VariableConvertor::process_function_term(std::string &term)
{
	std::string			func_name;

	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
		it != this->_var.end(); it++)
	{
		if (term.find(it->first) != std::string::npos)
		{
			term = convert_func_variable(term, it->first, it->second);
			func_name = get_function_name(term);;
			if (is_key_of_map(this->_func, func_name))
				term = convert_func_name(term, func_name, this->_func[func_name]);
		}
	}
}

std::string	VariableConvertor::convert_val_func(std::string &str)
{
	std::vector<std::string>	term = split_term(str);

	for(size_t i = 0; i < term.size(); i++)
	{
		if (is_key_of_map(this->_var, term[i]))
			process_variable_term(term[i]);
		if (term[i].find("(") != std::string::npos
			&& is_bracket_for_function(term[i], term[i].find("(")))
			process_function_term(term[i]);
	}
	str = "";
	for (size_t i = 0; i < term.size(); i++)
		str += term[i];
	return (str);
}
