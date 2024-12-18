/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 12:10:58 by yhwang           ###   ########.fr       */
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

#include "./ParseError.hpp"
#include "./InputConvertor.hpp"
#include "./SyntaxChecker.hpp"
#include "./VariableConvertor.hpp"
#include "../Utils.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

class	Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	void				set_var(std::map<std::string, std::string> var);
	void				set_func(std::map<std::string, std::string> func);
	std::string			parse(std::string &str);

private:
	void				print_var(void);
	void				print_func(void);
	int				check_keyword(std::string str);

	std::string			check_str(std::string &str);

	std::string				_str;

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;
};

#endif
