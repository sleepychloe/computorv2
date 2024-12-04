/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/04 03:03:01 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _err_msg("")
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i'};
	this->_set_vector_matrix = { '[', ']', ',', ';'};
	this->_set_operation = {'+', '-', '*', '/', '%'};
	this->_set_other = {'(', ')','^', '=', '?'};
	this->_set_space = {' ', '\t'};
	this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"},
			{OP_DIV, "/"}, {OP_MODULO, "%"}, {OP_MAT_MUL, "**"}};
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_set_alphabet = parse._set_alphabet;
	this->_set_number = parse._set_number;
	this->_set_vector_matrix = parse._set_vector_matrix;
	this->_set_operation = parse._set_operation;
	this->_set_other = parse._set_other;
	this->_set_space = parse._set_space;
	this->_operation = parse._operation;
	this->_var = parse._var;
	this->_func = parse._func;
	this->_left_term_operator = parse._left_term_operator;
	this->_right_term_operator = parse._right_term_operator;
	this->_err_msg = parse._err_msg;
	return (*this);
}

Parse::~Parse()
{
}

void	Parse::parse_start(std::string &str)
{
	check_str(str);
}

void	Parse::print_variant_value(ValueSet value)
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

int	Parse::check_keyword(std::string str)
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
		if (this->_var.size() == 0)
		{
			std::cout << MAGENTA
				<< "there is no function assigned yet" << BLACK << std::endl;
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
	return (0);
}

int	Parse::is_equation_form(std::string str)
{
	int	flag = 0;
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		i++;
	}
	if (flag != 1)
	{
		this->_err_msg = "equal(=) sign is missing";
		if (flag != 0)
			this->_err_msg = "equal(=) sign used multiple times";
		throw (this->_err_msg);
	}

	i = 0;
	while (i < str.length())
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '=')
		{
			this->_err_msg = "invalid equation form";
			throw (this->_err_msg);
		}
		while (str[i] != '=')
			i++;
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			break ;
		else
		{
			this->_err_msg = "invalid equation form";
			throw (this->_err_msg);
		}
	}
	return (1);
}

int	Parse::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(is_element_of_set(this->_set_alphabet, str[i])
			|| is_element_of_set(this->_set_number, str[i])
			|| is_element_of_set(this->_set_vector_matrix, str[i])
			|| is_element_of_set(this->_set_operation, str[i])
			|| is_element_of_set(this->_set_other, str[i])
			|| is_element_of_set(this->_set_space, str[i])))
		{
			this->_err_msg = "invalid character exists: ";
			this->_err_msg += str[i];
			throw (this->_err_msg);
		}
		i++;
	}
	return (1);
}

