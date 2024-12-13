/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/13 22:00:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()//: _err_msg("")
{
	this->_set_alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	this->_set_number = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', 'i', 'I'};
	this->_set_vector_matrix = { '[', ']', ',', ';'};
	this->_set_operation = {'+', '-', '*', '/', '%', '^'};
	this->_set_other = {'(', ')','^', '=', '?'};
	this->_set_space = {' ', '\t'};
	this->_operation = {{OP_ADD, "+"}, {OP_SUB, "-"}, {OP_MUL, "*"}, {OP_DIV, "/"},
				{OP_MODULO, "%"}, {OP_POWER, "^"}, {OP_MAT_MUL, "**"}};
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_str = parse._str;
	this->_set_alphabet = parse._set_alphabet;
	this->_set_number = parse._set_number;
	this->_set_vector_matrix = parse._set_vector_matrix;
	this->_set_operation = parse._set_operation;
	this->_set_other = parse._set_other;
	this->_set_space = parse._set_space;
	this->_operation = parse._operation;
	this->_var = parse._var;
	this->_func = parse._func;
	this->_struct_error = parse._struct_error;
	return (*this);
}

Parse::~Parse()
{
}

void	Parse::set_var(std::map<std::string, std::string> var)
{
	this->_var = var;
}

void	Parse::set_func(std::map<std::string, std::string> func)
{
	this->_func = func;
}

std::string	Parse::parse_start(std::string &str)
{
	this->_str = str;
	return (check_str(str));
}

void	Parse::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.cat = "syntax error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	this->_struct_error.pos = pos;

	this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.pos_str += "\t\t  ";
	this->_struct_error.pos_str += RED;
	if (pos != std::string::npos && pos >= 1)
	{
		for (size_t i = 0; i < pos - 1; i++)
			this->_struct_error.pos_str += "~";
	}
	this->_struct_error.pos_str += "^";
	this->_struct_error.pos_str += BLACK;
	throw (ParseException(this->_struct_error));
}

int	Parse::check_keyword(std::string str)
{
	if (str == "var" || str == "VAR"
		|| str == "vriable" || str == "VARIABLE")
	{
		return (1);
	}
	else if (str == "func" || str == "FUNC"
		|| str == "function" || str == "FUNCTION")
	{
		return (1);
	}
	return (0);
}

int	Parse::check_equal_sign(std::string str)
{
	int	flag = 0;
	size_t	i = 0;
	
	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		if (flag > 1)
			throw_err_msg("Parse::check_equal_sign(std::string str)",
				"equal(=) sign used multiple times", i);
		i++;
	}
	if (!flag)
		throw_err_msg("Parse::check_equal_sign(std::string str)",
			"equal(=) sign is missing", i);
	return (1);
}

int 	Parse::check_each_term(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '=')
			throw_err_msg("Parse::check_each_term(std::string str)",
				"invalid equation form: left term does not exist", i);

		while (str[i] != '=')
			i++;
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			break ;
		else
			throw_err_msg("Parse::check_each_term(std::string str)",
				"invalid equation form: right term does not exist", i);
	}
	return (1);
}

