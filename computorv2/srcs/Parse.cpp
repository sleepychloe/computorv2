/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/08 09:13:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _err_msg("")
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
	this->_set_alphabet = parse._set_alphabet;
	this->_set_number = parse._set_number;
	this->_set_vector_matrix = parse._set_vector_matrix;
	this->_set_operation = parse._set_operation;
	this->_set_other = parse._set_other;
	this->_set_space = parse._set_space;
	this->_operation = parse._operation;
	this->_err_msg = parse._err_msg;
	return (*this);
}

Parse::~Parse()
{
}

std::string	Parse::parse_start(std::string &str)
{
	return (check_str(str));
}

int	Parse::check_keyword(std::string str)
{
	if (str == "var" || str == "VAR"
		|| str == "vriable" || str == "VARIABLE")
	{
		return (1);
	}
	else if (str == "func" || str == "FUNC"
		|| str == "function" || str == "function")
	{
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
			if (str[i] == '(')
			{
				i++;
				if (str[i] == '+' || str[i] == '-')
					i++;
			}
			while (str[i] == '('
				|| std::isdigit(str[i]) || is_element_of_set(this->_set_alphabet, str[i])
				|| str[i] == ')')
				i++;
			if (str[i] == '\0')
				return (1);
			if (str[i - 1] == '^' || str[i] == '^' || !is_element_of_set(this->_set_operation, str[i]))
			{
				this->_err_msg = "invalid syntax: caret(^)";
				throw(this->_err_msg);
			}
		}
		i++;
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
	std::vector<std::string>	vector;

	str = str.substr(1, str.length() - 2);
	if (str[str.length() - 1] == ',')
	{
		if (type == VECTOR)
			this->_err_msg = "invalid syntax: vector form";
		else
			this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}
	vector = split(str, ',');

	if (!vector.size())
	{
		if (type == VECTOR)
			this->_err_msg = "invalid syntax: vector form";
		else
			this->_err_msg = "invalid syntax: matrix form";
		throw (this->_err_msg);
	}

	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i] == "")
		{
			if (type == VECTOR)
				this->_err_msg = "invalid syntax: vector form";
			else
				this->_err_msg = "invalid syntax: matrix form";
			throw (this->_err_msg);
		}
		for (size_t j = 0; j < vector[i].size(); j++)
		{
			if (!(vector[i][0] == '+' || vector[i][0] == '-'
				|| is_element_of_set(this->_set_number, vector[i][j])))
			{
				if (type == VECTOR)
					this->_err_msg = "invalid syntax: vector form";
				else
					this->_err_msg = "invalid syntax: matrix form";
				throw (this->_err_msg);
			}
		}
	}
	return (vector.size());
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
					{'*', OP_MUL}, {'/', OP_DIV},
					{'%', OP_MODULO}, {'^', OP_POWER}};
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
	std::string	sub_str = "";
	size_t		i = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;
	if (is_key_of_map(this->_operation, str[i])
		|| is_key_of_map(this->_operation, str[str.length() - 1]))
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
	}
	while (i < str.length())
	{
		if (str[i] == '(')
		{
			std::string sub_str = str.substr(i + 1, skip_bracket(ROUND_BRACKET, str, i) - i - 1);
			if (!check_operator(sub_str))
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
			i = skip_bracket(ROUND_BRACKET, str, i) + 1;
		}
		else if (is_key_of_map(this->_operation, str[i]))
		{
			if (str[i + 1] && is_key_of_map(this->_operation, str[i + 1]))
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_operator_round_brackets(std::string str)
{
	std::string	front;
	std::string	back;
	size_t		start;
	size_t		end;
	size_t		i;

	while (1)
	{
		if (str.find(")") == std::string::npos)
			return (1);
		i = 0;
		while (str[i] != ')')
			i++;
		end = i;
		while (str[i] != '(')
			i--;
		start = i;

		front = str.substr(0, start);
		back = str.substr(end + 1, std::string::npos);
		if ((front != "" && front[front.length() - 1] != '\0')
			&& !(front[front.length() - 1] == '('
				|| is_key_of_map(this->_operation, front[front.length() - 1])
				|| is_element_of_set(this->_set_alphabet, front[front.length() - 1])))
		{
			this->_err_msg = "invalid syntax: operator near round brackets";
			throw (this->_err_msg);
		}
		if ((back != "" && back[0] != '\0')
			&& !(back[0] == ')' || is_key_of_map(this->_operation, back[0])))
		{
			this->_err_msg = "invalid syntax: operator near round brackets";
			throw (this->_err_msg);
		}
		str = front + "1" + back;
		continue ;
	}
	return (1);
}

int	Parse::check_operator_square_brackets(std::string str)
{
	std::string	front;
	std::string	back;
	size_t		start;
	size_t		end;
	size_t		i;

	while (1)
	{
		if (str.find("[") == std::string::npos)
			return (1);
		i = 0;
		while (str[i] != '[')
			i++;
		start = i--;
		end = skip_bracket(SQUARE_BRACKET, str, i + 1);

		front = str.substr(0, start);
		back = str.substr(end + 1, std::string::npos);
		if ((front != "" && front[front.length() - 1] != '\0')
			&& !(front[front.length() - 1] == '('
				|| is_key_of_map(this->_operation, front[front.length() - 1])))
		{
			this->_err_msg = "invalid syntax: operator near square brackets";
			throw (this->_err_msg);
		}
		if ((back != "" && back[0] != '\0')
			&& !(back[0] == ')' || is_key_of_map(this->_operation, back[0])))
		{
			this->_err_msg = "invalid syntax: operator near square brackets";
			throw (this->_err_msg);
		}
		str = front + "1" + back;
		continue ;
	}
	return (1);
}

int	Parse::check_syntax(std::string &str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_question_mark(str) 
		&& check_caret(left_str) && check_caret(right_str)
		&& check_brackets(ROUND_BRACKET, left_str)
		&& check_brackets(ROUND_BRACKET, right_str)
		&& check_brackets(SQUARE_BRACKET, left_str)
		&& check_brackets(SQUARE_BRACKET, right_str)))
		return (0);

	convert_operator(left_str);
	convert_operator(right_str);
	str = left_str + "=" + right_str;

	if (!(check_operator(left_str) && check_operator(right_str)
		&& check_operator_round_brackets(left_str)
		&& check_operator_round_brackets(right_str)
		&& check_operator_square_brackets(left_str)
		&& check_operator_square_brackets(right_str)))
		return (0);

	size_t	i = 0;
	while (i < str.length())
	{
		str[i] = std::tolower(str[i]);
		i++;
	}
	return (1);
}

std::string	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return ("");
	if (!(is_equation_form(str) && check_invalid_character(str) && check_number(str)))
		return ("");

	remove_space(str);
	if (!check_syntax(str))
		return ("");
	return (str);
}
