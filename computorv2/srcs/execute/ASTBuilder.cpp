/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTBuilder.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:39:50 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 15:44:24 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute/ASTBuilder.hpp"

ASTBuilder::ASTBuilder()
{
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i'};
	this->_set_vector_matrix = { '[', ']', ',', ';'};
	this->_set_operator = {'+', '-', '*', '/', '%'};
	this->_operator = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
}

ASTBuilder::ASTBuilder(const ASTBuilder& builder)
{
	*this = builder;
}

ASTBuilder& ASTBuilder::operator=(const ASTBuilder& builder)
{
	if (this == &builder)
		return (*this);
	//
	return (*this);
}

ASTBuilder::~ASTBuilder()
{
}

std::unique_ptr<ASTNode>	ASTBuilder::build(std::string str)
{
	this->_str = str;

	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);
std::cout << "str:" << str << std::endl;
std::cout << "left: " << left_str << std::endl;
std::cout << "right: " << right_str << std::endl;
std::cout << "--------------------" << std::endl;


	size_t	i = 0;
	size_t	base;
	size_t	power;
	size_t	bracket;
	while (i < str.length())
	{
		bracket = 0;
		if (str[i] == '^')
		{
			std::cout << "FOUND CARET" << std::endl;
			base = i - 1;
			if (str[base] != ')')
			{
				std::cout << "base: ";
				while (base && !is_key_of_map(this->_operator, str[base]))
					base--;
				std::cout << str.substr(base, i - base) << std::endl;
			}
			else
			{
				std::cout << "base: ";
				while (base &&  str[base] != '(')
				{
					base--;
					if (str[base] == ')')
						bracket++;
				}
				while (bracket && base)
				{
					base--;
					if (str[base] == '(')
						bracket--;
				}
				std::cout << str.substr(base, i - base) << std::endl;
			}
			std::cout << "power: ";
			power = i + 1;
			while (str[power] != is_key_of_map(this->_operator, str[power])
				&& str[power] != '=' && str[power] != '\0')
				power++;
			power --;
			std::cout << str.substr(i + 1, power - i) << std::endl;
			i = power + 1;
		}
		i++;
	}


	// std::unique_ptr<ASTNode>	left_root = nullptr;
	// std::unique_ptr<ASTNode>	right_root = nullptr;

	// build_tree(left_str, left_root);
	// // build_tree(right_str, right_root);

	// visit_ast(left_root.get());
	// // visit_ast(right_root.get());
	return (nullptr);
}

void	ASTBuilder::throw_err_msg(std::string function, std::string err_msg, size_t term)
{
	std::unordered_map<int, std::string>	op = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
	std::string	str_copy = this->_str;

	this->_str = "";
	for (size_t i = 0; i < str_copy.length(); i ++)
	{
		if (is_key_of_map(op, str_copy[i]))
			this->_str += op[str_copy[i]];
		else
			this->_str += str_copy[i];
	}
std::cout << "str_copy: " << str_copy << std::endl;//
std::cout << "this->_str: " << this->_str << std::endl;//
	this->_struct_error.file_name = "ASTBuilder.cpp";
	this->_struct_error.cat = "";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	// this->_struct_error.pos = pos;
	(void)term;

	// this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	// this->_struct_error.pos_str += "\t\t  ";
	// this->_struct_error.pos_str += RED;
	// if (pos != std::string::npos && pos >= 1)
	// {
	// 	for (size_t i = 0; i < pos - 1; i++)
	// 		this->_struct_error.pos_str += "~";
	// }
	// this->_struct_error.pos_str += "^";
	// this->_struct_error.pos_str += BLACK;
	throw (ExecuteError::ExecuteException(this->_struct_error));
}

int	ASTBuilder::handle_brackets(std::stack<std::unique_ptr<ASTNode>> &stack_node,
							std::string str, size_t i)
{
	std::string			str_bracket;
	std::unique_ptr<ASTNode>	sub_root = nullptr;
	size_t		end;

	end = skip_bracket(ROUND_BRACKET, str, i);
	str_bracket = str.substr(i + 1, end - i - 1);
	build_tree(str_bracket, sub_root);
	stack_node.push(std::move(sub_root));
	return (end + 1);
}

int	ASTBuilder::precedence(std::string op)
{
	if (op == "+" || op == "-")
		return (1);
	if (op == "*" || op == "/" || op == "%")
		return (2);
	if (op == "**")
		return (3);
	// if (op == "^")
	// 	return (4);
	return (0);
}

void	ASTBuilder::build_subtree(std::stack<std::unique_ptr<ASTNode>> &stack_node,
				std::stack<std::string> &stack_op)
{
	std::string	op = stack_op.top();
	stack_op.pop();

	std::unique_ptr<ASTNode>	right = std::move(stack_node.top());
	stack_node.pop();
	std::unique_ptr<ASTNode>	left = std::move(stack_node.top());
	stack_node.pop();

	stack_node.push(std::make_unique<ASTNode>(op, std::move(left), std::move(right)));
}

int	ASTBuilder::handle_operator(std::stack<std::unique_ptr<ASTNode>> &stack_node,
				std::stack<std::string> &stack_op, char c, size_t i)
{
	std::string	op = this->_operator[c];

	if (!precedence(op))
		std::cout << "here" << std::endl;
	while (!stack_op.empty() && precedence(stack_op.top()) >= precedence(op))
		build_subtree(stack_node, stack_op);
	stack_op.push(op);
	std::cout << "op: " << op << std::endl;//
	return (i + 1);
}

std::string	ASTBuilder::get_term(std::string str, size_t &i)
{
	size_t		start = i;
	std::string	term;

	while (!(str[i] == '\0' || str[i] == '?'
		|| (str[i] == '(' && !is_bracket_for_function(str, i))
		|| is_key_of_map(this->_operator, str[i])))
		i++;
	term = str.substr(start, i - start);
	if (term == "" || term[0] == '\0' || term == "?")
		return ("");
	std::cout << "term: " << term << std::endl;//
	return (term);
}

void	ASTBuilder::build_tree(std::string str, std::unique_ptr<ASTNode> &node)
{
	std::stack<std::unique_ptr<ASTNode>>	stack_node;
	std::stack<std::string>			stack_op;
	std::string	term;
	NodeType	type;
	size_t		i = 0;

	while (i < str.length())
	{
		if (str[i] == '(' && !is_bracket_for_function(str, i))
			i = handle_brackets(stack_node, str, i);

		if (is_key_of_map(this->_operator, str[i]))
			i = handle_operator(stack_node, stack_op, str[i], i);
		else
		{
			term = get_term(str, i);
			if (term == "")
				break ;
			// type = check_term(term);
			type = NodeType::TERM_NUMBER;//temp
			stack_node.push(std::make_unique<ASTNode>(ASTNode(term, type)));
		}
	}
	while (!stack_op.empty())
		build_subtree(stack_node, stack_op);

	if (!stack_node.empty())
		node = std::move(stack_node.top());
}

void	ASTBuilder::visit_ast(ASTNode *node)
{
	if (node == nullptr)
		return ;

	visit_ast(node->get_left());
	visit_ast(node->get_right());

	//set ValueSet type value in this function
	if (node->get_type() != NodeType::OPERATOR)
		std::cout << "TERM: ";
	else
		std::cout << "OP: ";
	
	std::cout << node->get_value_str() << std::endl;
}