int	Parse::is_equation_form(std::string str)
{
	return (check_equal_sign(str) && check_each_term(str));
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
			throw_err_msg("Parse::check_invalid_character(std::string str)",
				"invalid character exists", i);
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
			i++;
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				if (str[i] == '.')
					point++;
				else
					digit++;
				if (digit > 5)
					throw_err_msg("check_float_point(std::string str)",
						"incorrect use of floating point: supports up to the fifth decimal place", i);
				if (point > 1)
					throw_err_msg("check_float_point(std::string str)",
							"incorrect use of floating point: used multiple times in one number", i);
				i++;
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
				throw_err_msg("Parse::check_number(std::string str)",
					"no operator between numbers", i - 1);
		}
		if (str[i] == '.')
		{
			if (!((str[i - 1] && ('0' <= str[i - 1] && str[i - 1] <= '9'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
				throw_err_msg("Parse::check_number(std::string str)",
					"incorrect location of floating point", i);
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

void	Parse::convert_to_standard_form(std::string &str)
{
	std::string	front;
	std::string	back;
	size_t		i = 0;

	remove_space(str);

	// ax to a*x, af(x) to a*f(x)
	while (i < str.length())
	{
		if (is_element_of_set(this->_set_number, str[i])
			&& str[i + 1]
			&& !is_element_of_set(this->_set_number, str[i + 1])
			&& is_element_of_set(this->_set_alphabet, str[i + 1]))
		{
			i++;
			front = str.substr(0, i);
			back = str.substr(i, std::string::npos);
			str = front + "*" + back;
		}
		i++;
	}
	this->_str = str;
}

// std::vector<std::string>	Parse::split_term(std::string str)
// {
// 	std::vector<std::string>	term;
// 	size_t				i = 0;
// 	std::string			tmp;

// 	convert_operator(str);
// 	while (1)
// 	{
// 		i = 0;
// 		while (!is_key_of_map(this->_operation, str[i])
// 			&& str[i] != '?' && str[i] != '\0')
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		if (str.substr(0, i) != "")
// 			term.push_back(str.substr(0, i));
// 		if (str[i] != '?')
// 			term.push_back(std::string(1, str[i]));
// 		else
// 			term.push_back(std::string(1, str[i]));
// 		str = str.substr(i + 1, std::string::npos);
// 	}
// 	if (str != "")
// 		term.push_back(str);
// 	return (term);
// }

// void	Parse::process_variable_term(std::string &term)
// {
// 	term = "(" + this->_var[term] + ")";
// }

// std::string	Parse::convert_func_variable(std::string term,
// 				std::string var_key, std::string var_value)
// {
// 	std::string	name = get_function_name(term);
// 	std::string	variable = get_function_variable(term);
// 	std::string	front;
// 	std::string	back;

// 	if (variable == var_key)
// 		term = name + "(" + var_value + ")";
// 	else if (variable.find(var_key) != std::string::npos)
// 	{
// 		front = variable.substr(0, variable.find(var_key));
// 		back = variable.substr(variable.find(var_key) + var_key.length(), std::string::npos);

// 		if ((front == "" || !is_element_of_set(this->_set_alphabet, front[front.length() - 1]))
// 			&& !is_element_of_set(this->_set_alphabet, back[0]))
// 			term = name + "(" + front + "(" + var_value + ")" + back + ")";
// 	}
// 	return (term);
// }

// std::string	Parse::convert_func_name(std::string term,
// 				std::string func_key, std::string func_value)
// {
// 	std::string	function;
// 	std::string	front;
// 	std::string	back;
// 	size_t		i = 0;

// 	if (get_function_name(term) == func_key)
// 	{
// 		function = func_value;
// 		while (i < function.length())
// 		{
// 			if (function[i] == 'x')
// 			{
// 				front = function.substr(0, i);
// 				back = function.substr(i + 1, std::string::npos);
// 				term = front + "(" + get_function_variable(term) + ")" + back;
// 				i = front.length() + get_function_variable(term).length() + 2;
// 			}
// 			else
// 				i++;
// 		}
// 	}
// 	term = "(" + term + ")";
// 	return (term);
// }

// void	Parse::process_function_term(std::string &term)
// {
// 	std::string			func_name;

// 	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
// 		it != this->_var.end(); it++)
// 	{
// 		if (term.find(it->first) != std::string::npos)
// 		{
// 			term = convert_func_variable(term, it->first, it->second);
// 			func_name = get_function_name(term);;
// 			if (is_key_of_map(this->_func, func_name))
// 				term = convert_func_name(term, func_name, this->_func[func_name]);
// 		}
// 	}
// }

// std::string	Parse::revert_term_to_str(std::vector<std::string> term)
// {
// 	std::string	str = "";

// 	for (size_t i = 0; i < term.size(); i++)
// 	{
// 		if (is_key_of_map(this->_operation, term[i][0]))
// 			str += this->_operation[term[i][0]];
// 		else
// 			str += term[i];
// 	}
// 	return (str);
// }

// void	Parse::convert_val_func(std::string &str)
// {
// 	std::vector<std::string>	term = split_term(str);

// 	for(size_t i = 0; i < term.size(); i++)
// 	{
// 		if (is_key_of_map(this->_var, term[i]))
// 			process_variable_term(term[i]);
// 		if (term[i].find("(") != std::string::npos
// 			&& is_bracket_for_function(term[i], term[i].find("(")))
// 			process_function_term(term[i]);
// 	}
// 	str = revert_term_to_str(term);
// }

int	Parse::check_question_mark(std::string str)
{
	if (str.find("?") == std::string::npos)
		return (1);

	if (str[str.length() - 1] != '?'
		|| str.find("?") < str.find("=")
		|| str.find("?") != str.length() - 1)
		throw_err_msg("Parse::check_question_mark(std::string str)",
			"no operator between numbers", str.find("?"));
	return (1);
}

int	Parse::check_caret_base(std::string str, size_t i, size_t pos)
{
	if (i == 0
		|| !(std::isdigit(str[i - 1])
		|| is_element_of_set(this->_set_alphabet, str[i - 1])
		|| str[i - 1] == ')'))
		throw_err_msg("Parse::check_caret_base(std::string str, size_t i, size_t pos)",
			"incorrect location of caret(^): base is missed" , pos + i);
	return (1);
}

int	Parse::skip_caret_power(std::string str, size_t i)
{
	if (str[i] == '(')
	{
		i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
	}
	while (str[i] == '('
		|| std::isdigit(str[i])
		|| is_element_of_set(this->_set_alphabet, str[i])
		|| str[i] == ')' || str[i] == ']')
		i++;
	return (i);
}

int	Parse::check_caret_power(std::string str, size_t &i, size_t pos)
{
	if (i == str.length() - 1)
		throw_err_msg("Parse::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect location of caret(^): power is missed", pos + str.length() - 1);

	i++;
	i = skip_caret_power(str, i);
	if (str[i] == '\0')
		return (1);

	if (str[i - 1] == '^')
		throw_err_msg("Parse::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect location of caret(^): power is missed", pos + i - 1);
	if (str[i] == '^')
		throw_err_msg("Parse::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect use of caret(^): used multiple times", pos + i);
	if (!is_element_of_set(this->_set_operation, str[i]))
		throw_err_msg("Parse::check_caret_power(std::string str, size_t &i, size_t pos)",
			"incorrect power of caret(^): supports only int value for power", pos + i);
	return (1);
}

int	Parse::check_caret(int str_type, std::string str)
{
	size_t	pos = 0;
	size_t	i = 0;

	if (str.find("^") == std::string::npos)
		return (1);

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			if (str[i + 1] && str[i + 1] == '^')
				throw_err_msg("Parse::check_caret(std::string str)",
					"incorrect use of caret(^): used multiple times", pos + i + 1);
			if (!check_caret_base(str, i, pos))
				return (0);
			if (!check_caret_power(str, i, pos))
				return (0);
		}
		i++;
	}
	return (1);
}

int	Parse::check_brackets(int str_type, int bracket_type, std::string str)
{
	std::stack<char>	stack;
	char			bracket[2];
	size_t			pos = 0;
	size_t			i = 0;

	bracket[OPEN] = (bracket_type == ROUND_BRACKET) ? '(' : '[';
	bracket[CLOSE] = (bracket_type == ROUND_BRACKET) ? ')' : ']';

	if (str.find(std::string(1, bracket[CLOSE])) == std::string::npos
		&& str.find(std::string(1, bracket[OPEN])) == std::string::npos)
		return (1);

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;
	while (i < str.length())
	{
		if (str[i] == bracket[OPEN])
			stack.push(str[i]);
		if (str[i] == bracket[CLOSE])
		{
			
			if (str[i - 1] && str[i - 1] == bracket[OPEN])
				throw_err_msg("Parse::check_brackets(int str_type, int bracket_type, std::string str)",
					"incorrect use of brackets: no character in the brackets", pos + i);
			if (stack.empty())
				throw_err_msg("Parse::check_brackets(int str_type, int bracket_type, std::string str)",
					"incorrect use of brackets: bracket(s) not pair", pos + i);
			stack.pop();
		}
		i++;
	}
	if (!stack.empty())
		throw_err_msg("Parse::check_brackets(int str_type, int bracket_type, std::string str)",
			"incorrect use of brackets: bracket(s) not pair", pos + i - 1);
	return (1);
}

void	Parse::check_vector_str(int type, std::string str, size_t pos)
{
	if (str[0] == ',')
	{
		if (type == VECTOR)
			throw_err_msg("Parse::check_vector_str(int type, std::string str, size_t pos)",
				"invalid verctor form: invalid use of comma(,)", pos);
		else
			throw_err_msg("Parse::check_vector_str(int type, std::string str, size_t pos)",
				"invalid matrix form: invalid use of comma(,)", pos);
	}
	if (str[str.length() - 1] == ',')
	{
		if (type == VECTOR)
			throw_err_msg("Parse::check_vector_str(int type, std::string str, size_t pos)",
				"invalid verctor form: invalid use of comma(,)", pos + str.length() - 1);
		else
			throw_err_msg("Parse::check_vector_str(int type, std::string str, size_t pos)",
				"invalid matrix form: invalid use of comma(,)", pos + str.length() - 1);
	}
}

void	Parse::check_vector_element(int type, char c, size_t pos)
{
	if (!(is_element_of_set(this->_set_alphabet, c)
		|| is_element_of_set(this->_set_number, c)
		|| is_element_of_set(this->_set_operation, c)))
	{
		if (type == VECTOR)
			throw_err_msg("Parse::check_vector_element(int type, char c, size_t pos)",
				"invalid vector form: invalid character exists", pos);
		else
			throw_err_msg("Parse::check_vector_element(int type, char c, size_t pos)",
				"invalid matrix form: invalid character exists", pos);
	}
}

int	Parse::check_vector_form(int type, std::string str, size_t pos)
{
	std::vector<std::string>	vector;

	str = str.substr(1, str.length() - 2);
	pos++;
	check_vector_str(type, str, pos);

	vector = split(str, ',');
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == "")
		{
			if (type == VECTOR)
				throw_err_msg("Parse::check_vector_form(int type, std::string str, size_t pos)",
					"invalid vector form: invalid use of comma(,)", pos);
			else
				throw_err_msg("Parse::check_vector_form(int type, std::string str, size_t pos)",
					"invalid matrix form: invalid use of comma(,)", pos);
		}
		for (size_t j = 0; j < vector[i].length(); j++)
			check_vector_element(type, vector[i][j], pos + j);
		pos += vector[i].length();
		pos++;
	}
	return (vector.size());
}

void	Parse::check_matrix_str(std::string str, size_t pos)
{
	if (str[0] == ';')
		throw_err_msg("Parse::check_matrix_str(std::string str, size_t pos)",
			"invalid matrix form: invalid use of semi-colon(;)", pos);
	if (str[str.length() - 1] == ';')
		throw_err_msg("Parse::check_matrix_str(std::string str, size_t pos)",
			"invalid matrix form: invalid use of semi-colon(;)", pos + str.length() - 1);
}

void	Parse::check_matrix_row(std::string row, size_t pos)
{
	if (row[0] != '[')
		throw_err_msg("Parse::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid character exists", pos);
	if (row.find("[", 1) != std::string::npos)
		throw_err_msg("Parse::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid use of bracets", pos + row.find("[", 1));

	if (row[row.length() - 1] != ']')
		throw_err_msg("Parse::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid character exists", pos + row.length() - 1);
	if (row.find("]") != row.length() - 1)
		throw_err_msg("Parse::check_matrix_row(std::string row, size_t pos)",
			"invalid matrix form: invalid use of bracets", pos + row.find("]"));
}

void	Parse::check_matrix_column(std::string row, size_t i, size_t pos)
{
	int		col_size = 0;

	if (i == 0)
		col_size = check_vector_form(MATRIX, row, pos);
	else
	{
		if (col_size < 1 || col_size != check_vector_form(MATRIX, row, pos))
		{
			throw_err_msg("Parse::check_matrix_column(std::string row, size_t i, size_t pos)",
				"invalid matrix form: column size of each row should be same",
				pos + row.length() - 1);
		}
	}
}

int	Parse::check_matrix_form(std::string str, size_t pos)
{
	std::vector<std::string>	row;

	str = str.substr(1, str.length() - 2);
	pos++;
	check_matrix_str(str, pos);

	row = split(str, ';');
	for (size_t i = 0; i < row.size();i++)
	{
		if (row[i] == "")
			throw_err_msg("Parse::check_matrix_form(std::string str, size_t pos)",
					"invalid matrix form: invalid use of semi-colon(;)", pos);
		check_matrix_row(row[i], pos);
		check_matrix_column(row[i], i, pos);
		pos += row[i].length();
		pos++;
	}
	return (row.size());
}

int	Parse::skip_vector_matrix(std::string str, std::string &new_str, size_t i, size_t pos)
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
		if (!check_vector_form(VECTOR, bracket, pos))
			return (0);
	}
	else
	{
		if (!check_matrix_form(bracket, pos))
			return (0);
	}
	new_str += bracket;
	return (i++);
}

