/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExponentSimplifier.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:34:59 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 23:59:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPONENT_SIMPLIFIER_HPP
# define EXPONENT_SIMPLIFIER_HPP

#include <iostream>//erase later
#include <string>
#include <stack>
#include "./ExecuteError.hpp"
#include "../Utils.hpp"
#include "../Color.hpp"

class ExponentSimplifier
{
public:
	ExponentSimplifier();
	ExponentSimplifier(const ExponentSimplifier& simplifier);
	ExponentSimplifier& operator=(const ExponentSimplifier& simplifier);
	~ExponentSimplifier();

	std::string	calculate(std::string str);
private:
	
	void				throw_err_msg(std::string function,
							std::string err_msg, size_t pos_start, size_t pos_end);

	std::string			get_base(std::string str, size_t i);
	std::string			check_power(std::string power, size_t i);
	std::string			get_power(std::string str, size_t &i);
	std::string			check_exponent(std::string str);

	std::string				_str;

	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_map<int, std::string>	_operator; // {OP_OPERATOR, "operator"}

	ExecuteError::t_error			_struct_error;
};

# endif
