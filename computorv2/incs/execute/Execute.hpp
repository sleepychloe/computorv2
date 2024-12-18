/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:27:42 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 20:53:35 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_HPP
# define EXECUTE_HPP

#include <map>

#include "./ExecuteError.hpp"
#include "./ExponentSimplifier.hpp"
#include "./ASTNode.hpp"
#include "./ASTBuilder.hpp"
#include "../Utils.hpp"
#include "../Define.hpp"
#include "../Color.hpp"
#include "../../matrix/incs/Complex.hpp"
#include "../../matrix/incs/Vector.hpp"
#include "../matrix/incs/Matrix.hpp"

class Execute
{
public:
	Execute();
	Execute(const Execute& execute);
	Execute& operator=(const Execute& execute);
	~Execute();

	std::map<std::string, std::string>	get_var(void) const;
	std::map<std::string, std::string>	get_func(void) const;

	void					execute(std::string str);

private:
	std::string				_str;

	std::map<std::string, std::string>	_var;
	std::map<std::string, std::string>	_func;

	std::unique_ptr<ASTNode>		_root;
};

# endif
