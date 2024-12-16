/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorMatrixChecker.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:13:57 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 07:46:40 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/VectorMatrixChecker.hpp"

VectorMatrixChecker::VectorMatrixChecker()
{
}

VectorMatrixChecker::VectorMatrixChecker(std::string str, size_t pos)
				:_str(str), _pos(pos)
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i', 'I'};
	this->_set_operator = {'+', '-', '*', '/', '%', '^'};
}

VectorMatrixChecker::VectorMatrixChecker(const VectorMatrixChecker& checker)
{
	*this = checker;
}

VectorMatrixChecker& VectorMatrixChecker::operator=(const VectorMatrixChecker& checker)
{
	if (this == &checker)
		return (*this);
	this->_str = checker._str;
	this->_pos = checker._pos;
	this->_set_alphabet = checker._set_alphabet;
	this->_set_number = checker._set_number;
	this->_set_operator = checker._set_operator;
	this->_struct_error = checker._struct_error;
	return (*this);
}

VectorMatrixChecker::~VectorMatrixChecker()
{
}

int	VectorMatrixChecker::vector_check(std::string str)
{
	if (check_vector_form(VECTOR, str, this->_pos))
		return (0);
	return (1);
}

int	VectorMatrixChecker::matrix_check(std::string str)
{
	if (!check_matrix_form(str, this->_pos))
		return (0);
	return (1);
}

void	VectorMatrixChecker::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "VectorMatrixChecker.cpp";
	this->_struct_error.cat = "syntax error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	this->_struct_error.pos = pos;

	this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.pos_str += "\t\t  ";
	this->_struct_error.pos_str += RED;
	if (pos != std::string::npos && pos >= 1)
	{
		for (size_t i = 0; i < pos - 1; i++)
			this->_struct_error.pos_str += "~";
	}
	this->_struct_error.pos_str += "^";
	this->_struct_error.pos_str += BLACK;
	throw (Error::ParseException(this->_struct_error));
}

void	VectorMatrixChecker::check_vector_str(int type, std::string str, size_t pos)
{
	if (str[0] == ',')
	{
		if (type == VECTOR)
			throw_err_msg("VectorMatrixChecker::check_vector_str(int type, std::string str, size_t pos)",
				"invalid verctor form: invalid use of comma(,)", pos);
		else
			throw_err_msg("VectorMatrixChecker::check_vector_str(int type, std::string str, size_t pos)",
				"invalid matrix form: invalid use of comma(,)", pos);
	}
	if (str[str.length() - 1] == ',')
	{
		if (type == VECTOR)
			throw_err_msg("VectorMatrixChecker::check_vector_str(int type, std::string str, size_t pos)",
				"invalid verctor form: invalid use of comma(,)", pos + str.length() - 1);
		else
			throw_err_msg("VectorMatrixChecker::check_vector_str(int type, std::string str, size_t pos)",
				"invalid matrix form: invalid use of comma(,)", pos + str.length() - 1);
	}
}

void	VectorMatrixChecker::check_vector_element(int type, char c, size_t pos)
{
	if (!(is_element_of_set(this->_set_alphabet, c)
		|| is_element_of_set(this->_set_number, c)
		|| is_element_of_set(this->_set_operator, c)))
	{
		if (type == VECTOR)
			throw_err_msg("VectorMatrixChecker::check_vector_element(int type, char c, size_t pos)",
				"invalid vector form: invalid character exists", pos);
		else
			throw_err_msg("VectorMatrixChecker::check_vector_element(int type, char c, size_t pos)",
				"invalid matrix form: invalid character exists", pos);
	}
}

int	VectorMatrixChecker::check_vector_form(int type, std::string str, size_t pos)
{
	std::vector<std::string>	vector;

	str = str.substr(1, str.length() - 2);
	pos++;
	check_vector_str(type, str, pos);

	vector = split(str, ',');
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == "")
		{
			if (type == VECTOR)
				throw_err_msg("VectorMatrixChecker::check_vector_form(int type, std::string str, size_t pos)",
					"invalid vector form: invalid use of comma(,)", pos);
			else
				throw_err_msg("VectorMatrixChecker::check_vector_form(int type, std::string str, size_t pos)",
					"invalid matrix form: invalid use of comma(,)", pos);
		}
		for (size_t j = 0; j < vector[i].length(); j++)
			check_vector_element(type, vector[i][j], pos + j);
		pos += vector[i].length();
		pos++;
	}
	return (vector.size());
}

void	VectorMatrixChecker::check_matrix_str(std::string str, size_t pos)
{
	if (str[0] == ';')
		throw_err_msg("VectorMatrixChecker::check_matrix_str(std::string str, size_t pos)",
			"invalid matrix form: invalid use of semi-colon(;)", pos);
	if (str[str.length() - 1] == ';')
		throw_err_msg("VectorMatrixChecker::check_matrix_str(std::string str, size_t pos)",
			"invalid matrix form: invalid use of semi-colon(;)", pos + str.length() - 1);
}

void	VectorMatrixChecker::check_matrix_row(std::string row, size_t pos)
{
	if (row[0] != '[')
		throw_err_msg("VectorMatrixChecker::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid character exists", pos);
	if (row.find("[", 1) != std::string::npos)
		throw_err_msg("VectorMatrixChecker::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid use of bracets", pos + row.find("[", 1));

	if (row[row.length() - 1] != ']')
		throw_err_msg("VectorMatrixChecker::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid character exists", pos + row.length() - 1);
	if (row.find("]") != row.length() - 1)
		throw_err_msg("VectorMatrixChecker::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid use of bracets", pos + row.find("]"));
}

void	VectorMatrixChecker::check_matrix_column(std::string row, size_t i, int &col_size, size_t pos)
{
	if (i == 0)
		col_size = check_vector_form(MATRIX, row, pos);
	else
	{
		if (col_size != check_vector_form(MATRIX, row, pos))
		{
			throw_err_msg("VectorMatrixChecker::check_matrix_column(std::string row, size_t i, size_t pos)",
				"invalid matrix form: column size of each row should be same",
				pos + row.length() - 1);
		}
	}
}

int	VectorMatrixChecker::check_matrix_form(std::string str, size_t pos)
{
	std::vector<std::string>	row;

	str = str.substr(1, str.length() - 2);
	pos++;
	check_matrix_str(str, pos);
	row = split(str, ';');

	int	col_size = 0;
	for (size_t i = 0; i < row.size();i++)
	{
		if (row[i] == "")
			throw_err_msg("VectorMatrixChecker::check_matrix_form(std::string str, size_t pos)",
					"invalid matrix form: invalid use of semi-colon(;)", pos);
		check_matrix_row(row[i], pos);
		check_matrix_column(row[i], i, col_size, pos);
		pos += row[i].length();
		pos++;
	}
	return (row.size());
}
