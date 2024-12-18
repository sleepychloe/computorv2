/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:46:22 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 14:59:46 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute/AST.hpp"

AST::AST(): _left_root(nullptr), _right_root(nullptr), _err_msg("")
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i'};
	this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
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

std::map<std::string, std::string>	AST::get_var(void) const
{
	return (this->_var);
}

std::map<std::string, std::string>	AST::get_func(void) const
{
	return (this->_func);
}

void	AST::start_syntax_checking(std::string &str)
{
	check_str(str);
}

int	AST::is_number_str(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(is_element_of_set(this->_set_number, str[i])
			|| str[i] == '+' || str[i] == '-'))
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
		if (term.find("[") != std::string::npos)
			this->_err_msg = "vector and matrix cannot be used with function";
		else
			this->_err_msg = "variable name should be consisted with letter(s)";
		return (0);
	}
	return (1);
}

int	AST::is_valid_function_name(std::string term)
{
	if (check_round_brackets(term) != 1)
	{
		this->_err_msg = "invalid function name: brackets";
		return (0);
	}
	if (!(is_alpha_str(get_function_name(term))))
	{
		this->_err_msg = "function name should be consisted with letter(s)";
		return (0);
	}
	if (!(is_number_str(get_function_variable(term))
		|| is_valid_variable_name(get_function_variable(term))))
		return (0);
	return (1);
}

NodeType	AST::set_type_of_term(std::string term)
{
	if (term.find("(") != std::string::npos
			&& term.find(")") != std::string::npos)
	{
		if (is_valid_function_name(term))
			return (NodeType::TERM_FUNCTION);
	}
	else if (term.find("[") != std::string::npos
			&& term.find("]") != std::string::npos)
	{
		if (term.find("[", 1) != std::string::npos)
			return (NodeType::TERM_MATRIX);
		else
			return (NodeType::TERM_VECTOR);
	}
	else
	{
		if (is_number_str(term))
			return (NodeType::TERM_NUMBER);
		if (is_valid_variable_name(term))
			return (NodeType::TERM_VARIABLE);
	}
	return (NodeType::TERM_INVALID);
}

int	AST::is_existing_variable(std::string var)
{
	if (this->_var.find(var) != this->_var.end())
		return (1);
	return (0);
}

int	AST::is_existing_function_name(std::string func)
{
	if (this->_func.find(func) != this->_func.end())
		return (1);
	return (0);
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
	{
		std::cout << "type: number" << std::endl;//
	}
	else if (type == NodeType::TERM_VARIABLE)
	{
		if (is_existing_variable(term))
		{
			std::cout << "existing variable" << std::endl;
		}
		std::cout << "type: variable" << std::endl;//
	}
	else if (type == NodeType::TERM_FUNCTION)
	{
		if (is_number_str(get_function_variable(term)))
		{
			if (is_existing_function_name(get_function_name(term)))
			{
				std::cout << "varibale is number, existing function name" << std::endl;
			}
			else
			{
				this->_err_msg = "function has not been defiend";
				throw (this->_err_msg);
			}
		}
		std::cout << "type: function" << std::endl;//
	}
	else if (type == NodeType::TERM_VECTOR)
	{
		std::cout << "type: vector" << std::endl;//
	}
	else if (type == NodeType::TERM_MATRIX)
	{
		std::cout << "type: matrix" << std::endl;//
	}
	return (type);
}

int	AST::check_str(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	this->_left_root = nullptr;
	this->_right_root = nullptr;

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

///////////////////////////////////////////////////////////////////////////
// void	AST::print_variant_value(ValueSet value)
// {
// 	if (std::get_if<float>(&value))
// 		std::cout << *std::get_if<float>(&value);
// 	else if (std::get_if<Complex<float>>(&value))
// 		std::cout << *std::get_if<Complex<float>>(&value);
// 	else if (std::get_if<Matrix<float>>(&value))
// 		std::cout << *std::get_if<Matrix<float>>(&value);
// 	else if (std::get_if<Matrix<Complex<float>>>(&value))
// 		std::cout << *std::get_if<Matrix<Complex<float>>>(&value);
// 	else if (std::get_if<Vector<float>>(&value))
// 		std::cout << *std::get_if<Vector<float>>(&value);
// 	else if (std::get_if<Vector<Complex<float>>>(&value))
// 		std::cout << *std::get_if<Vector<Complex<float>>>(&value);
// 	else
// 	{
// 		this->_err_msg = "detected unknown type while printing variable list";
// 		this->_err_msg += ": std::map<std::string, V>";
// 		this->_err_msg += "(V = std::variant<float, Complex<float>, Matrix<float>, Matrix<Complex<float>>,";
// 		this->_err_msg += "Vector<float>, Vector<Complex<float>>>)";
// 		throw (this->_err_msg);
// 	}
// }
// std::string	AST::float_to_string(float value)
// {
// 	std::stringstream	ss;

// 	ss << value;
// 	return (ss.str());
// }

// std::string	AST::complex_to_string(Complex<float> value)
// {
// 	std::string	real = float_to_string(value.real());
// 	std::string	imag = float_to_string(value.imag());
// 	std::string	res;

// 	if (real == "0" && imag == "0")
// 		return ("0");
// 	imag = imag + "i";
// 	if (real != "0" && value.imag() > 0)
// 		imag = "+" + imag;
// 	if (real == "0")
// 		real = "";
// 	if (imag == "0i")
// 		imag = "";
// 	return (real + imag);
// }

// std::string	AST::ValueSet_to_string(ValueSet value)
// {
// 	if (std::get_if<float>(&value))
// 		return (float_to_string(*std::get_if<float>(&value)));
// 	else if (std::get_if<Complex<float>>(&value))
// 		return (complex_to_string(*std::get_if<Complex<float>>(&value)));
// 	else if (std::get_if<Vector<float>>(&value))
// 	{

// 	}
// 	else if (std::get_if<Vector<Complex<float>>>(&value))
// 	{

// 	}
// 	else if (std::get_if<Matrix<float>>(&value))
// 	{

// 	}
// 	else if (std::get_if<Matrix<Complex<float>>>(&value))
// 	{

// 	}
// 	return ("");
// }
