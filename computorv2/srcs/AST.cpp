/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:46:22 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/07 22:04:26 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/AST.hpp"

AST::AST(): _err_msg("")
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i'};
	this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"},
			{OP_DIV, "/"}, {OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
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

// int	AST::is_number_str(std::string str)
// {
// 	size_t	i = 0;

// 	while (i < str.length())
// 	{
// 		if (!(is_element_of_set(this->_set_number, str[i])
// 			|| str[i] == '+' || str[i] == '-' || str[i] == '^'))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	AST::is_alpha_str(std::string str)
// {
// 	size_t	i = 0;

// 	while (i < str.length())
// 	{
// 		if (!is_element_of_set(this->_set_alphabet, str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	AST::is_valid_variable_name(std::string term)
// {
// 	if (term == "i")
// 	{
// 		this->_err_msg = "variable name cannot not be \"i\"";
// 		return (0);
// 	}
// 	if (!is_alpha_str(term))
// 	{
// 		this->_err_msg = "variable name should be consisted with letter(s)1";
// 		return (0);
// 	}
// 	return (1);
// }

// std::string	AST::is_element_of_func(std::string function_name)
// {
// 	std::string	value = "";

// 	if (this->_func.find(function_name) != this->_func.end())
// 		value = this->_func[function_name];
// 	return (value);
// }

// int	AST::is_valid_function_name(std::string term)
// {
// 	if (check_round_brackets(term) != 1)
// 	{
// 		this->_err_msg = "invalid function name: brackets";
// 		return (0);
// 	}

// 	std::string	function_name = term.substr(0, term.find("("));
// 	std::string	variable = term.substr(term.find("(") + 1, term.length() - term.find("(") - 2);

// 	std::cout << "funtion name: " << function_name << std::endl;
// 	std::cout << "variable: " << variable << std::endl;

// 	// /* check function name */
// 	if (!is_alpha_str(function_name))
// 	{
// 		this->_err_msg = "function name should be consisted with letter(s)";
// 		return (0);
// 	}
// 	// /* check variable */
// 	if (is_number_str(variable) && variable != "i")
// 	{
// 		if (is_element_of_func(function_name) == "")
// 		{
// 			this->_err_msg = "function does not exists, cannot assign";
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		if (!is_valid_variable_name(variable))
// 			return (0);
// 	}
// 	return (1);
// }

// int	AST::check_valid_term(std::string term_str)
// {
// 	if (term_str.find("[") != std::string::npos
// 			&& term_str.find("]") != std::string::npos)
// 	{
// 		if (term_str.find("[", 1) != std::string::npos)
// 			return (TERM_MATRIX);
// 		else
// 			return (TERM_VECTOR);
// 	}
// 	if (is_number_str(term_str))
// 		return (TERM_NUMBER);
// 	if (is_valid_variable_name(term_str))
// 		return (TERM_VARIBLE);
// 	if (is_valid_function_name(term_str))
// 		return (TERM_FUNCTION);
// 	return (TERM_INVALID);
// }

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

// void	AST::set_type_of_term(TermOperatorPair &term_op)
// {
// 	VectorTermPair	term_pair = term_op.first;
// 	int		type;

// 	for (size_t i = 0; i < term_pair.first.size(); i++)
// 	{
// 		type = check_valid_term(term_pair.first[i]);
// 		if (type == TERM_INVALID)
// 		{
// 			this->_err_msg = "cannot deciede value type";
// 			throw (this->_err_msg);
// 		}

// 		if (type == TERM_NUMBER)
// 		{
// 			term_pair.second[i] = convert_to_value_set(term_pair.first[i]);
// 			std::cout << "converted: value: ";
// 			print_variant_value(term_pair.second[i]);
// 			std::cout << std::endl;
			
// 		}
// 		else if (type == TERM_VARIBLE)
// 		{
// 			// variable: convert to value if variable already exists
// 			std::cout << "do it later: it's variable"
// 				<< std::endl;
// 		}
// 		else if (type == TERM_FUNCTION)
// 		{
// 			// function:
// 			//	- f(x): leave like this
// 			//	- f(1): (after making calculating function)
// 			//		check which type(number/vector/matrix), set type
// 			// set value after converting
// 			std::cout << "do it later: it's function(variable), or function(number)"
// 				<< std::endl;
// 		}
// 		else if (type == TERM_VECTOR)
// 			set_type_vector(term_pair.first[i], term_pair.second[i]);
// 		else
// 		{
// 			std::cout << term_pair.first[i] << "\ntype: matrix" << std::endl;
// 			/* code */
// 		}
// 	}
// 	std::cout << "----------------" << std::endl;
// }

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
	return (0);
}

void	AST::build_subtree(std::stack<std::unique_ptr<ASTNode>>& stack_node,
				std::stack<std::string>& stack_op)
{
	std::string	op = stack_op.top();
	stack_op.pop();

	std::unique_ptr<ASTNode>	right = std::move(stack_node.top());
	stack_node.pop();
	std::unique_ptr<ASTNode>	left = std::move(stack_node.top());
	stack_node.pop();

	stack_node.push(std::make_unique<ASTNode>(op, std::move(left), std::move(right)));
}

void	AST::build_tree(std::string str, std::unique_ptr<ASTNode> &node)
{
	std::stack<std::unique_ptr<ASTNode>>	stack_node;
	std::stack<std::string>			stack_op;

	std::string				sub_str;
	std::unique_ptr<ASTNode>		sub_root;

	size_t	start;
	size_t	i = 0;
	while (i < str.length())
	{
		if (str[i] == '(')
		{
			start = i;
			i = skip_round_bracket(str, i);
			sub_str = str.substr(start + 1, i - start - 1);
			sub_root = nullptr;
			build_tree(sub_str, sub_root);
			stack_node.push(std::move(sub_root));
			i++;
		}
		else if (is_key_of_map(this->_operation, str[i]))
		{
			if (!precedence(this->_operation[str[i]]))
			{
				this->_err_msg = "cannot set precedence of operation";
				throw (this->_err_msg);
			}
			while (!stack_op.empty() && precedence(stack_op.top()) >= precedence(this->_operation[str[i]]))
				build_subtree(stack_node, stack_op);
			stack_op.push(this->_operation[str[i]]);
			i++;
		}
		else
		{
			start = i;
			while (str[i] != '\0' && str[i] != '?'
				&& str[i] != '(' && !is_key_of_map(this->_operation, str[i]))
				i++;
			if (str.substr(start, i - start) != "" && str.substr(start, i - start) != "?")
				stack_node.push(std::make_unique<ASTNode>(ASTNode(str.substr(start, i - start))));
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

	if (node->get_type() == NodeType::TERM)
		std::cout << "TERM: ";
	else if (node->get_type() == NodeType::OPERATOR)
		std::cout << "OP: ";
	
	std::cout << node->get_value_str() << std::endl;
}

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

int	AST::check_str(std::string str)
{
	std::string		left_str = str.substr(0, str.find("="));
	std::string		right_str = str.substr(str.find("=") + 1, std::string::npos);

	std::unique_ptr<ASTNode>	left_root = nullptr;
	std::unique_ptr<ASTNode>	right_root = nullptr;

	build_tree(left_str, left_root);
	build_tree(right_str, right_root);

	std::cout << "left AST----------" << std::endl;
	visit_ast(left_root.get());
	std::cout << std::endl << "right AST----------" << std::endl;
	visit_ast(right_root.get());

	// std::cout << std::endl << "calc----------" << std::endl;
	// float left_value = calculate_ast(left_root.get());
	// std::cout << "calc: " << left_value << std::endl;
	return (1);
}
