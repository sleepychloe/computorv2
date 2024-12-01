/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/01 13:44:10 by yhwang           ###   ########.fr       */
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
#include <variant>
#include <iterator>
#include "./Color.hpp"

using V = std::variant<float, Complex<float>, Matrix<float>, Matrix<Complex<float>>, Vector<float>, Vector<Complex<float>>>;

# define ROUND_BRACKET		0
# define SQUARE_BRACKET		1

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

	void			parse_start(std::string &str);

private:
	void			print_variant_value(V value);
	int			check_keyword(std::string str);

	int			is_equation_form(std::string str);
	int			is_element_of_set(std::unordered_set<char> set, char c);
	int			check_invalid_character(std::string str);
	int			check_float_point(std::string str);
	int			check_number(std::string str);

	void			remove_space(std::string &str);
	int			skip_square_brackets(std::string str, std::string &new_str, size_t i);
	void			convert_operator(std::string &str);

	int			check_brackets(int type, std::string str);
	id_t			check_sign(std::string str);
	int			check_syntax(std::string &str);

	int			check_str(std::string &str);

	std::unordered_set<char>		_valid_character;
	std::unordered_set<char>		_operation;

	std::map<std::string, V>		_var;
	std::map<std::string, V>		_func;
	std::string 				_err_msg;
};

#endif