int	Parse::is_bracket_for_function(std::string str, size_t bracket_open_idx)
{
	if (str[bracket_open_idx] != '(' || bracket_open_idx == 0)
		return (0);
	if (is_element_of_set(this->_set_alphabet, str[bracket_open_idx - 1])
		&& str.find(')') != std::string::npos
		&& bracket_open_idx < str.find(")", bracket_open_idx + 1))
		return (1);
	return (0);
}

int	Parse::skip_function(std::string str, std::string &new_str, size_t i)
{
	new_str += str.substr(i, skip_bracket(ROUND_BRACKET, str, i) - i + 1);
	i = skip_bracket(ROUND_BRACKET,  str, i) + 1;
	return (i);
}

int	Parse::skip_vector_matrix_function(std::string str,
				std::string &new_str, size_t i, size_t pos)
{
	i = skip_vector_matrix(str, new_str, i, pos + i);
	if (!(is_element_of_set(this->_set_alphabet, str[i])
		|| is_element_of_set(this->_set_number, str[i])
		|| is_element_of_set(this->_set_operation, str[i])
		|| is_element_of_set(this->_set_other, str[i])
		|| str[i] == '\0'))
		throw_err_msg("Parse::skip_vector_matrix_function(std::string str, std::string &new_str, size_t i, size_t pos)",
			"invalid character exists", pos + i);
	if (str[i] == '(' && is_bracket_for_function(str, i))
		i = skip_function(str, new_str, i);
	return (i);
}

