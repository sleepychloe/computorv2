/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:12:06 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <exception>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <stack>
#include <cctype>

#include "./ParseError.hpp"
#include "./InputConvertor.hpp"
#include "./SyntaxChecker.hpp"

#include "./Utils.hpp"
#include "./Define.hpp"
#include "./Color.hpp"

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	void				set_var(std::map<std::string, std::string> var);
	void				set_func(std::map<std::string, std::string> func);
	std::string			parse_start(std::string &str);

private:
	int				check_keyword(std::string str);


	// int				check_syntax(std::string &str);

	// std::vector<std::string>	split_term(std::string str);
	// void				process_variable_term(std::string &term);
	// std::string			convert_func_variable(std::string term,
	// 						std::string var_key, std::string var_value);
	// std::string			convert_func_name(std::string term,
	// 						std::string func_key, std::string func_value);
	// void				process_function_term(std::string &term);
	// void				convert_val_func(std::string &str);

	// void				print_info(void); //remove later
	// void				print_str(std::string str); //remove later
	std::string			check_str(std::string &str);

	std::string				_str;

	// std::unordered_set<char>		_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	// std::unordered_set<char>		_set_number; // '0' to '9', '.', 'i', 'I'
	// std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	// std::unordered_set<char>		_set_operation; // '+', '-', '*', '/', '%', '^'
	// std::unordered_set<char>		_set_other; // '(', ')','^', '=', '?'
	// std::unordered_set<char>		_set_space; // ' ', '\t'
	// std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;

	// Error::t_error				_struct_error;
};

#endif
