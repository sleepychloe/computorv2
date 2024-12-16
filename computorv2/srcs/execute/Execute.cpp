/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:45:43 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 20:59:45 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute/Execute.hpp"

Execute::Execute(): _root(nullptr)
{
}

Execute::Execute(const Execute& execute)
{
	*this = execute;
}

Execute& Execute::operator=(const Execute& execute)
{
	if (this == &execute)
		return (*this);
	/* code */
	return (*this);
}

Execute::~Execute()
{
}

std::map<std::string, std::string>	Execute::get_var(void) const
{
	return (this->_var);
}

std::map<std::string, std::string>	Execute::get_func(void) const
{
	return (this->_func);
}

void	Execute::execute(std::string str)
{
	this->_str = str;
	/* 
	1. build ast(left, right seperately)
	2. term check
	*/

	//ASTBuilder
}
