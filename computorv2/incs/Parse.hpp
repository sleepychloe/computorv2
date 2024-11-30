/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/30 23:20:58 by yhwang           ###   ########.fr       */
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
#include <variant>
#include <iterator>

using V = std::variant<float, Complex<float>, Matrix<float>, Matrix<Complex<float>>, Vector<float>, Vector<Complex<float>>>;

# define TYPE_VARIABLE		0
# define TYPE_FUNCTION		1
# define TYPE_CALCULATE		2

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	void				parse_start(std::string &str);

private:
	int				check_keyword(std::string str);

	int				is_equation_form(std::string str);
	int				check_float_point(std::string str);
	int				check_number(std::string str);
	void				remove_space(std::string &str);

	// void				check_type(std::string &str);
	int				check_str(std::string &str);

	std::map<std::string, V>		_var;
	std::map<std::string, V>		_func;
	std::string 				_err_msg;
};

#endif
