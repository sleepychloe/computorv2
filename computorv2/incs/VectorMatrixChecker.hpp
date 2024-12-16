/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorMatrixChecker.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:05:32 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:09:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATRIX_CHECKER_HPP
# define VECTOR_MATRIX_CHECKER_HPP

#include <string>
#include "./ParseError.hpp"
#include "./OperatorConvertor.hpp"
#include "./Define.hpp"
#include "./Utils.hpp"

class VectorMatrixChecker
{
public:
	VectorMatrixChecker(std::string str, size_t pos);
	VectorMatrixChecker(const VectorMatrixChecker& checker);
	VectorMatrixChecker& operator=(const VectorMatrixChecker& checker);
	~VectorMatrixChecker();

	int				vector_check(std::string str);
	int				matrix_check(std::string str);

private:
	VectorMatrixChecker();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	void				check_vector_str(int type, std::string str, size_t pos);
	void				check_vector_element(int type, char c, size_t pos);
	int				check_vector_form(int type, std::string str, size_t pos);

	void				check_matrix_str(std::string str, size_t pos);
	void				check_matrix_row(std::string row, size_t pos);
	void				check_matrix_column(std::string row, size_t i, int &col_size, size_t pos);
	int				check_matrix_form(std::string str, size_t pos);

	std::string			_str;
	size_t				_pos;

	std::unordered_set<char>	_set_alphabet; // 'a' to 'z'
	std::unordered_set<char>	_set_number;
	std::unordered_set<char>	_set_operator; // '+', '-', '*', '/', '%', '^'

	Error::t_error			_struct_error;
};

# endif
