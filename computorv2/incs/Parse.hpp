/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/04 15:11:00 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "../matrix/incs/Complex.hpp"
#include "../matrix/incs/Vector.hpp"
#include "../matrix/incs/Matrix.hpp"

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <variant>
#include <iterator>
#include <stack>
#include <cctype>
#include "./Utils.hpp"
#include "./Color.hpp"

# define ROUND_BRACKET		0
# define SQUARE_BRACKET		1

# define OPEN			0
# define CLOSE			1

# define VECTOR			0
# define MATRIX			1

# define OP_ADD			1 /* + */
# define OP_SUB			2 /* - */
# define OP_MUL			3 /* * */
# define OP_DIV			4 /* / */
# define OP_MODULO		5 /* % */
# define OP_MAT_MUL		6 /* ** */

# define TYPE_NUMBER		1
# define TYPE_VECTOR		2
# define TYPE_MATRIX		3
# define TYPE_QUESTION_MARK	4

using	ValueSet = std::variant<float,
				Complex<float>,
				Matrix<float>,
				Matrix<Complex<float>>,
				Vector<float>,
				Vector<Complex<float>>>;
using	VectorStrIntPair = std::pair<std::vector<std::string>, std::vector<int>>;
using	TermOperatorPair = std::pair<std::vector<ValueSet>, std::vector<int>>;

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	void				parse_start(std::string &str);

private:
	void				print_variant_value(ValueSet value);
	int				check_keyword(std::string str);

	int				is_equation_form(std::string str);
	int				check_invalid_character(std::string str);
	int				check_float_point(std::string str);
	int				check_number(std::string str);
	void				remove_space(std::string &str);

	int				check_brackets(int type, std::string str);

	int				check_vector_form(int type, std::string str);
	int				check_matrix_form(std::string str);

	int				skip_bracket(int type, std::string str, size_t i);
	int				skip_vector_matrix(std::string str, std::string &new_str, size_t i);
	char				do_convert(std::string str, size_t &i);
	void				convert_operator(std::string &str);

	int				check_question_mark(std::string str);
	int				check_operator(std::string str);
	int				check_caret(std::string str);
	int				check_syntax(std::string &str);

	void				split_term(std::string str, VectorStrIntPair &term_op);

	int				is_number_str(std::string str);
	int				is_alpha_str(std::string str);

	int				is_valid_variable_name(std::string term);
	std::string			is_element_of_func(std::string function_name);
	int				is_valid_function_name(std::string term);
	int				is_valid_term(std::string &term);
	void				convert_type_number(std::string &value_str);
	int				check_value_type(std::string &value_str);
	void				convert_term(VectorStrIntPair &term_op);

	int				check_str(std::string &str);

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	std::unordered_set<char>		_set_number; // '0' to '9', '.'
	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>		_set_operation; // '+', '-', '*', '/', '%'
	std::unordered_set<char>		_set_other; // '(', ')','^', '=', '?'
	std::unordered_set<char>		_set_space; // ' ', '\t'
	std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}

	std::map<std::string, ValueSet>		_var;
	std::map<std::string, std::string>	_func;

	TermOperatorPair			_left_term_operator;
	TermOperatorPair			_right_term_operator;
	std::string 				_err_msg;
};

#endif
