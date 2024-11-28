/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/28 17:49:43 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	return (*this);
}

Parse::~Parse()
{
}