int	Parse::check_float_point(std::string str)
{
	size_t	i = 0;
	int	point;
	int	digit;

	while (i < str.length())
	{
		point = 0;
		digit = 0;
		if (str[i] == '.')
		{
			point++;
			if (!((str[i - 1] && ('0' <= str[i - 1] && str[i - 1] <= '9'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
			{
				this->_err_msg = "invalid syntax: float point";
				throw (this->_err_msg);
			}
			i++;

			if (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				{
					if (str[i] == '.')
						point++;
					else
						digit++;
					i++;
				}
				if (str[i - 1] == '.' || point >= 2 || digit > 5)
				{
					this->_err_msg = "invalid syntax: float point";
					if (digit > 5)
						this->_err_msg += ": supports up to the fifth decimal place";
					throw (this->_err_msg);
				}
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_number(std::string str)
{
	size_t	i = 0;
	int	space = 0;

	while (i < str.length())
	{
		space = 0;
		if ('0' <= str[i] && str[i] <= '9')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
			{
				space++;
				i++;
			}
			if (space && ('0' <= str[i] && str[i] <= '9'))
			{
				this->_err_msg = "invalid syntax: no operator between numbers";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (check_float_point(str));
}

void	Parse::remove_space(std::string &str)
{
	size_t		i = 0;
	std::string	new_str = "";

	while (i < str.size())
	{
		if (str[i] != ' ' && str[i] != '\t')
			new_str += str[i];
		i++;
	}
	str = new_str;
}

int	Parse::check_question_mark(std::string str)
{
	if (str.find("?") == std::string::npos)
		return (1);

	if (str[str.length() - 1] != '?'
		|| str.find("?") < str.find("=")
		|| str.find("?") != str.length() - 1)
	{
		this->_err_msg = "invalid syntax: question mark";
		throw (this->_err_msg);
	}
	return (1);
}

int	Parse::check_brackets(int type, std::string str)
{
	std::stack<char>	stack;
	char			bracket[2];
	size_t			i = 0;

	bracket[OPEN] = (type == ROUND_BRACKET) ? '(' : '[';
	bracket[CLOSE] = (type == ROUND_BRACKET) ? ')' : ']';

	if (str.find(std::string(1, bracket[CLOSE])) == std::string::npos
		&& str.find(std::string(1, bracket[OPEN])) == std::string::npos)
		return (1);

	while (i < str.length())
	{
		if (str[i] == bracket[OPEN])
			stack.push(str[i]);
		if (str[i] == bracket[CLOSE])
		{
			if ((str[i - 1] && str[i - 1] == bracket[OPEN])
				|| stack.empty())
			{
				if (bracket[OPEN] == '(')
					this->_err_msg = "invalid syntax: round brackets";
				else
					this->_err_msg = "invalid syntax: square brackets";
				throw (this->_err_msg);
			}
			stack.pop();
		}
		i++;
	}
	if (!stack.empty())
	{
		if (bracket[OPEN] == '(')
			this->_err_msg = "invalid syntax: round brackets";
		else
			this->_err_msg = "invalid syntax: square brackets";
		throw (this->_err_msg);
	}
	return (1);
}

int	Parse::check_vector_form(int type, std::string str)
{
	std::vector<std::string>	column;

	str = str.substr(1, str.length() - 2);
	if (str[str.length() - 1] == ',')
	{
		if (type == VECTOR)
			this->_err_msg = "invalid syntax: vector form";
		else
			this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}
	column = split(str, ',');

	if (!column.size())
	{
		if (type == VECTOR)
			this->_err_msg = "invalid syntax: vector form";
		else
			this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}

	for (size_t i = 0; i < column.size(); i++)
	{
		convert_operator(column[i]);
		if (column[i] == ""
			|| !check_brackets(ROUND_BRACKET, column[i])
			|| !check_operator(column[i]))
		{
			if (type == VECTOR)
				this->_err_msg = "invalid syntax: vector form";
			else
				this->_err_msg = "invalid syntax: matrix form";
			throw (this->_err_msg);
		}
	}
	return (column.size());
}

int	Parse::check_matrix_form(std::string str)
{
	std::vector<std::string>	row;
	str = str.substr(1, str.length() - 2);
	if (str[str.length() - 1] == ';')
	{
		this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}
	row = split(str, ';');

	/* check row */
	if (!row.size())
	{
		this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}

	/* check column */
	int		col_size;
	for (size_t i = 0; i < row.size();i++)
	{
		if (!(row[i][0] == '[' && row[i][row[i].length() - 1] == ']')
			|| row[i].find("[", 1) != std::string::npos)
		{
			this->_err_msg = "invalid syntax: matrix form";
			throw (this->_err_msg);
		}
		if (i == 0)
			col_size = check_vector_form(MATRIX, row[i]);
		else
		{
			if (col_size != check_vector_form(MATRIX, row[i]))
			{
				this->_err_msg = "invalid syntax: matrix form";
				throw (this->_err_msg);
			}
		}
	}
	return (row.size());
}

int	Parse::skip_bracket(int type, std::string str, size_t i)
{
	char			bracket[2];
	std::stack<char>	stack;

	bracket[OPEN] = (type == SQUARE_BRACKET) ? '[': '(';
	bracket[CLOSE] = (type == SQUARE_BRACKET) ? ']': ')';

	stack.push(str[i]);
	i++;
	while (i < str.length())
	{
		if (str[i] == bracket[OPEN])
			stack.push(str[i]);
		if (str[i] == bracket[CLOSE])
			stack.pop();
		if (stack.empty())
			break ;
		i++;
	}
	return (i);
}

int	Parse::skip_vector_matrix(std::string str, std::string &new_str, size_t i)
{
	if (str[i] != '[')
		return (i);

	std::string		bracket;
	size_t			start = i;
	size_t			j = 0;
	int			cnt = 0;

	i = skip_bracket(SQUARE_BRACKET, str, i);
	i++;
	bracket = str.substr(start, i - start);

	while (j < bracket.length())
	{
		if (bracket[j] == '[')
			cnt++;
		j++;
	}

	if (cnt == 1)
	{
		if (!(check_brackets(SQUARE_BRACKET, bracket)
			&& check_vector_form(VECTOR, bracket)))
			return (0);
		new_str += bracket;
	}
	else
	{
		if (!(check_brackets(SQUARE_BRACKET, bracket)
			&& check_matrix_form(bracket)))
			return (0);
		new_str += bracket;
	}
	return (i++);
}

char	Parse::do_convert(std::string str, size_t &i)
{
	std::unordered_map<char, int> op = {{'+', OP_ADD}, {'-', OP_SUB},
					{'*', OP_MUL}, {'/', OP_DIV}, {'%', OP_MODULO}};
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i - 1] && (str[i - 1] == '(' || str[i - 1] == '^'
					|| str[i - 1] == OP_MUL || str[i - 1] == OP_MAT_MUL
					|| str[i - 1] == OP_DIV || str[i - 1] == OP_MODULO))
			return (str[i]);
	}
	else if (str[i] == '*')
	{
		if (str[i + 1] && str[i + 1] == '*')
		{
			i = i + 1;
			return (OP_MAT_MUL);
		}
	}
	return (op[str[i]]);
}

void	Parse::convert_operator(std::string &str)
{
	std::string	new_str = "";
	size_t		i = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		new_str += str[0];
		i++;
	}
	while (i < str.length())
	{
		i = skip_vector_matrix(str, new_str, i);
		if (!(is_element_of_set(this->_set_alphabet, str[i])
			|| is_element_of_set(this->_set_number, str[i])
			|| is_element_of_set(this->_set_operation, str[i])
			|| is_element_of_set(this->_set_other, str[i])
			|| str[i] == '\0'))
		{
			this->_err_msg = "invalid character exists: ";
			this->_err_msg += str[i];
			throw (this->_err_msg);
		}
		if (is_element_of_set(this->_set_operation, str[i]))
			new_str += do_convert(str, i);
		else
			new_str += str[i];
		i++;
	}
	str = new_str;
}

int	Parse::check_operator(std::string str)
{
	size_t			i = 0;

	if (is_key_of_map(this->_operation, str[0])
		|| is_key_of_map(this->_operation, str[str.length() - 1]))
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
	}

	while (i < str.length())
	{
		if (is_key_of_map(this->_operation, str[i]))
		{
			if (str[i + 1] && is_key_of_map(this->_operation, str[i + 1]))
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		else if (str[i] == '[' || str[i] == '(')
		{
			// if (i != 0 && !is_key_of_map(this->_operation, str[i - 1])
			// 	&& !(str[i] == '(' && str[i - 1] == '^'))
			// {
			// 	this->_err_msg = "invalid syntax: operator";
			// 	throw (this->_err_msg);
			// }
			if (str[i] == '[')
				i = skip_bracket(SQUARE_BRACKET, str, i);
			else
				i = skip_bracket(ROUND_BRACKET, str, i);
			i++;
			
			// if (str[i] != '\0' && !is_key_of_map(this->_operation, str[i])
			// 	&& !(str[i - 1] == ')' && str[i] == '^'))
			// {
			// 	this->_err_msg = "invalid syntax: operator";
			// 	throw (this->_err_msg);
			// }
		}
		i++;
	}
	return (1);
}

int	Parse::check_caret(std::string str)
{
	size_t	i = 0;

	if (str[0] == '^' || str[str.length() - 1] == '^')
	{
		this->_err_msg = "invalid syntax: caret(^)";
		throw(this->_err_msg);
	}
	while (i < str.length())
	{
		if (str[i] == '^')
		{
			/* base: num or (num) */
			if (!(std::isdigit(str[i - 1])
				|| is_element_of_set(this->_set_alphabet, str[i - 1]) || str[i - 1] == ')'))
			{
				this->_err_msg = "invalid syntax: caret(^)";
				throw(this->_err_msg);
			}
			i++;
			/* power: (+-int) */
			while (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-'
				|| std::isdigit(str[i]) || is_element_of_set(this->_set_alphabet, str[i]))
				i++;
			if (str[i] == '\0')
				return (1);
			if (str[i - 1] == '^' || str[i] == '^' || !is_key_of_map(this->_operation, str[i]))
			{
				this->_err_msg = "invalid syntax: caret(^)";
				throw(this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_syntax(std::string &str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_question_mark(str) 
		&& check_brackets(ROUND_BRACKET, left_str)
		&& check_brackets(ROUND_BRACKET, right_str)
		&& check_brackets(SQUARE_BRACKET, left_str)
		&& check_brackets(SQUARE_BRACKET, right_str)))
		return (0);

	convert_operator(left_str);
	convert_operator(right_str);
	str = left_str + "=" + right_str;

	if (!(check_caret(left_str) && check_caret(right_str)
		&& check_operator(left_str) && check_operator(right_str)))
		return (0);
	return (1);
}

void	Parse::split_term(std::string str, VectorStrIntPair &term_op)
{
	std::vector<std::string>	term;
	std::vector<int>		op;
	size_t				i;

	while (1)
	{
		i = 0;
		while (!is_key_of_map(this->_operation, str[i])
			&& str[i] != '?' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		if (str.substr(0, i) != "")
			term.push_back(str.substr(0, i));
		if (str[i] != '?')
			op.push_back(str[i]);
		else
			term.push_back(std::string(1, str[i]));
		str = str.substr(i + 1, std::string::npos);
	}
	if (str != "")
		term.push_back(str);

	term_op.first = term;
	term_op.second = op;
}

int	Parse::check_value_type(std::string &value_str)
{
	if (value_str == "?")
		return (TYPE_QUESTION_MARK);

	if (value_str.find("[") != std::string::npos
		&& value_str.find("]") != std::string::npos)
	{
		if (value_str.find("[", 1) != std::string::npos)
			return (TYPE_MATRIX);
		else
			return (TYPE_VECTOR);
	}
	else
		return (TYPE_NUMBER);
	return (0);
}

int	Parse::is_valid_variable_name(std::string term)
{
	size_t	i = 0;

	if (term == "i")
		return (0);
	while (i < term.length())
	{
		if (!is_element_of_set(this->_set_alphabet, term[i]))
			return (0);
		i++;
	}
	//check variable name, convert
	return (1);
}

int	Parse::is_valid_function_name(std::string term)
{
	if (term.find("(") == std::string::npos
		|| !check_brackets(ROUND_BRACKET, term)
		|| term.find("(", term.find("(") + 1) != std::string::npos)
		return (0);

	/* check function name */
	size_t	i = 0;
	while (i < term.find("("))
	{
		if (!is_element_of_set(this->_set_alphabet, term[i]))
			return (0);
		i++;
	}
	i++;

	/* check variable */
	std::string	variable = term.substr(i , term.length() - 1 - i);

	//consider about f(2), not only f(x)
	//when variable is number -> check number is valid, check function name, convert

	// when variable is letter
	// if (!is_valid_variable_name(term.substr(i , term.length() - 1 - i)))
	// 	return (0);
	return (1);
}

int	Parse::is_valid_term(std::string &term)
{
	size_t	i = 0;

	if (is_element_of_set(this->_set_number, term[0]))
	{
		while (i < term.size())
		{
			if (!(is_element_of_set(this->_set_number, term[i])
				|| term[i] == '^'))
				return (0);
			i++;
		}
		return (1);
	}
	if (!(is_valid_function_name(term) || is_valid_variable_name(term)))
		return (0);


	while (i < term.length())
	{
		term[i] = std::toupper(term[i]);
		i++;
	}
	return (1);
}

void	Parse::convert_type_number(std::string &term)
{
	if (!is_valid_term(term))
	{
		this->_err_msg = "invalid term";
		throw (this->_err_msg);
	}

	// check variable, function name -> replace
}

void	Parse::convert_term(VectorStrIntPair &term_op)
{
	int	type;
	
	for (size_t i = 0; i < term_op.first.size(); i++)
	{
		type = check_value_type(term_op.first[i]);
		if (!type)
		{
			this->_err_msg = "cannot deciede value type";
			throw (this->_err_msg);
		}
		if (type == TYPE_NUMBER)
		{
			convert_type_number(term_op.first[i]);
			std::cout << term_op.first[i] << "\ntype: number" << std::endl;
		}
		else if (type == TYPE_VECTOR)
		{
			std::cout << term_op.first[i] << "\ntype: vector" << std::endl;
		}
		else if (type == TYPE_MATRIX)
		{
			std::cout << term_op.first[i] << "\ntype: matrix" << std::endl;
		}
		else
			term_op.first.pop_back();
	}
	std::cout << "----------------" << std::endl;
}

int	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return (1);
	if (!(is_equation_form(str) && check_invalid_character(str) && check_number(str)))
		return (0);

	remove_space(str);
	if (!check_syntax(str))
		return (0);

	//remove brackets


	std::string		left_str = str.substr(0, str.find("="));
	std::string		right_str = str.substr(str.find("=") + 1, std::string::npos);
	VectorStrIntPair	left_term_operator;
	VectorStrIntPair	right_term_operator;

	split_term(left_str, left_term_operator);
	split_term(right_str, right_term_operator);

	convert_term(left_term_operator);
	convert_term(right_term_operator);

///////////////////
	std::cout << "left term: " << left_str << std::endl;
	for (size_t i = 0; i < left_term_operator.first.size(); i++)
	{
		std::cout << "term: " << left_term_operator.first[i] << std::endl;
		if (i < left_term_operator.second.size())
		{
			std::cout << "op: " << std::endl;
			if (left_term_operator.second[i] == OP_ADD)
				std::cout << "\"+\"" << std::endl;
			else if (left_term_operator.second[i] == OP_SUB)
				std::cout << "\"-\"" << std::endl;
			else if (left_term_operator.second[i] == OP_MUL)
				std::cout << "\"*\"" << std::endl;
			else if (left_term_operator.second[i] == OP_DIV)
				std::cout << "\"/\"" << std::endl;
			else if (left_term_operator.second[i] == OP_MODULO)
				std::cout << "\"%\"" << std::endl;
			else if (left_term_operator.second[i] == OP_MAT_MUL)
				std::cout << "\"**\"" << std::endl;
		}
	}
	std::cout << "right term: " << right_str << std::endl;
	for (size_t i = 0; i < right_term_operator.first.size(); i++)
	{
		std::cout << "term: " << right_term_operator.first[i] << std::endl;
		if (i < right_term_operator.second.size())
		{
			std::cout << "op: " << std::endl;
			if (right_term_operator.second[i] == OP_ADD)
				std::cout << "\"+\"" << std::endl;
			else if (right_term_operator.second[i] == OP_SUB)
				std::cout << "\"-\"" << std::endl;
			else if (right_term_operator.second[i] == OP_MUL)
				std::cout << "\"*\"" << std::endl;
			else if (right_term_operator.second[i] == OP_DIV)
				std::cout << "\"/\"" << std::endl;
			else if (right_term_operator.second[i] == OP_MODULO)
				std::cout << "\"%\"" << std::endl;
			else if (right_term_operator.second[i] == OP_MAT_MUL)
				std::cout << "\"**\"" << std::endl;
		}
	}
	return (1);
}
