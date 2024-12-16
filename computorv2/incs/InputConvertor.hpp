/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputConvertor.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:03:09 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:09:23 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_CONVERTOR_HPP
# define INPUT_CONVERTOR_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "./ParseError.hpp"
#include "./Define.hpp"
#include "./Utils.hpp"

class InputConvertor
{
public:
	InputConvertor(std::string str);
	InputConvertor(const InputConvertor& convertor);
	InputConvertor& operator=(const InputConvertor& convertor);
	~InputConvertor();

	std::string			convert(std::string str);

private:
	InputConvertor();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				check_equal_sign(std::string str);
	int				check_each_term(std::string str);
	int				is_equation_form(std::string str);

	int				check_invalid_character(std::string str);

	int				check_float_point(std::string str);
	int				check_number(std::string str);

	void				remove_space(std::string &str);
	void				convert_to_lower_case(std::string &str);
	void				convert_to_standard_form(std::string &str);

	std::string			_str;

	std::unordered_set<char>	_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	std::unordered_set<char>	_set_number; // '0' to '9', '.', 'i', 'I'
	std::unordered_set<char>	_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>	_set_operator; // '+', '-', '*', '/', '%', '^'
	std::unordered_set<char>	_set_other; // '(', ')','^', '=', '?'
	std::unordered_set<char>	_set_space; // ' ', '\t'

	Error::t_error			_struct_error;
};

#endif
