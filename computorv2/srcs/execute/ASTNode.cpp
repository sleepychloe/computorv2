/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:42:48 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 15:29:35 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute/ASTNode.hpp"

ASTNode::ASTNode()
{
}

ASTNode::ASTNode(std::string term, NodeType type): _type(type), _value_str(term), _value(0.0f),
				_left(nullptr), _right(nullptr)
{
}

ASTNode::ASTNode(std::string op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
				: _type(NodeType::OPERATOR), _value_str(op), _value(0.0f),
				_left(std::move(left)), _right(std::move(right))
{
}

ASTNode::ASTNode(const ASTNode& astnode)
{
	*this = astnode;
}

ASTNode& ASTNode::operator=(const ASTNode& astnode)
{
	if (this == &astnode)
		return (*this);
	this->_type = astnode._type;
	this->_value_str = astnode._value_str;
	this->_value = astnode._value;
	this->_left = (astnode._left == nullptr) ? nullptr : std::make_unique<ASTNode>(*astnode._left);
	this->_right = (astnode._right == nullptr) ? nullptr : std::make_unique<ASTNode>(*astnode._right);
	return (*this);
}

ASTNode::~ASTNode()
{
}

NodeType	ASTNode::get_type(void) const
{
	return (this->_type);
}

std::string	ASTNode::get_value_str(void) const
{
	return (this->_value_str);
}

ValueSet	ASTNode::get_value(void) const
{
	return (this->_value);
}

ASTNode*	ASTNode::get_left(void) const
{
	return (this->_left.get());
}

ASTNode*	 ASTNode::get_right(void) const
{
	return (this->_right.get());
}

void	ASTNode::set_type(NodeType type)
{
	this->_type = type;
}

void	ASTNode::set_value(ValueSet value)
{
	this->_value = value;
}

void	ASTNode::set_left(std::unique_ptr<ASTNode> left)
{
	this->_left = std::move(left);
}

void	ASTNode::set_right(std::unique_ptr<ASTNode> right)
{
	this->_right = std::move(right);
}
