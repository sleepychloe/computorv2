/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:42:13 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/07 19:42:54 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_NODE_HPP

#include <string>
#include <memory>
#include <utility>
#include <variant>
#include "../matrix/incs/Complex.hpp"
#include "../matrix/incs/Vector.hpp"
#include "../matrix/incs/Matrix.hpp"

using	ValueSet = std::variant<float,
				Complex<float>,
				Matrix<float>,
				Matrix<Complex<float>>,
				Vector<float>,
				Vector<Complex<float>>>;

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
	ASTNode(std::string term);
	ASTNode(std::string op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
	ASTNode(const ASTNode& astnode);
	ASTNode& operator=(const ASTNode& astnode);
	~ASTNode();

	NodeType			get_type(void) const;
	std::string			get_value_str(void) const;
	ValueSet			get_value(void) const;
	ASTNode*			get_left(void) const;
	ASTNode*			get_right(void) const;

	void				set_type(NodeType type);
	void				set_value(ValueSet value);
	void				set_left(std::unique_ptr<ASTNode> left);
	void				set_right(std::unique_ptr<ASTNode> right);

private:
	ASTNode();

	NodeType			_type;
	std::string			_value_str;
	ValueSet			_value;
	std::unique_ptr<ASTNode>	_left;
	std::unique_ptr<ASTNode>	_right;
};

#endif
