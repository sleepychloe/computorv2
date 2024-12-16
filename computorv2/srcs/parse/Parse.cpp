/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:27:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse/Parse.hpp"

Parse::Parse()
{
	// this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
	// 		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	// 		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	// 		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	// this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i', 'I'};
	// this->_set_vector_matrix = { '[', ']', ',', ';'};
	// this->_set_operation = {'+', '-', '*', '/', '%', '^'};
	// this->_set_other = {'(', ')','^', '=', '?'};
	// this->_set_space = {' ', '\t'};
	// this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
	// 			{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	// this->_str = parse._str;
	// this->_set_alphabet = parse._set_alphabet;
	// this->_set_number = parse._set_number;
	// this->_set_vector_matrix = parse._set_vector_matrix;
	// this->_set_operation = parse._set_operation;
	// this->_set_other = parse._set_other;
	// this->_set_space = parse._set_space;
	// this->_operation = parse._operation;
	// this->_var = parse._var;
	// this->_func = parse._func;
	// this->_struct_error = parse._struct_error;
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

std::string	Parse::parse_start(std::string &str)
{
	this->_str = str;
	return (check_str(str));
}

int	Parse::check_keyword(std::string str)
{
	if (str == "var" || str == "VAR"
		|| str == "vriable" || str == "VARIABLE")
	{
		return (1);
	}
	else if (str == "func" || str == "FUNC"
		|| str == "function" || str == "FUNCTION")
	{
		return (1);
	}
	return (0);
}



// std::vector<std::string>	Parse::split_term(std::string str)
// {
// 	std::vector<std::string>	term;
// 	size_t				i = 0;
// 	std::string			tmp;

// 	while (1)
// 	{
// 		i = 0;
// 		while (!is_key_of_map(this->_operation, str[i])
// 			&& str[i] != '?' && str[i] != '\0')
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		if (str.substr(0, i) != "")
// 			term.push_back(str.substr(0, i));
// 		if (str[i] != '?')
// 			term.push_back(std::string(1, str[i]));
// 		else
// 			term.push_back(std::string(1, str[i]));
// 		str = str.substr(i + 1, std::string::npos);
// 	}
// 	if (str != "")
// 		term.push_back(str);
// 	return (term);
// }

// void	Parse::process_variable_term(std::string &term)
// {
// 	term = "(" + this->_var[term] + ")";
// }

// std::string	Parse::convert_func_variable(std::string term,
// 				std::string var_key, std::string var_value)
// {
// 	std::string	name = get_function_name(term);
// 	std::string	variable = get_function_variable(term);
// 	std::string	front;
// 	std::string	back;

// 	if (variable == var_key)
// 		term = name + "(" + var_value + ")";
// 	else if (variable.find(var_key) != std::string::npos)
// 	{
// 		front = variable.substr(0, variable.find(var_key));
// 		back = variable.substr(variable.find(var_key) + var_key.length(), std::string::npos);

// 		if ((front == "" || !is_element_of_set(this->_set_alphabet, front[front.length() - 1]))
// 			&& !is_element_of_set(this->_set_alphabet, back[0]))
// 			term = name + "(" + front + "(" + var_value + ")" + back + ")";
// 	}
// 	return (term);
// }

// std::string	Parse::convert_func_name(std::string term,
// 				std::string func_key, std::string func_value)
// {
// 	std::string	function;
// 	std::string	front;
// 	std::string	back;
// 	size_t		i = 0;

// 	if (get_function_name(term) == func_key)
// 	{
// 		function = func_value;
// 		while (i < function.length())
// 		{
// 			if (function[i] == 'x')
// 			{
// 				front = function.substr(0, i);
// 				back = function.substr(i + 1, std::string::npos);
// 				term = front + "(" + get_function_variable(term) + ")" + back;
// 				i = front.length() + get_function_variable(term).length() + 2;
// 			}
// 			else
// 				i++;
// 		}
// 	}
// 	term = "(" + term + ")";
// 	return (term);
// }

// void	Parse::process_function_term(std::string &term)
// {
// 	std::string			func_name;

// 	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
// 		it != this->_var.end(); it++)
// 	{
// 		if (term.find(it->first) != std::string::npos)
// 		{
// 			term = convert_func_variable(term, it->first, it->second);
// 			func_name = get_function_name(term);;
// 			if (is_key_of_map(this->_func, func_name))
// 				term = convert_func_name(term, func_name, this->_func[func_name]);
// 		}
// 	}
// }

// void	Parse::convert_val_func(std::string &str)
// {
// 	std::vector<std::string>	term = split_term(str);

// 	for(size_t i = 0; i < term.size(); i++)
// 	{
// 		if (is_key_of_map(this->_var, term[i]))
// 			process_variable_term(term[i]);
// 		if (term[i].find("(") != std::string::npos
// 			&& is_bracket_for_function(term[i], term[i].find("(")))
// 			process_function_term(term[i]);
// 	}
// 	str = "";
// 	for (size_t i = 0; i < term.size(); i++)
// 		str += term[i];
// }

// void	Parse::print_info(void) //remove later
// {
// 	std::cout << "variable" << std::endl;
// 	if (this->_var.size() == 0)
// 	{
// 		std::cout << MAGENTA
// 			<< "there is no variable assigned yet" << BLACK << std::endl;
// 	}
// 	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
// 		it != this->_var.end(); it++)
// 	{
// 		std::cout << YELLOW << it->first << BLACK << std::endl;
// 		std::cout << it->second;
// 		std::cout << std::endl
// 			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
// 	}
// 	std::cout << "=============================================================" << std::endl;
// 	std::cout << "function" << std::endl;
// 	if (this->_func.size() == 0)
// 	{
// 		std::cout << MAGENTA
// 			<< "there is no function assigned yet" << BLACK << std::endl;
// 	}
// 	for (std::map<std::string, std::string>::iterator it = this->_func.begin();
// 		it != this->_func.end(); it++)
// 	{
// 		std::cout << YELLOW << it->first << BLACK << std::endl;
// 		std::cout << it->second;
// 		std::cout << std::endl
// 			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
// 	}
// }

// void	Parse::print_str(std::string str) //remove later
// {
// 	for (size_t i = 0; i < str.length(); i++)
// 	{
// 		if (is_key_of_map(this->_operation, str[i]))
// 			std::cout << this->_operation[str[i]];
// 		else
// 			std::cout << str[i];
// 	}
// }

std::string	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return (str);

	InputConvertor	convertor(str);
	str = convertor.convert(str);

	SyntaxChecker	syntax(str);
	str = syntax.check(str);

	// print_info();//remove later
	// std::cout << "str before converting: ";//
	// print_str(str);//
	// std::cout << std::endl;//

	// std::string	left_str = str.substr(0, str.find("="));
	// std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	// convert_val_func(left_str);
	// convert_val_func(right_str);
	// //calculate power
	// str = left_str + "=" + right_str;

	// std::cout << "str after converting: ";//remove later
	// print_str(str);//
	// std::cout << std::endl;//
	return (str);
}
