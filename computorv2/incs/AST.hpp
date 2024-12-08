/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:46:25 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/08 16:54:31 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_HPP
# define AST_HPP

#include <string>
#include <stack>
#include <variant>
#include <map>
#include <unordered_set>
#include "./ASTNode.hpp"
#include "../matrix/incs/Complex.hpp"
#include "../matrix/incs/Vector.hpp"
#include "../matrix/incs/Matrix.hpp"
#include "./Utils.hpp"
#include "./Color.hpp"

# define OP_ADD			1 /* + */
# define OP_SUB			2 /* - */
# define OP_MUL			3 /* * */
# define OP_DIV			4 /* / */
# define OP_MODULO		5 /* % */
# define OP_POWER		6 /* ^ */
# define OP_MAT_MUL		7 /* ** */

# define TERM_INVALID		0
# define TERM_NUMBER		1
# define TERM_VARIBLE		2
# define TERM_FUNCTION		3
# define TERM_VECTOR		4
# define TERM_MATRIX		5

using	ValueSet = std::variant<float,
				Complex<float>,
				Matrix<float>,
				Matrix<Complex<float>>,
				Vector<float>,
				Vector<Complex<float>>>;

class AST
{
public:
	AST();
	AST(const AST& ast);
	AST &operator=(const AST& ast);
	~AST();

	void				start_syntax_checking(std::string &str);
	
private:
	void				print_variant_value(ValueSet value);
	int				check_keyword(std::string str);

	int				skip_round_bracket(std::string str, size_t i);
	int				precedence(std::string op);
	void				build_subtree(std::stack<std::unique_ptr<ASTNode>>& stack_node,
						std::stack<std::string>& stack_op);

	int				is_part_of_function_expression(std::string str, int i);
	std::unique_ptr<ASTNode>	handle_brackets(std::string str, size_t &i);
	void				build_tree(std::string str, std::unique_ptr<ASTNode> &root);

	void				visit_ast(ASTNode *node);
	// float				calculate_ast(ASTNode *node);

	// int				is_number_str(std::string str);
	// int				is_alpha_str(std::string str);
	// int				is_valid_variable_name(std::string term);
	// std::string			is_element_of_func(std::string function_name);
	// int				is_valid_function_name(std::string term);

	// ValueSet			convert_to_value_set(std::string term_str);
	// void				set_type_number(std::string &term_str, ValueSet &term_value);

	// Complex<float>			string_to_complex(std::string nb_str);
	// void				set_type_vector(std::string &term_str, ValueSet &term_value);
	// int				check_valid_term(std::string term_str);
	// void				set_type_of_term(TermOperatorPair &term_op);

	int				check_str(std::string str);

	std::unordered_set<char>		_set_alphabet; // 'a' to 'z'
	std::unordered_set<char>		_set_number; // '0' to '9', '.', 'i'
	std::unordered_map<int, std::string>	_operation; // {OP_OPERATOR, "operator"}

	std::map<std::string, ValueSet>		_var;
	std::map<std::string, std::string>	_func;

	std::unique_ptr<ASTNode>		_left_root;
	std::unique_ptr<ASTNode>		_right_root;

	std::string				_err_msg;
};

#endif
