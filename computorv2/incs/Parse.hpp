/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/14 01:43:10 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <exception>
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

# define LEFT_STR		0
# define RIGHT_STR		1

typedef struct s_error
{
	std::string	cat;
	std::string	function;
	std::string	msg;
	size_t		pos;
	std::string	pos_str;
}	t_error;

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	class ParseException: public std::exception
	{
	public:
		ParseException(const t_error &error): _error(error) {}

		virtual const char* what() const throw()
		{
			std::ostringstream	oss;
		
			oss << "Parse.cpp: " << this->_error.function << std::endl
				<< RED << "error: " << this->_error.cat << ": "
				<< YELLOW << this->_error.msg << ": " << BLACK
				<< "at position " << this->_error.pos << std::endl
				<< this->_error.pos_str << std::endl;
			this->_what_msg = oss.str();
			return (_what_msg.c_str());
		}

	private:
		t_error			_error;
		mutable std::string	_what_msg;
	};

	void				set_var(std::map<std::string, std::string> var);
	void				set_func(std::map<std::string, std::string> func);
	std::string			parse_start(std::string &str);

private:
	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				check_keyword(std::string str);

	int				check_equal_sign(std::string str);
	int				check_each_term(std::string str);
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
	int				check_caret_base(std::string str, size_t i, size_t pos);
	int				skip_caret_power(std::string str, size_t i);
	int				check_caret_power(std::string str, size_t &i, size_t pos);
	int				check_caret(int str_type, std::string str);
	int				check_brackets(int str_type, int bracket_type, std::string str);

	void				check_vector_str(int type, std::string str, size_t pos);
	void				check_vector_element(int type, char c, size_t pos);
	int				check_vector_form(int type, std::string str, size_t pos);

	void				check_matrix_str(std::string str, size_t pos);
	void				check_matrix_row(std::string row, size_t pos);
	void				check_matrix_column(std::string row, size_t i, int &col_size, size_t pos);
	int				check_matrix_form(std::string str, size_t pos);
	int				skip_vector_matrix(std::string str,
							std::string &new_str, size_t i, size_t pos);

	int				is_bracket_for_function(std::string str, size_t bracket_open_idx);
	int				skip_function(std::string str, std::string &new_str, size_t i);
	int				skip_vector_matrix_function(std::string str,
							std::string &new_str, size_t i, size_t pos);
	char				do_convert(std::string str, size_t &i);
	void				convert_operator(int str_type, std::string &str);

	int				check_first_sign(std::string str, size_t pos);
	int				check_operator_bracket_str(std::string str, size_t i, size_t pos);
	int				check_operator(int str_type, std::string str);

	int				check_operator_near_brackets(int str_type, std::string str);

	int				check_syntax(std::string &str);
	std::string			check_str(std::string &str);

	std::string				_str;

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z', 'A' to 'Z'
	std::unordered_set<char>		_set_number; // '0' to '9', '.', 'i', 'I'
	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>		_set_operation; // '+', '-', '*', '/', '%', '^'
	std::unordered_set<char>		_set_other; // '(', ')','^', '=', '?'
	std::unordered_set<char>		_set_space; // ' ', '\t'
	std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;

	t_error					_struct_error;
};

#endif
