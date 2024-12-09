/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:46:22 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/09 15:49:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/AST.hpp"

AST::AST(): _left_root(nullptr), _right_root(nullptr), _err_msg("")
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i'};
	this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};
}

AST::AST(const AST& ast)
{
	*this = ast;
}

AST& AST::operator=(const AST& ast)
{
	if (this == &ast)
		return (*this);
	this->_set_alphabet = ast._set_alphabet;
	this->_set_number = ast._set_number;
	this->_operation = ast._operation;
	this->_var = ast._var;
	this->_func = ast._func;
	this->_left_root = (this->_left_root == nullptr) ? nullptr : std::make_unique<ASTNode>(*ast._left_root);
	this->_right_root = (this->_right_root == nullptr) ? nullptr : std::make_unique<ASTNode>(*ast._right_root);
	this->_err_msg = ast._err_msg;
	return (*this);
}

AST::~AST()
{
}

void	AST::print_variant_value(ValueSet value)
{
	if (std::get_if<float>(&value))
		std::cout << *std::get_if<float>(&value);
	else if (std::get_if<Complex<float>>(&value))
		std::cout << *std::get_if<Complex<float>>(&value);
	else if (std::get_if<Matrix<float>>(&value))
		std::cout << *std::get_if<Matrix<float>>(&value);
	else if (std::get_if<Matrix<Complex<float>>>(&value))
		std::cout << *std::get_if<Matrix<Complex<float>>>(&value);
	else if (std::get_if<Vector<float>>(&value))
		std::cout << *std::get_if<Vector<float>>(&value);
	else if (std::get_if<Vector<Complex<float>>>(&value))
		std::cout << *std::get_if<Vector<Complex<float>>>(&value);
	else
	{
		this->_err_msg = "detected unknown type while printing variable list";
		this->_err_msg += ": std::map<std::string, V>";
		this->_err_msg += "(V = std::variant<float, Complex<float>, Matrix<float>, Matrix<Complex<float>>,";
		this->_err_msg += "Vector<float>, Vector<Complex<float>>>)";
		throw (this->_err_msg);
	}
}

void	AST::start_syntax_checking(std::string &str)
{
	check_str(str);
}

int	AST::check_keyword(std::string str)
{
	if (str == "var" || str == "VAR"
		|| str == "vriable" || str == "VARIABLE")
	{
		// //test
		// this->_var["a"] = 1.1f;
		// this->_var["b"] = Complex<float>(1, 1);
		// this->_var["c"] = Matrix<float>({{1.1, 2.2}, {3.3, 4.4}});
		// this->_var["d"] = Matrix<Complex<float>>({{Complex<float>(1, 1), Complex<float>(2, 2)},
		// 					{Complex<float>(3, 3), Complex<float>(4, 4)}});
		// this->_var["e"] = Vector<float>({1.1, 2.2, 3.3});
		// this->_var["f"] = Vector<Complex<float>>({Complex<float>(1, 1), Complex<float>(2, 2), Complex<float>(3, 3)});

		std::cout << MAGENTA << "╔═════════════════════╗" << BLACK << std::endl;
		std::cout << MAGENTA << "║    VARIABLE LIST    ║" << BLACK << std::endl;
		std::cout << MAGENTA << "╚═════════════════════╝" << BLACK << std::endl;
		if (this->_var.size() == 0)
		{
			std::cout << MAGENTA
				<< "there is no variable assigned yet" << BLACK << std::endl;
			return (1);
		}
		for (std::map<std::string, ValueSet>::iterator it = this->_var.begin();
			it != this->_var.end(); it++)
		{
			std::cout << YELLOW << it->first << BLACK << std::endl;
			print_variant_value(it->second);
			std::cout << std::endl
				<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
		}
		return (1);
	}
	else if (str == "func" || str == "FUNC"
		|| str == "function" || str == "function")
	{
		std::cout << MAGENTA << "╔═════════════════════╗" << BLACK << std::endl;
		std::cout << MAGENTA << "║    FUNCTION LIST    ║" << BLACK << std::endl;
		std::cout << MAGENTA << "╚═════════════════════╝" << BLACK << std::endl;
		if (this->_func.size() == 0)
		{
			std::cout << MAGENTA
				<< "there is no function assigned yet" << BLACK << std::endl;
			return (1);
		}
		for (std::map<std::string, std::string>::iterator it = this->_func.begin();
			it != this->_func.end(); it++)
		{
			std::cout << YELLOW << it->first << BLACK << std::endl;
			std::cout << it->second;
			std::cout << std::endl
				<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
		}
		return (1);
	}
	return (0);
}

int	AST::skip_round_bracket(std::string str, size_t i)
{
	std::stack<char>	stack;

	stack.push(str[i]);
	i++;
	while (i < str.length())
	{
		if (str[i] == '(')
			stack.push(str[i]);
		if (str[i] == ')')
			stack.pop();
		if (stack.empty())
			break ;
		i++;
	}
	return (i);
}

