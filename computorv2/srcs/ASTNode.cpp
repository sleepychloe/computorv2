/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:42:48 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/06 19:43:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ASTNode.hpp"

ASTNode::ASTNode()
{
}

/* term */
ASTNode::ASTNode(std::string term): _type(NodeType::TERM), _value(std::move(term)),
					_left(nullptr), _right(nullptr)
{
}

/* operator */
ASTNode::ASTNode(std::string op, std::unique_ptr<ASTNode>left, std::unique_ptr<ASTNode>right)
				: _type(NodeType::OPERATOR), _value(op),
				_left(std::move(left)), _right(std::move(right)) 
{
}

ASTNode::ASTNode(const ASTNode &astnode)
{
	*this = astnode;
}

ASTNode& ASTNode::operator=(const ASTNode &astnode)
{
	if (this == &astnode)
		return (*this);
	this->_type = astnode._type;
	this->_value = astnode._value;
	this->_left = astnode._left ? std::make_unique<ASTNode>(*astnode._left) : nullptr;
	this->_right = astnode._right ? std::make_unique<ASTNode>(*astnode._right) : nullptr;
	return (*this);
}

ASTNode::~ASTNode()
{
}
