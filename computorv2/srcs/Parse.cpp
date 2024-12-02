/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:08:56 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/02 17:41:28 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _err_msg("")
{
	this->_valid_character = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k',
				'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				'w', 'x', 'y', 'z',
				'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
				'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
				'W', 'X', 'Y', 'Z',
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.',
				'(', ')', '[', ']', ',', ';', '=', '?',
				'+', '-', '*', '/', '%', '^', ' ', '\t'};
	this->_operation = {OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MODULO, OP_MAT_MUL};
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse&	Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_valid_character = parse._valid_character;
	this->_operation = parse._operation;
	this->_var = parse._var;
	this->_operation = parse._operation;
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

void	Parse::print_variant_value(V value)
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
		for (std::map<std::string, V>::iterator it = this->_var.begin();
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
		for (std::map<std::string, V>::iterator it = this->_var.begin();
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
			this->_err_msg = "equal(=) sign used multiple time";
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

int	Parse::is_element_of_set(std::unordered_set<char> set, char c)
{
	if (set.find(c) != set.end())
		return (1);
	return (0);
}

int	Parse::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!is_element_of_set(this->_valid_character, str[i]))
		{
			this->_err_msg = "invalid character exists";
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

std::vector<std::string>	Parse::split(std::string str, char delimeter)
{
	std::vector<std::string>	res;

	std::string			token;
	std::stringstream		ss(str);
	while (std::getline(ss, token, delimeter))
		res.push_back(token);
	return (res);
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

int	Parse::check_square_brackets(std::string str, std::string &new_str, size_t i)
{
	if (str[i] != '[')
		return (i);

	/* vector */
	if (str.find("[", i + 1) == std::string::npos
		|| str.find("]", i + 1) < str.find("[", i + 1))
	{
		if (!check_vector_form(VECTOR, str.substr(i, str.find("]", i) - i + 1)))
			return (0);
		new_str += str.substr(i, str.find("]", i) - i + 1);
		i = str.find("]", i) + 1;
	}
	/* matrix */
	else if (str.find("[", i + 1) != std::string::npos)
	{	
		size_t	j = str.find("[", i + 1);
		size_t	cnt = 1;

		while (0 < cnt && cnt <= 2 && j < str.length())
		{
			if (str[j] == '[')
				cnt++;
			else if (str[j] == ']')
				cnt--;
			if (cnt == 0)
				break ;
			j++;
		}
		if (cnt < 0 || cnt > 2)
		{
			this->_err_msg = "invalid syntax: matrix form";
			throw (this->_err_msg);
		}

		if (!check_matrix_form(str.substr(i, j - i + 1)))
			return (0);
		new_str += str.substr(i, j - i + 1);
		i = j + 1;
	}
	else
	{
		this->_err_msg = "invalid syntax: square brackets";
		throw (this->_err_msg);
	}
	return (i);
}

void	Parse::convert_operator(std::string &str)
{
	std::string	new_str = "";
	size_t		i = 0;

	while (i < str.size())
	{
		i = check_square_brackets(str, new_str, i);
		if (str[i] == '+' || str[i] == '-')
		{
			if (i == 0 || (str[i - 1] && (str[i - 1] == '(' 
					||str[i - 1] == '+' || str[i - 1] == '-'
					|| str[i - 1] == '*' || str[i - 1] == '/'
					|| str[i - 1] == '%')))
				new_str += str[i];
			else
			{
				if (str[i] == '+')
					new_str += OP_ADD;
				else
					new_str += OP_SUB;
			}
		}
		else if (str[i] == '*')
		{
			if (str[i + 1] && str[i + 1] == '*')
			{
				new_str += OP_MAT_MUL;
				i++;
			}
			else
				new_str += OP_MUL;
		}
		else if (str[i] == '/')
			new_str += OP_DIV;
		else if (str[i] == '%')
			new_str += OP_MODULO;
		else
			new_str += str[i];
		i++;
	}
	str = new_str;
}

int	Parse::check_bracket_pair(char *bracket, std::string str)
{
	size_t	open = 0;
	size_t	close = 0;
	size_t	i = 0;

	while (i < str.length())
	{
		if (str.find(std::string(1, bracket[CLOSE])) == std::string::npos)
		{
			if (str.find(std::string(1, bracket[OPEN])) != std::string::npos)
			{
				if (bracket[OPEN] == '(')
					this->_err_msg = "invalid syntax: round brackets";
				else
					this->_err_msg = "invalid syntax: square brackets";
				throw (this->_err_msg);
			}
			return (1);
		}
		if (str[i] == bracket[CLOSE])
		{
			close = i;
			if (str.substr(0, close).find(std::string(1, bracket[OPEN])) == std::string::npos)
			{
				if (bracket[OPEN] == '(')
					this->_err_msg = "invalid syntax: round brackets";
				else
					this->_err_msg = "invalid syntax: square brackets";
				throw (this->_err_msg);
			}
			while (str[i] != bracket[OPEN] && i > 0)
				i--;
			open = i;
			if (open + 1 == close)
			{
				if (bracket[OPEN] == '(')
					this->_err_msg = "invalid syntax: round brackets";
				else
					this->_err_msg = "invalid syntax: square brackets";
				throw (this->_err_msg);
			}
			str = str.substr(0, open)
				+ str.substr(open + 1, close - open - 1)
				+ str.substr(close + 1, std::string::npos);
			i = 0;
		}
		i++;
	}
	return (1);
}

int	Parse::check_brackets(int type, std::string str)
{
	char	bracket[2];

	if (type == ROUND_BRACKET)
	{
		bracket[OPEN] = '(';
		bracket[CLOSE] = ')';
	}
	else
	{
		bracket[OPEN] = '[';
		bracket[CLOSE] = ']';
	}

	if (!check_bracket_pair(bracket, str))
		return (0);
	return (1);
}

int	Parse::check_syntax(std::string &str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_brackets(ROUND_BRACKET, left_str)
		&& check_brackets(ROUND_BRACKET, right_str)
		&& check_brackets(SQUARE_BRACKET, left_str)
		&& check_brackets(SQUARE_BRACKET, right_str)))
		return (0);
	return (1);
}

int	Parse::check_str(std::string &str)
{
	if (check_keyword(str))
		return (1);
	if (!(is_equation_form(str) && check_invalid_character(str) && check_number(str)))
		return (0);

	remove_space(str);

	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	convert_operator(left_str);
	convert_operator(right_str);
	str = left_str + "=" + right_str;

	if (!check_syntax(str))
		return (0);
	return (1);
}
