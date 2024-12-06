/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:42:13 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/06 22:03:33 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_NODE_HPP

#include <string>
#include <memory>
#include <utility>

enum class NodeType
{
	OPERATOR = 0,
	TERM = 1,

	TERM_INVALID,
	TERM_NUMBER,
	TERM_VARIABLE,
	TERM_FUNCTION,
	TERM_VECTOR,
	TERM_MATRIX
};

class ASTNode
{
public:
	/* term */
	ASTNode(std::string term); // term
	/* operator */
	ASTNode(std::string op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
	ASTNode(const ASTNode& astnode);
	ASTNode& operator=(const ASTNode& astnode);
	~ASTNode();

	NodeType			_type;
	std::string			_value;
	std::unique_ptr<ASTNode>	_left;
	std::unique_ptr<ASTNode>	_right;

private:
	ASTNode();
};

#endif
