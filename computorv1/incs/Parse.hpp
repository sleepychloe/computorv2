/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/24 18:23:38 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <utility>
#include "../incs/Color.hpp"

# define TYPE_FRACTIONAL		-1
# define TYPE_HIGH_DEGREE		-2
# define TYPE_ZERO			0

# define START				0
# define END				1
# define KEEP				2

# define FRONT				0
# define BACK				1
# define BRACKET			2

class Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	virtual ~Parse();

	char				get_variable(void);
	std::vector<float>		get_reduced_form(void);
	std::vector<float>		get_degree(void);
	int				get_equation_type(void);
	int				get_flag_bonus(void);
	std::string			get_equation_str(void);

	void				parse_start(char *argv, int flag_bonus);

protected:
	// check basic elements
	int				is_equation_form(std::string str);
	int				check_variable(std::string str);
	int				check_invalid_character(std::string str);
	int				check_number(std::string str);
	void				remove_space(std::string &str);

	// check syntax
	int				check_brackets(std::string str);
	int				check_sign(std::string str);
	int				check_point(std::string str);
	int				check_caret(std::string str);
	int				check_syntax(std::string str);

	// remove brackets: term == 1
	void				remove_bracket_without_calc(std::string &str,
						std::vector<std::string> &s);
	int				find_next_bracket(std::vector<size_t> &i,
						std::vector<std::string> &s);
	void				remove_bracket_one_term(std::string &str);

	// remove brackets: term > 1
	void				check_front_str(std::vector<size_t> &i,
						std::vector<std::string> &s);
	void				apply_operation_from_front(std::string &tmp,
						std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				find_mul_dev_front_str(std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				apply_operation_from_back(std::string &tmp,
						std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				find_mul_dev_back_str(std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				get_bracket_str(std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				remove_bracket_multiple_term(std::string &str);
	int				remove_bracket(std::string &str);

	// handle terms
	std::vector<std::string>	split_term(std::string str);
	float				find_degree(std::string str);
	void				add_coefficient_of_variable(std::string &str);
	int				remove_variable(std::string &str);

	// calculate
	int				check_operation(std::string str);
	void				split_expression(std::string str,
						std::vector<float> &nb, std::vector<char> &op);
	float				calc(float nb1, float n2, char op);
	std::string			calculate(std::string str);
	std::string			float_to_string(float num);
	int				get_term(std::string str,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);

	// set equation string
	void				set_equation_type(void);
	void				make_form_ascending_order(void);
	void				set_equation_str(void);
	void				make_reduced_form(void);

	int				check_str(std::string str);

	char				_variable;
	std::vector<float>		_reduced_form;
	std::vector<float>		_degree;
	int				_max_degree;
	int				_equation_type;
	int				_flag_bonus;
	std::string			_equation_str;
	std::string			_err_msg;
};

#endif
