/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxChecker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:55:43 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:13:40 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECKER_HPP
# define SYNTAX_CHECKER_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "./ParseError.hpp"
#include "./OperatorConvertor.hpp"
#include "./OperatorChecker.hpp"
#include "./Define.hpp"
#include "./Utils.hpp"

class SyntaxChecker
{
public:
	SyntaxChecker(std::string str);
	SyntaxChecker(const SyntaxChecker& checker);
	SyntaxChecker &operator=(const SyntaxChecker& checker);
	~SyntaxChecker();

	std::string			check(std::string str);

private:
	SyntaxChecker();

	int				check_each_str(int str_type, std::string str);
	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				check_question_mark(int str_type, std::string str);

	int				check_caret_base(std::string str, size_t i, size_t pos);
	int				skip_caret_power(std::string str, size_t i);
	int				check_caret_power(std::string str, size_t &i, size_t pos);
	int				check_caret(int str_type, std::string str);

	int				check_brackets(int str_type, int bracket_type, std::string str);

	std::string			_str;
 
	std::unordered_set<char>	_set_alphabet; // 'a' to 'z'
	std::unordered_set<char>	_set_operator; // '+', '-', '*', '/', '%', '^'

	Error::t_error			_struct_error;
};

# endif
