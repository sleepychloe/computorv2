/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/03 02:11:28 by yhwang           ###   ########.fr       */
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
#include <sstream>
#include "./Color.hpp"

using V = std::variant<float, Complex<float>, Matrix<float>, Matrix<Complex<float>>, Vector<float>, Vector<Complex<float>>>;

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

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	void				parse_start(std::string &str);

private:
	void				print_variant_value(V value);
	int				check_keyword(std::string str);

	int				is_equation_form(std::string str);
	int				is_element_of_set(std::unordered_set<char> set, char c);
	int				check_invalid_character(std::string str);
	int				check_float_point(std::string str);
	int				check_number(std::string str);
	void				remove_space(std::string &str);

	int				check_brackets(int type, std::string str);

	std::vector<std::string>	split(std::string str, char delimeter);
	int				check_vector_form(int type, std::string str);
	int				check_matrix_form(std::string str);

	int				skip_bracket(int type, std::string str, size_t i);
	int				skip_vector_matrix(std::string str, std::string &new_str, size_t i);
	char				do_convert(std::string str, size_t &i);
	void				convert_operator(std::string &str);

	int				check_question_mark(std::string str);
	int				check_operator(std::string str);
	int				check_syntax(std::string &str);
	
	int				check_str(std::string &str);

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	std::unordered_set<char>		_set_number; // '0' to '9', '.'
	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>		_set_operation; // '+', '-', '*', '/', '%'
	std::unordered_set<char>		_set_other; // '(', ')','^', '=', '?'
	std::unordered_set<char>		_set_space; // ' ', '\t'
	std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}
	std::map<std::string, V>		_var;
	std::map<std::string, V>		_func;
	std::string 				_err_msg;
};

#endif
