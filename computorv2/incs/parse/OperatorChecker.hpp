/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorChecker.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:59:00 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:54:28 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_CHECKER_HPP
# define OPERATOR_CHECKER_HPP

#include <string>
#include "./ParseError.hpp"
#include "./VectorMatrixChecker.hpp"
#include "../Define.hpp"
#include "../Utils.hpp"

class OperatorChecker
{
public:
	OperatorChecker(std::string str);
	OperatorChecker(const OperatorChecker& checker);
	OperatorChecker& operator=(const OperatorChecker& checker);
	~OperatorChecker();

	int				check(std::string str);

private:
	OperatorChecker();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				check_first_sign(std::string str, size_t pos);
	int				check_operator_bracket_str(std::string str, size_t i, size_t pos);
	int				check_operator(int str_type, std::string str);

	void				check_before_open_bracket(std::string str, size_t open_idx, size_t pos);
	void				check_after_close_bracket(std::string str, size_t close_idx, size_t pos);
	int				check_for_vector_matrix(std::string &str, size_t i, size_t pos);
	int				check_for_function(std::string &str, size_t i, size_t pos);
	int				check_for_round_brackets(std::string str, size_t pos);
	int				check_operator_near_brackets(int str_type, std::string str);

	std::string				_str;

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z'
	std::unordered_map<int, std::string>	_operator; // {OP_OPERATOR, "operator"}

	Error::t_error				_struct_error;
};

#endif