int	AST::precedence(std::string op)
{
	if (op == "+" || op == "-")
		return (1);
	if (op == "*" || op == "/" || op == "%")
		return (2);
	if (op == "**")
		return (3);
	if (op == "^")
		return (4);
	return (0);
}

void	AST::build_subtree(std::stack<std::unique_ptr<ASTNode>> &stack_node,
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

int	AST::is_part_of_function_expression(std::string str, size_t i)
{
	if (i > 0 && is_element_of_set(this->_set_alphabet, str[i - 1]))
		return (1);
	return (0);
}

int	AST::handle_brackets(std::stack<std::unique_ptr<ASTNode>> &stack_node,
				std::string str, size_t i)
{
	std::string			str_bracket;
	std::unique_ptr<ASTNode>	sub_root = nullptr;
	size_t		end;

	end = skip_round_bracket(str, i);
	str_bracket = str.substr(i + 1, end - i - 1);
	build_tree(str_bracket, sub_root);
	stack_node.push(std::move(sub_root));
	return (end + 1);
}

int	AST::handle_operator(std::stack<std::unique_ptr<ASTNode>> &stack_node,
				std::stack<std::string> &stack_op, char c, size_t i)
{
	std::string	op = this->_operation[c];

	if (!precedence(op))
	{
		this->_err_msg = "cannot set precedence of operation";
		throw (this->_err_msg);
	}
	while (!stack_op.empty() && precedence(stack_op.top()) >= precedence(op))
		build_subtree(stack_node, stack_op);
	stack_op.push(op);
	std::cout << "op: " << op << std::endl;//
	return (i + 1);
}

std::string	AST::get_term(std::string str, size_t &i)
{
	size_t		start = i;
	std::string	term;

	while (!(str[i] == '\0' || str[i] == '?'
		|| (str[i] == '(' && !is_part_of_function_expression(str, i))
		|| is_key_of_map(this->_operation, str[i])))
		i++;
	term = str.substr(start, i - start);
	if (term == "" || term[0] == '\0' || term == "?")
		return ("");
	std::cout << "term: " << term << std::endl;//
	return (term);
}

int	AST::is_number_str(std::string str)
{
	size_t	i = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;
	while (i < str.length())
	{
		if (!is_element_of_set(this->_set_number, str[i]))
			return (0);
		i++;
	}
	if (str.find("i") != std::string::npos)
	{
		if (str.find("i", str.find("i", str.find("i")) + 1) != std::string::npos)
			return (0);
	}
	return (1);
}

int	AST::is_alpha_str(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!is_element_of_set(this->_set_alphabet, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	AST::is_valid_variable_name(std::string term)
{
	if (term == "i")
	{
		this->_err_msg = "variable name cannot not be \"i\"";
		return (0);
	}

	size_t	i = 0;

	if (term[i] == '+' || term[i] == '-')
		i++;
	while (is_element_of_set(this->_set_number, term[i]))
		i++;
	if (!is_alpha_str(term.substr(i, std::string::npos)))
	{
		this->_err_msg = "variable name should be consisted with letter(s)1";
		return (0);
	}
	return (1);
}

std::string	AST::is_element_of_func(std::string function_name)
{
	std::string	value = "";

	if (this->_func.find(function_name) != this->_func.end())
		value = this->_func[function_name];
	return (value);
}

int	AST::is_valid_function_name(std::string term)
{
	if (check_round_brackets(term) != 1)
	{
		this->_err_msg = "invalid function name: brackets";
		return (0);
	}

	std::string	function_name = term.substr(0, term.find("("));
	std::string	variable = term.substr(term.find("(") + 1, term.length() - term.find("(") - 2);

	std::cout << "funtion name: " << function_name << std::endl;//
	std::cout << "variable: " << variable << std::endl;//

	// /* check function name */
	if (!is_alpha_str(function_name))
	{
		this->_err_msg = "function name should be consisted with letter(s)";
		return (0);
	}
	// /* check variable */
	if (is_number_str(variable) && variable != "i")
	{
		if (is_element_of_func(function_name) == "")
		{
			this->_err_msg = "function does not exists, cannot assign";
			return (0);
		}
	}
	else
	{
		if (!is_valid_variable_name(variable))
			return (0);
	}
	return (1);
}

NodeType	AST::set_type_of_term(std::string term)
{
	if (term.find("[") != std::string::npos
			&& term.find("]") != std::string::npos)
	{
		if (term.find("[", 1) != std::string::npos)
			return (NodeType::TERM_MATRIX);
		else
			return (NodeType::TERM_VECTOR);
	}
	if (is_number_str(term))
		return (NodeType::TERM_NUMBER);
	if (is_valid_variable_name(term))
		return (NodeType::TERM_VARIABLE);
	if (is_valid_function_name(term))
		return (NodeType::TERM_FUNCTION);
	return (NodeType::TERM_INVALID);
}

NodeType	AST::check_term(std::string &term)
{
	NodeType	type;

	type = set_type_of_term(term);
	if (type == NodeType::TERM_INVALID)
	{
		if (this->_err_msg == "")
			this->_err_msg = "invalid term";
		throw (this->_err_msg);
	}
	if (type == NodeType::TERM_NUMBER)
		std::cout << "type: number" << std::endl;//
	else if (type == NodeType::TERM_VARIABLE)
		std::cout << "type: variable" << std::endl;//
	else if (type == NodeType::TERM_FUNCTION)
		std::cout << "type: function" << std::endl;//
	else if (type == NodeType::TERM_VECTOR)
		std::cout << "type: vector" << std::endl;//
	else if (type == NodeType::TERM_MATRIX)
		std::cout << "type: matrix" << std::endl;//
	return (type);
}

void	AST::build_tree(std::string str, std::unique_ptr<ASTNode> &node)
{
	std::stack<std::unique_ptr<ASTNode>>	stack_node;
	std::stack<std::string>			stack_op;
	std::string	term;
	NodeType	type;
	size_t		i = 0;

	while (i < str.length())
	{
		if (str[i] == '(' && !is_part_of_function_expression(str, i))
			i = handle_brackets(stack_node, str, i);

		if (is_key_of_map(this->_operation, str[i]))
			i = handle_operator(stack_node, stack_op, str[i], i);
		else
		{
			term = get_term(str, i);
			if (term == "")
				break ;
			type = check_term(term);
			stack_node.push(std::make_unique<ASTNode>(ASTNode(term, type)));
		}
	}
	while (!stack_op.empty())
		build_subtree(stack_node, stack_op);

	if (!stack_node.empty())
		node = std::move(stack_node.top());
}

void	AST::visit_ast(ASTNode *node)
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

int	AST::check_str(std::string str)
{
	std::string		left_str = str.substr(0, str.find("="));
	std::string		right_str = str.substr(str.find("=") + 1, std::string::npos);

	this->_left_root = nullptr;
	this->_right_root = nullptr;

	build_tree(left_str, this->_left_root);
	build_tree(right_str, this->_right_root);

	// std::cout << "left AST----------" << std::endl;
	// visit_ast(this->_left_root.get());
	// std::cout << std::endl << "right AST----------" << std::endl;
	// visit_ast(this->_right_root.get());
	return (1);
}

//--------------------------------------------------------------------------------
// ValueSet	AST::convert_to_value_set(std::string term_str)
// {
// 	ValueSet	res;

// 	if (term_str[term_str.length() - 1] != 'i')
// 		res.emplace<float>(atof(term_str.c_str()));
// 	else
// 	{
// 		std::string	imag = term_str.substr(0, term_str.length() - 1);

// 		if (term_str == "")
// 			res.emplace<Complex<float>>(0, 1);
// 		else
// 			res.emplace<Complex<float>>(0, atof(imag.c_str()));
// 	}
// 	return (res);
// }

// // Complex<float>	AST::string_to_complex(std::string nb_str)
// // {
	
// // 	// return ();
// // }

// void	AST::set_type_vector(std::string &term_str, ValueSet &term_value)
// {
// 	std::vector<std::string>	vector = split(term_str, ',');

// 	for (size_t i = 0; i < vector.size(); i++)
// 	{
// 		if (!is_number_str(vector[i]))
// 		{
// 			this->_err_msg = "invalid term: vector";
// 			throw (this->_err_msg);
// 		}
// 		//string_to_complex()
// 		(void)term_value;
// 	}
// }

// float AST::calculate_ast(ASTNode* node)
// {
//     if (!node)
//         throw std::runtime_error("Invalid node in calculation");

//     // If it's a TERM node (operand), convert its value_str to a float
//     if (node->get_type() == NodeType::TERM) {
//         try {
//             return std::stof(node->get_value_str());
//         } catch (...) {
//             throw std::runtime_error("Invalid term value: " + node->get_value_str());
//         }
//     }

//     // If it's an OPERATOR node, evaluate left and right children
//     float left_value = calculate_ast(node->get_left());
//     float right_value = calculate_ast(node->get_right());

//     // Apply the operation based on value_str
//     std::string op = node->get_value_str();
//     if (op == "+")
//         return left_value + right_value;
//     else if (op == "-")
//         return left_value - right_value;
//     else if (op == "*")
//         return left_value * right_value;
//     else if (op == "/") {
//         if (std::fabs(right_value) < 1e-6) // Check for near-zero values
//             throw std::runtime_error("Division by zero");
//         return left_value / right_value;
//     } else if (op == "**")
//         return std::pow(left_value, right_value);
//     else
//         throw std::runtime_error("Unsupported operation: " + op);
// }