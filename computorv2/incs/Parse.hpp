/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/12 11:57:59 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
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
# define OP_POWER		6 /* ^ */
# define OP_MAT_MUL		7 /* ** */

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

	int				is_equation_form(std::string str);
	int				check_invalid_character(std::string str);
	int				check_float_point(std::string str);
	int				check_number(std::string str);
	void				remove_space(std::string &str);

	void				convert_to_standard_form(std::string &str);
	
	std::vector<std::string>	split_term(std::string str);
	void				process_variable_term(std::string &term);
	std::string			convert_func_variable(std::string term,
							std::string var_key, std::string var_value);
	std::string			convert_func_name(std::string term,
							std::string func_key, std::string func_value);
	void				process_function_term(std::string &term);
	std::string			revert_term_to_str(std::vector<std::string> term);
	void				convert_val_func(std::string &str);

	int				check_question_mark(std::string str);
	int				check_caret(std::string str);
	int				check_brackets(int type, std::string str);

	int				check_vector_form(int type, std::string str);
	int				check_matrix_form(std::string str);
	int				skip_bracket(int type, std::string str, size_t i);
	int				skip_vector_matrix(std::string str, std::string &new_str, size_t i);
	char				do_convert(std::string str, size_t &i);
	int				is_bracket_for_function(std::string str, size_t bracket_open_idx);
	void				convert_operator(std::string &str);

	int				check_operator(std::string str);
	int				check_operator_round_brackets(std::string str);
	int				check_operator_square_brackets(std::string str);
	int				check_syntax(std::string &str);

	std::string			check_str(std::string &str);

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	std::unordered_set<char>		_set_number; // '0' to '9', '.', 'i', 'I'
	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>		_set_operation; // '+', '-', '*', '/', '%', '^'
	std::unordered_set<char>		_set_other; // '(', ')','^', '=', '?'
	std::unordered_set<char>		_set_space; // ' ', '\t'
	std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;

	std::string 				_err_msg;
};

#endif