char	Parse::do_convert(std::string str, size_t &i)
{
	std::unordered_map<char, int> op = {{'+', OP_ADD}, {'-', OP_SUB},
					{'*', OP_MUL}, {'/', OP_DIV},
					{'%', OP_MODULO}, {'^', OP_POWER}};
	if (str[i] == '+' || str[i] == '-')
	{
		if (i > 1 && (str[i - 1] == '(' || str[i - 1] == '^'
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

void	Parse::convert_operator(int str_type, std::string &str)
{
	std::string	new_str = "";
	size_t		pos = 0;
	size_t		i = 0;

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	while (i < str.length())
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			new_str += str[i];

		i = skip_vector_matrix_function(str, new_str, i, pos);
		if (is_element_of_set(this->_set_operation, str[i]))
			new_str += do_convert(str, i);
		else
			new_str += str[i];
		i++;
	}
	str = new_str;
}

int	Parse::check_operator(int str_type, std::string str)
{
	std::string	sub_str = "";
	size_t		pos = 0;
	size_t		i = 0;

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;
	if (!(str_type == LEFT_STR || str_type == RIGHT_STR))
		pos = str_type;

	if (str[i] == '+' || str[i] == '-')
		i++;
	if (is_key_of_map(this->_operation, str[i]))
		throw_err_msg("Parse::check_operator(int str_type, std::string str)",
			"invalid use of operation: expect number before using operation", pos + i);
	if (is_key_of_map(this->_operation, str[str.length() - 1]))
		throw_err_msg("Parse::check_operator(int str_type, std::string str)",
			"invalid use of operation: expect number after using operation", pos + str.length() - 1);

	while (i < str.length())
	{
		if (str[i] == '(' && !is_bracket_for_function(str, i))
		{
			sub_str = str.substr(i + 1, skip_bracket(ROUND_BRACKET, str, i) - i - 1);
			check_operator(pos + i + 1, sub_str);
			i = skip_bracket(ROUND_BRACKET, str, i) + 1;
		}
		else if (is_key_of_map(this->_operation, str[i]))
		{
			if (str[i + 1] && is_key_of_map(this->_operation, str[i + 1]))
				throw_err_msg("Parse::check_operator(int str_type, std::string str)",
					"invalid use of operation: expect number before using operation", pos + i + 1);
		}
		i++;
	}
	return (1);
}

// int	Parse::check_operator_round_brackets(std::string str)
// {
// 	std::string	front;
// 	std::string	back;
// 	size_t		start;
// 	size_t		end;
// 	size_t		i;

// 	while (1)
// 	{
// 		if (str.find(")") == std::string::npos)
// 			return (1);
// 		i = 0;
// 		while (str[i] != ')')
// 			i++;
// 		end = i;
// 		while (str[i] != '(')
// 			i--;
// 		start = i;

// 		front = str.substr(0, start);
// 		back = str.substr(end + 1, std::string::npos);
// 		if ((front != "" && front[front.length() - 1] != '\0')
// 			&& !(front[front.length() - 1] == '('
// 				|| is_key_of_map(this->_operation, front[front.length() - 1])
// 				|| is_element_of_set(this->_set_operation, front[front.length() - 1])
// 				|| is_element_of_set(this->_set_alphabet, front[front.length() - 1])))
// 		{
// 			this->_err_msg = "invalid syntax: operator near round brackets";
// 			throw (this->_err_msg);
// 		}
// 		if ((back != "" && back[0] != '\0')
// 			&& !(back[0] == ')'
// 				|| is_key_of_map(this->_operation, back[0])
// 				|| is_element_of_set(this->_set_operation, back[0])))
// 		{
// 			this->_err_msg = "invalid syntax: operator near round brackets";
// 			throw (this->_err_msg);
// 		}
// 		str = front + "1" + back;
// 		continue ;
// 	}
// 	return (1);
// }

// int	Parse::check_operator_square_brackets(std::string str)
// {
// 	std::string	front;
// 	std::string	back;
// 	size_t		start;
// 	size_t		end;
// 	size_t		i;

// 	while (1)
// 	{
// 		if (str.find("[") == std::string::npos)
// 			return (1);
// 		i = 0;
// 		while (str[i] != '[')
// 			i++;
// 		start = i--;
// 		end = skip_bracket(SQUARE_BRACKET, str, i + 1);

// 		front = str.substr(0, start);
// 		back = str.substr(end + 1, std::string::npos);
// 		if ((front != "" && front[front.length() - 1] != '\0')
// 			&& !(front[front.length() - 1] == '('
// 				|| is_key_of_map(this->_operation, front[front.length() - 1])))
// 		{
// 			this->_err_msg = "invalid syntax: operator near square brackets";
// 			throw (this->_err_msg);
// 		}
// 		if ((back != "" && back[0] != '\0')
// 			&& !(back[0] == ')' || is_key_of_map(this->_operation, back[0])))
// 		{
// 			this->_err_msg = "invalid syntax: operator near square brackets";
// 			throw (this->_err_msg);
// 		}
// 		str = front + "1" + back;
// 		continue ;
// 	}
// 	return (1);
// }

int	Parse::check_syntax(std::string &str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_question_mark(str) 
		&& check_caret(LEFT_STR, left_str) && check_caret(RIGHT_STR, right_str)
		&& check_brackets(LEFT_STR, ROUND_BRACKET, left_str)
		&& check_brackets(RIGHT_STR, ROUND_BRACKET, right_str)
		&& check_brackets(LEFT_STR, SQUARE_BRACKET, left_str)
		&& check_brackets(RIGHT_STR, SQUARE_BRACKET, right_str)))
		return (0);

	convert_operator(LEFT_STR, left_str);
	convert_operator(RIGHT_STR, right_str);
	str = left_str + "=" + right_str;

	if (!(check_operator(LEFT_STR, left_str) && check_operator(RIGHT_STR, right_str)
		))
		return (0);
	// 	&& check_operator_round_brackets(left_str)
	// 	&& check_operator_round_brackets(right_str)
	// 	&& check_operator_square_brackets(left_str)
	// 	&& check_operator_square_brackets(right_str)))
	// 	return (0);

	// size_t	i = 0;
	// while (i < str.length())
	// {
	// 	str[i] = std::tolower(str[i]);
	// 	i++;
	// }
	//this->_str update
	return (1);
}

std::string	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return (str);
	if (!(is_equation_form(str) && check_invalid_character(str) && check_number(str)))
		return ("");

	convert_to_standard_form(str);
// ////////// remove later
// 	std::cout << "variable" << std::endl;
// 	if (this->_var.size() == 0)
// 	{
// 		std::cout << MAGENTA
// 			<< "there is no variable assigned yet" << BLACK << std::endl;
// 	}
// 	for (std::map<std::string, std::string>::iterator it = this->_var.begin();
// 		it != this->_var.end(); it++)
// 	{
// 		std::cout << YELLOW << it->first << BLACK << std::endl;
// 		std::cout << it->second;
// 		std::cout << std::endl
// 			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
// 	}
// 	std::cout << "function" << std::endl;
// 	if (this->_func.size() == 0)
// 	{
// 		std::cout << MAGENTA
// 			<< "there is no function assigned yet" << BLACK << std::endl;
// 	}
// 	for (std::map<std::string, std::string>::iterator it = this->_func.begin();
// 		it != this->_func.end(); it++)
// 	{
// 		std::cout << YELLOW << it->first << BLACK << std::endl;
// 		std::cout << it->second;
// 		std::cout << std::endl
// 			<< MAGENTA << "═══════════════════════" << BLACK << std::endl;
// 	}
// 	std::cout << "str before converting: " << str << std::endl;//
// ///////////
	// std::string	left_str = str.substr(0, str.find("="));
	// std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	// convert_val_func(left_str);
	// convert_val_func(right_str);
	// //calculate power
	// str = left_str + "=" + right_str;

// std::cout << "str after converting: " << str << std::endl;//

	if (!check_syntax(str))
		return ("");
	// std::cout << "---------------------parsing done" << std::endl;
	return (str);
}
