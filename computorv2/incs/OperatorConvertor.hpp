/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorConvertor.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:59:42 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:09:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_CONVERTOR_HPP
# define OPERATOR_CONVERTOR_HPP

#include <string>
#include "./ParseError.hpp"
#include "./VectorMatrixChecker.hpp"
#include "./Define.hpp"
#include "./Utils.hpp"

class OperatorConvertor
{
public:
	OperatorConvertor(std::string str);
	OperatorConvertor(const OperatorConvertor& convertor);
	OperatorConvertor& operator=(const OperatorConvertor& convertor);
	~OperatorConvertor();

	std::string			convert(std::string str);

private:
	OperatorConvertor();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				skip_vector_matrix(std::string str,
							std::string &new_str, size_t i, size_t pos);
	int				is_bracket_for_function(std::string str, size_t bracket_open_idx);
	int				skip_function(std::string str, std::string &new_str, size_t i);
	int				skip_vector_matrix_function(std::string str,
							std::string &new_str, size_t i, size_t pos);
	char				do_convert(std::string str, size_t &i);

	std::string			convert_operator(std::string str);

	std::string			_str;

	std::unordered_set<char>	_set_alphabet; // 'a' to 'z'
	std::unordered_set<char>	_set_number;
	std::unordered_set<char>	_set_operator; // '+', '-', '*', '/', '%', '^'
	std::unordered_set<char>	_set_other; // '(', ')','^', '=', '?'

	Error::t_error			_struct_error;
};

#endif
