/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 20:30:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_str = parse._str;
	this->_var = parse._var;
	this->_func = parse._func;
	return (*this);
}

Parse::~Parse()
{
}

void	Parse::set_var(std::map<std::string, std::string> var)
{
	this->_var = var;
}

void	Parse::set_func(std::map<std::string, std::string> func)
{
	this->_func = func;
}

std::string	Parse::parse(std::string &str)
{
	this->_str = str;
	return (check_str(str));
}

void	Parse::print_var(void)
{
	std::cout << YELLOW
		<< "╔═════════════════════╗" << std::endl
		<< "║    VARIABLE LIST    ║" << std::endl
		<< "╚═════════════════════╝" << BLACK << std::endl;
	if (this->_var.size() == 0)
		std::cout << MAGENTA
			<< "there is no variable assigned yet" << BLACK << std::endl;

	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
		it != this->_var.end(); it++)
	{
		std::cout << YELLOW << it->first << BLACK << std::endl
			<< it->second << std::endl
			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
	}
}

void	Parse::print_func(void)
{
	std::cout << YELLOW
		<< "╔═════════════════════╗" << std::endl
		<< "║    FUNCTION LIST    ║" << std::endl
		<< "╚═════════════════════╝" << BLACK << std::endl;
	if (this->_func.size() == 0)
		std::cout << MAGENTA
			<< "there is no function assigned yet" << BLACK << std::endl;

	for (std::map<std::string, std::string>::iterator it = this->_func.begin();
		it != this->_func.end(); it++)
	{
		std::cout << YELLOW << it->first << BLACK << std::endl
			<< it->second << std::endl
			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
	}
}

int	Parse::check_keyword(std::string str)
{
	if (str == "var" || str == "VAR"
		|| str == "variable" || str == "VARIABLE")
	{
		print_var();
		return (1);
	}
	else if (str == "func" || str == "FUNC"
		|| str == "function" || str == "FUNCTION")
	{
		print_func();
		return (1);
	}
	return (0);
}

void	Parse::print_str(std::string str) //remove later
{
	std::unordered_map<int, std::string>	op = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};

	for (size_t i = 0; i < str.length(); i++)
	{
		if (is_key_of_map(op, str[i]))
			std::cout << op[str[i]];
		else
			std::cout << str[i];
	}
}

std::string	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return (str);

	InputConvertor	input_convertor(str);
	str = input_convertor.convert(str);

	std::string	str_copy = str;

	SyntaxChecker	syntax_checker(str);
	str = syntax_checker.check(str);

	std::cout << "str before converting: ";//remove later
	print_str(str);//
	std::cout << std::endl;//

	VariableConvertor	variable_convertor(str_copy, this->_var, this->_func);
	str = variable_convertor.convert(str);

	std::cout << "str after converting: ";//remove later
	print_str(str);//
	std::cout << std::endl;//
	return (str);
}
