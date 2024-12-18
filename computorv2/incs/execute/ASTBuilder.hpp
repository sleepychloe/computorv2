/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:39:28 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 15:19:06 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILDER_HPP
# define AST_BUILDER_HPP

#include <string>
#include <memory>
#include <variant>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include "./ExecuteError.hpp"
#include "./ASTNode.hpp"
#include "../../matrix/incs/Complex.hpp"
#include "../../matrix/incs/Vector.hpp"
#include "../matrix/incs/Matrix.hpp"
#include "../Utils.hpp"
#include "../Color.hpp"

using	ValueSet = std::variant<float,
				Complex<float>,
				Matrix<float>,
				Matrix<Complex<float>>,
				Vector<float>,
				Vector<Complex<float>>>;

class ASTBuilder
{
public:
	ASTBuilder();
	ASTBuilder(const ASTBuilder& builder);
	ASTBuilder& operator=(const ASTBuilder& builder);
	~ASTBuilder();

	std::unique_ptr<ASTNode>	build(std::string str);

private:
	void				throw_err_msg(std::string function, std::string err_msg, size_t term);

	int				handle_brackets(std::stack<std::unique_ptr<ASTNode>> &stack_node,
							std::string str, size_t i);

	int				precedence(std::string op);
	void				build_subtree(std::stack<std::unique_ptr<ASTNode>> &stack_node,
							std::stack<std::string> &stack_op);
	int				handle_operator(std::stack<std::unique_ptr<ASTNode>> &stack_node,
							std::stack<std::string> &stack_op,
							char c, size_t i);

	std::string			get_term(std::string str, size_t &i);

	void				build_tree(std::string str, std::unique_ptr<ASTNode> &node);

	void				visit_ast(ASTNode *node);

	std::string				_str;

	std::unordered_set<char>		_set_number; // '0' to '9', '.', 'i'
	std::unordered_set<char>		_set_vector_matrix; // '[', ']', ',', ';'
	std::unordered_set<char>		_set_operator; // '+', '-', '*', '/', '%'
	std::unordered_map<int, std::string>	_operator; // {OP_OPERATOR, "operator"}

	ExecuteError::s_error			_struct_error;
};

# endif
