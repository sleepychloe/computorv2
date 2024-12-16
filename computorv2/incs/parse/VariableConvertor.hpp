/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VariableConvertor.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:12 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 16:17:02 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_CONVERTOR_HPP
# define VARIABLE_CONVERTOR_HPP

#include <string>
#include <map>
#include <vector>
#include "../Define.hpp"
#include "../Utils.hpp"

class VariableConvertor
{
public:
	VariableConvertor(std::string str, std::map<std::string,
				std::string> var, std::map<std::string, std::string> func);
	VariableConvertor(const VariableConvertor& convertor);
	VariableConvertor& operator=(const VariableConvertor& convertor);
	~VariableConvertor();

	std::string	convert(std::string str);

private:
	VariableConvertor();

	std::vector<std::string>	split_term(std::string str);
	void				process_variable_term(std::string &term);
	std::string			convert_func_variable(std::string term,
							std::string var_key, std::string var_value);
	std::string			convert_func_name(std::string term,
							std::string func_key, std::string func_value);
	void				process_function_term(std::string &term);
	std::string			convert_val_func(std::string &str);

	std::string				_str;

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z'
	std::unordered_map<int, std::string>	_operator; // {OP_OPERATOR, "operator"}

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;
};

#endif
