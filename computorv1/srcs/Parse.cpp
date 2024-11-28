
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/20 11:34:55 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _variable(0), _max_degree(0), _equation_type(0),
		_flag_bonus(0), _equation_str(""), _err_msg("")
{
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_variable = parse._variable;
	this->_reduced_form = parse._reduced_form;
	this->_degree = parse._degree;
	this->_max_degree = parse._max_degree;
	this->_equation_type = parse._equation_type;
	this->_flag_bonus = parse._flag_bonus;
	this->_equation_str = parse._equation_str;
	this->_err_msg = parse._err_msg;
	return (*this);
}

Parse::~Parse()
{
}

char	Parse::get_variable(void)
{
	return (this->_variable);
}

std::vector<float>	Parse::get_reduced_form(void)
{
	return (this->_reduced_form);
}

std::vector<float>	Parse::get_degree(void)
{
	return (this->_degree);
}

int	Parse::get_equation_type(void)
{
	return (this->_equation_type);
}

int	Parse::get_flag_bonus(void)
{
	return (this->_flag_bonus);
}

std::string	Parse::get_equation_str(void)
{
	return (this->_equation_str);
}

void	Parse::parse_start(char *argv, int flag_bonus)
{
	std::string	str(argv);

	this->_flag_bonus = flag_bonus;
	check_str(str);
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

int	Parse::check_variable(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))
		{
			this->_variable = str[i];
			break ;
		}
		i++;
	}
	if (this->_variable == 0)
	{
		this->_err_msg = "cannot determine the variable";
		throw (this->_err_msg);
	}

	i = 0;
	while (i < str.length())
	{
		if (str[i] == this->_variable)
		{
			i++;
			if (str[i] == this->_variable)
			{
				this->_err_msg = "inappropriate variable form";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(str[i] == this->_variable || ('0' <= str[i] && str[i] <= '9')
			|| str[i] == '.' || str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '=' || str[i] == ' ' || str[i] == '\t'))
		{
			this->_err_msg = "cannot determine the variable";
			throw (this->_err_msg);
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
	return (1);
}

void	Parse::remove_space(std::string	&str)
{
	size_t		i = 0;
	std::string	new_str = "";

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (i < str.size())
	{
		if (str[i] != ' ' && str[i] != '\t')
			new_str += str[i];
		i++;
	}
	str = new_str;
}

int	Parse::check_brackets(std::string str)
{
	int	open = 0;
	int	close = 0;
	int	cnt_open = 0;
	int	cnt_close = 0;

	size_t	i = 0;
	while (i < str.length())
	{
		if (str[i] == '(')
			cnt_open++;
		if (str[i] == ')')
			cnt_close++;
		i++;
	}
	if (cnt_open != cnt_close)
	{
		this->_err_msg = "invalid syntax: brackets";
		throw (this->_err_msg);
	}

	i = 0;
	while (i < str.length())
	{
		if (str.find(")") == std::string::npos)
			break ;
		if (str[i] == ')')
		{
			close = i;
			if (str.substr(0, close).find("(") == std::string::npos)
				break ;
			while (str[i] != '(' && i > 0)
				i--;
			open = i;
			str = str.substr(0, open)
				+ str.substr(open + 1, close - open - 1)
				+ str.substr(close + 1, std::string::npos);
			i = 0;
		}
		i++;
	}

	i = 0;
	while (i < str.length())
	{
		if (str[i] == '(' || str[i] == ')')
		{
			this->_err_msg = "invalid syntax: brackets";
			throw (this->_err_msg);
		}
		i++;
	}
	return (1);
}

int	Parse::check_sign(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	if (str[0] == '*' || str[0] == '/'
		|| str[str.length() - 1] == '+' || str[str.length() - 1] == '-'
		|| str[str.length() - 1] == '*' || str[str.length() - 1] == '/')
	{
		this->_err_msg = "invalid syntax: operator";
			throw (this->_err_msg);
	}

	i = 0;
	while (str[i] == '+' || str[i] == '-' || str[i] == '(')
		i++;
	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			while (str[i] == this->_variable || str[i] == '^'
				|| ('0' <= str[i] && str[i] <= '9') || str[i] == '.'
				|| str[i] == '+' || str[i] == '-'
				|| str[i] == '(' || str[i] == ')')
				i++;
			if (!(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
				|| str[i] == '\0'))
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}

	i = 0;
	while (i < str.length())
	{
		if (str[i] == this->_variable)
		{
			i++;
			if (str[i] == this->_variable)
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}

	i = 0;
	while (i < str.length())
	{
		if (str[i] == ')' && str[i + 1] && str[i + 1] == '(')
		{
			this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
		}
		i++;
	}
	return (1);
}

int	Parse::check_point(std::string str)
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
					if (digit > 2)
						this->_err_msg += ": supports up to the fifth decimal place";
					throw (this->_err_msg);
				}
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_caret(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			if (!(str[i - 1] && (str[i - 1] == this->_variable)
				&& (str[i + 1] && '0' <= str[i + 1] && str[i + 1] <= '9')))
			{
				this->_err_msg = "invalid syntax: caret(^)";
				throw (this->_err_msg);
			}
			i++;
			if ('0' <= str[i] && str[i] <= '9')
			{
				while ('0' <= str[i] && str[i] <= '9')
					i++;
				if (!(str[i] == '+' || str[i] == '-'
					|| str[i] == '*' || str[i] == '/' || str[i] == '=' || str[i] == '\0'))
				{
					this->_err_msg = "invalid syntax: caret(^)";
					throw (this->_err_msg);
				}
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_syntax(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_brackets(left_str) && check_brackets(right_str)
		&& check_sign(left_str) && check_sign(right_str)
		&& check_point(str) && check_caret(str)))
		return (0);
	return (1);
}

void	Parse::remove_bracket_without_calc(std::string &str,
				std::vector<std::string> &s)
{
	if (s[FRONT][s[FRONT].length() - 1] == '+')
	{
		if (s[BRACKET][0] == '+')
			s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
		else if (s[BRACKET][0] == '-')
			s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
	}
	else if (s[FRONT][s[FRONT].length() - 1] == '-')
	{
		if (s[BRACKET][0] == '+')
			s[BRACKET] = s[BRACKET].substr(1, std::string::npos);
		else if (s[BRACKET][0] == '-')
		{
			s[BRACKET] = s[BRACKET].substr(1, std::string::npos);
			s[FRONT][s[FRONT].length() - 1] = '+';
		}
	}
	str = s[FRONT] + s[BRACKET] + s[BACK];
}

int	Parse::find_next_bracket(std::vector<size_t> &i,
				std::vector<std::string> &s)
{
	i[KEEP] = 0;
	if (s[BACK] == "")
		return (0);
	while (s[BACK][i[KEEP]] != ')' && s[BACK][i[KEEP]] != '\0')
		i[KEEP]++;
	if (s[BACK][i[KEEP]] == '\0')
		return (0);
	i[END] = s[FRONT].length() + s[BRACKET].length() + 2 + s[BACK].find(")");
	i[END]--;
	return (1);
}

void	Parse::remove_bracket_one_term(std::string &str)
{
	std::vector<size_t>		i(3, 0);
	std::vector<std::string>	s(3, "");
	std::vector<std::string>	tmp_term;

	while (1)
	{
		if (str[i[END]] == '\0' || str.find(")") == std::string::npos)
			break ;
		while (str[i[END]] != ')' && str[i[END]] != '\0')
			i[END]++;
		if (str[i[END]] == '\0')
			break ;
		i[START] = i[END];
		while (str[i[START]] != '(')
			i[START]--;
		s[FRONT] = str.substr(0, i[START]);
		s[BRACKET] = str.substr(i[START] + 1, i[END] - i[START] - 1);
		s[BACK] = str.substr(i[END] + 1, std::string::npos);
		if (s[BRACKET] == "")
		{
			this->_err_msg = "invalid syntax: brackets";
			throw (this->_err_msg);
		}

		tmp_term = split_term(s[BRACKET]);
		if (tmp_term.size() == 1)
		{
			remove_bracket_without_calc(str, s);
			i[END] = 0;
		}
		else
		{
			if (!find_next_bracket(i, s))
				break ;
		}
		tmp_term.clear();
		i[END]++;
	}
}

void	Parse::check_front_str(std::vector<size_t> &i, std::vector<std::string> &s)
{
	if (s[FRONT].length() >= 2 && s[FRONT][s[FRONT].length() - 1] == '('
		&& !(s[FRONT][s[FRONT].length() - 2] == '+'
			|| s[FRONT][s[FRONT].length() - 2] == '-'
			|| s[FRONT][s[FRONT].length() - 2] == '*'
			|| s[FRONT][s[FRONT].length() - 2] == '/'
			|| s[FRONT][s[FRONT].length() - 2] == '('))
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
	}

	if (s[FRONT].length() >= 2 && ((s[FRONT][s[FRONT].length() - 1] == '('
		&& (s[FRONT][s[FRONT].length() - 2] == '-'
			|| s[FRONT][s[FRONT].length() - 2] == '+'))))
	{
		if (i[START] != 0)
			i[START]--;
		s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
		if (s[FRONT][s[FRONT].length() - 1] == '-'
			|| s[FRONT][s[FRONT].length() - 1] == '+')
		{
			s[FRONT] = s[FRONT] + "1*";
			i[START] = i[START] + 2;
		}
	}
	else
		s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
}

void	Parse::apply_operation_from_front(std::string &tmp,
				std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	nb = "0";
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	if (!get_term(tmp, tmp_term_degree))
	{
		this->_err_msg = "cannot seperate the terms";
		throw (this->_err_msg);
	}
	if (s[FRONT][i[KEEP] + 1] == '*')
	{
		term_degree.first.clear();
		term_degree.second.clear();
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < keep_term_degree.first.size(); j++)
			{
				term_degree.first.push_back(float_to_string(atof(keep_term_degree.first[j].c_str())
										* atof(tmp_term_degree.first[k].c_str())));
				term_degree.second.push_back(tmp_term_degree.second[k]
								+ keep_term_degree.second[j]);
			}
		}
	}
	else
	{
		for (size_t k = 0; k < term_degree.second.size(); k++)
		{
			if (term_degree.second[k] > 0)
			{
				this->_err_msg = "this program does not support to calculate expression containing variable in fraction";
				throw (this->_err_msg);
			}
			nb = float_to_string(atof(nb.c_str()) + atof(term_degree.first[k].c_str()));
		}
		if (atof(nb.c_str()) == 0)
		{
			this->_err_msg = "cannot divided by 0";
			throw (this->_err_msg);
		}

		term_degree.first.clear();
		term_degree.second.clear();
		term_degree.second = tmp_term_degree.second;
		for (size_t j = 0; j < tmp_term_degree.first.size(); j++)
			term_degree.first.push_back(float_to_string(atof(tmp_term_degree.first[j].c_str()) / atof(nb.c_str())));
	}
}

void	Parse::find_mul_dev_front_str(std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	tmp = "";
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	check_front_str(i, s);

	i[START] = s[FRONT].length() - 1;
	while (s[FRONT].length() >= 1 && s[FRONT][i[START]] != '\0'
		&& (s[FRONT][i[START]] == '*' || s[FRONT][i[START]] == '/'))
	{
		i[START]--;
		i[KEEP] = i[START];
		while ((s[FRONT][i[START]] != '\0'
			&& '0' <= s[FRONT][i[START]] && s[FRONT][i[START]] <= '9')
				|| s[FRONT][i[START]] == '.'
				|| s[FRONT][i[START]] == this->_variable || s[FRONT][i[START]] == '^')
			i[START]--;
		if (s[FRONT][i[START]] != '\0'
			&& (s[FRONT][i[START]] == '+' || s[FRONT][i[START]] == '-'))
			i[START]--;
		tmp = s[FRONT].substr(i[START] + 1, i[KEEP] - i[START]);
		apply_operation_from_front(tmp, i, s, term_degree);
		s[FRONT] = s[FRONT].substr(0, i[START] + 1);
		i[START] = s[FRONT].length() - 1;
	}
}

void	Parse::apply_operation_from_back(std::string &tmp,
				std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	if (!get_term(tmp, tmp_term_degree))
	{
		this->_err_msg = "cannot seperate the terms";
		throw (this->_err_msg);
	}
	if (s[BACK][i[KEEP] - 1] == '*')
	{
		term_degree.first.clear();
		term_degree.second.clear();
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < keep_term_degree.first.size(); j++)
			{
				term_degree.first.push_back(float_to_string(atof(keep_term_degree.first[j].c_str())
										* atof(tmp_term_degree.first[k].c_str())));
				term_degree.second.push_back(tmp_term_degree.second[k]
								+ keep_term_degree.second[j]);
			}
		}
	}
	else
	{
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			if (tmp_term_degree.second[k] > 0)
			{
				this->_err_msg = "this program does not support to calculate expression containing variable in fraction";
				throw (this->_err_msg);
			}
			if (k > 0)
				tmp_term_degree.first[0] = float_to_string(atof(tmp_term_degree.first[0].c_str())
								+ atof(tmp_term_degree.first[k].c_str()));
		}
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < term_degree.first.size(); j++)
			{
				if (atof(tmp_term_degree.first[0].c_str()) == 0)
				{
					this->_err_msg = "cannot divided by 0";
					throw (this->_err_msg);
				}
				term_degree.first[j] = float_to_string(atof(term_degree.first[j].c_str())
								/ atof(tmp_term_degree.first[0].c_str()));
			}
		}
	}
}

void	Parse::find_mul_dev_back_str(std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	tmp = "";

	i[END] = 0;
	if (s[BACK][i[END]] != '\0'
		&& !(s[BACK][i[END]] == '+' || s[BACK][i[END]] == '-'
			|| s[BACK][i[END]] == '*' || s[BACK][i[END]] == '/'
			|| s[BACK][i[END]] == ')'))
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
	}

	while (s[BACK][i[END]] != '\0'
		&& (s[BACK][i[END]] == '*' || s[BACK][i[END]] == '/'))
	{
		if (s[BACK][i[END] + 1] != '\0' && s[BACK][i[END] + 1] == '(')
		{
			i[END]++;
			i[KEEP] = i[END];
			tmp = s[BACK].substr(2, s[BACK].find(")") - 2);
			apply_operation_from_back(tmp, i, s, term_degree);
			s[BACK] = s[BACK].substr(s[BACK].find(")") + 1, std::string::npos);
			i[END] = 0;
		}
		else
		{
			i[END]++;
			i[KEEP] = i[END];
			if (s[BACK][i[END]] == '+' || s[BACK][i[END]] == '-')
				i[END]++;
			while ((s[BACK][i[END]] != '\0'
				&& '0' <= s[BACK][i[END]] && s[BACK][i[END]] <= '9')
					|| s[BACK][i[END]] == '.'
					|| s[BACK][i[END]] == this->_variable || s[BACK][i[END]] == '^')
				i[END]++;
			tmp = s[BACK].substr(i[KEEP], i[END] - i[KEEP]);
			apply_operation_from_back(tmp, i, s, term_degree);
			s[BACK] = s[BACK].substr(i[END] - i[KEEP] + 1, std::string::npos);
			i[END] = 0;
		}
	}
}

void	Parse::get_bracket_str(std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::vector<float>	term_float;

	for (size_t i = 0; i < term_degree.first.size();i++)
		term_float.push_back(atof(term_degree.first[i].c_str()));
	s[BRACKET] = "";
	for (size_t i = 0; i < term_float.size(); i++)
	{
		if (term_float[i] >= 0)
			s[BRACKET] += "+";
		s[BRACKET] += float_to_string(term_float[i]);
		if (term_degree.second[i] > 0)
		{
			s[BRACKET] += "*" + std::string(1, this->_variable) + "^";
			s[BRACKET] += float_to_string(term_degree.second[i]);
		}
	}
}

void	Parse::remove_bracket_multiple_term(std::string &str)
{
	std::vector<size_t>		i(3, 0);
	std::vector<std::string>	s(3, "");

	std::pair<std::vector<std::string>, std::vector<float>>	term_degree;

	while (1)
	{
		if (str[i[END]] == '\0' || str.find(")") == std::string::npos)
			break ;
		while (str[i[END]] != ')' && str[i[END]] != '\0')
			i[END]++;
		if (str[i[END]] == '\0')
			break ;
		i[START] = i[END];
		while (str[i[START]] != '(')
			i[START]--;
		s[FRONT] = str.substr(0, i[START] + 1);
		s[BRACKET] = str.substr(i[START] + 1, i[END] - i[START] - 1);
		s[BACK] = str.substr(i[END] + 1, std::string::npos);
		if (s[BRACKET] == "")
		{
			this->_err_msg = "invalid syntax: brackets";
			throw (this->_err_msg);
		}
		if (!(get_term(s[BRACKET], term_degree)))
		{
			this->_err_msg = "cannot seperate the terms";
			throw (this->_err_msg);
		}

		find_mul_dev_front_str(i, s, term_degree);
		find_mul_dev_back_str(i, s, term_degree);
		get_bracket_str(s, term_degree);

		term_degree.first.clear();
		term_degree.second.clear();
		str = s[FRONT] + s[BRACKET] + s[BACK];
	}
}

int	Parse::remove_bracket(std::string &str)
{	
	remove_bracket_one_term(str);
	remove_bracket_multiple_term(str);
	return (1);
}

std::vector<std::string>	Parse::split_term(std::string str)
{
	std::vector<std::string>	term;
	size_t				i = 0;
	std::string			tmp;

	while (1)
	{
		i = 0;
		if (str[0] == '+' || str[0] == '-')
			i++;
		while (str[i] != '+' && str[i] != '-' && str[i] != '\0')
		{
			if ((str[i] == '*' || str[i] == '/')
				&& (str[i + 1]) && (str[i + 1] == '+' || str[i + 1] == '-'))
				i = i + 2;
			if (str[i] == '^')
			{
				if (str[i + 1] && (str[i + 1] == '+' || str[i + 1] == '-'))
					i = i + 2;
			}
			tmp = "";
			i++;
		}
		term.push_back(str.substr(0, i));
		if (i == str.length())
			break ;
		str = str.substr(i, std::string::npos);
	}
	return (term);
}

float	Parse::find_degree(std::string str)
{
	float	degree = 0;
	int	sign = 1;
	size_t	i = 0;
	size_t	tmp;

	while (i < str.length())
	{
		if (str[i] == '*')
			sign = 1;
		else if (str[i] == '/')
			sign = -1;

		if (str[i] == this->_variable
			&& str[i + 1] && str[i + 1] == '^')
		{
			i = i + 2;
			tmp = i;
			while ('0' <= str[i] && str[i] <= '9')
				i++;
			degree += sign * atof(str.substr(tmp, i - tmp).c_str());
		}
		else if (str[i] == this->_variable)
			degree += sign * 1;
		i++;
	}
	return (degree);
}

void	Parse::add_coefficient_of_variable(std::string &str)
{
	size_t		i = 0;
	std::string	tmp;

	while (i < str.length())
	{
		if (str[i] == this->_variable)
		{
			if (i == 0)
			{
				str = "1*" + str;
				i = i + 2;
			}
			if (i != 0 && (str[i - 1] == '+' || str[i - 1] == '-'))
			{
				tmp = "1*" + std::string(1, this->_variable);
				if (str[i - 1] == '-')
					tmp = "-1*" + std::string(1, this->_variable);
				str = str.substr(0, i - 1) + tmp + str.substr(i + 1, std::string::npos);
				i = str.substr(0, i).length() + tmp.length();
			}
		}
		i++;
	}
}

int	Parse::remove_variable(std::string &str)
{
	size_t		i = 0;
	size_t		start;
	size_t		end;
	std::string	tmp;

	add_coefficient_of_variable(str);

	while (i < str.length())
	{
		tmp = "";
		if ((str[i] == this->_variable)
			|| (str[i] == this->_variable && str[i + 1] && str[i + 1] == '^'))
		{
			start = i;
			i++;
			if (str[i] == '^')
				i++;
			while ('0' <= str[i] && str[i] <= '9')
				i++;
			end = i - 1;
			if (!(str[start - 1] == '*' || str[start - 1] == '/'))
				tmp += "*";
			tmp += "1";
			if (str[end + 1] && !(str[end + 1] == '*' || str[end + 1] == '/'))
				tmp += "*";
			str = str.substr(0, start) + tmp + str.substr(end + 1, std::string::npos);
			i = str.substr(0, start).length() + tmp.length();
		}
		i++;
	}
	return (1);
}

int	Parse::check_operation(std::string str)
{
	size_t	i = 0;
	size_t	cnt = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;

	while (i < str.length())
	{
		if (i != 0 && (str[i - 1] == '*' || str[i - 1] == '/')
			&& (str[i] == '+' || str[i] == '-'))
			i++;
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			cnt++;
		i++;
	}
	if (!cnt)
		return (0);
	return (1);
}

void	Parse::split_expression(std::string str,
				std::vector<float> &nb, std::vector<char> &op)
{
	size_t		i = 0;
	std::string	tmp = "";

	while (i < str.length())
	{
		if ((str[i] == '+' || str[i] == '-'))
			tmp += str[i];
		while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
		{
			tmp += str[i];
			i++;
		}
		if ((i > 0 && str[i - 1] != '*' && str[i - 1] != '/'
			&& (str[i] == '+' || str[i] == '-'))
			|| str[i] == '*' || str[i] == '/')
		{
			nb.push_back(atof(tmp.c_str()));
			op.push_back(str[i]);
			tmp = "";
		}
		i++;
	}
	nb.push_back(atof(tmp.c_str()));
}

float	Parse::calc(float nb1, float nb2, char op)
{
	float	res;

	if (op == '+')
		res = nb1 + nb2;
	else if (op == '-')
		res = nb1 - nb2;
	else if (op == '*')
		res = nb1 * nb2;
	else
	{
		if (nb2 == 0)
		{
			this->_err_msg = "cannot divided by 0";
			throw (this->_err_msg);
		}
		res = nb1 / nb2;
	}
	return (res);
}

std::string	Parse::calculate(std::string str)
{
	if (!check_operation(str))
	{
		if (str[0] == '+')
			str = str.substr(1, std::string::npos);
		return (str);
	}

	std::vector<float>	nb;
	std::vector<char>	op;

	split_expression(str, nb, op);

	size_t		i = 0;

	while (i < op.size())
	{
		if (op[i] == '*' || op[i] == '/')
		{
			nb[i] = calc(nb[i], nb[i + 1], op[i]);
			op.erase(op.begin() + i);
			nb.erase(nb.begin() + i + 1);
			i--;
		}
		i++;
	}

	i = 0;
	while (i < op.size())
	{
		if (op[i] == '+' || op[i] == '-')
		{
			nb[i] = calc(nb[i], nb[i + 1], op[i]);
			op.erase(op.begin() + i);
			nb.erase(nb.begin() + i + 1);
			i--;
		}
		i++;
	}
	return (float_to_string(nb[0]));
}

std::string	Parse::float_to_string(float num)
{
	std::stringstream	ss;

	ss << num;
	return (ss.str());
}

int	Parse::get_term(std::string str,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	term_degree.first = split_term(str);
	for (size_t i = 0; i < term_degree.first.size(); i++)
		term_degree.second.push_back(find_degree(term_degree.first[i]));
	for (std::vector<std::string>::iterator it = term_degree.first.begin();
		it != term_degree.first.end(); it++)
	{
		if (!remove_variable(*it))
			return (0);
	}
	for (size_t i = 0; i < term_degree.first.size(); i++)
		term_degree.first[i] = calculate(term_degree.first[i]);

	for (size_t i = 0; i < term_degree.first.size(); i++)
	{
		for (size_t start = i + 1; start < term_degree.first.size(); start++)
		{
			if (term_degree.second[i] == term_degree.second[start])
			{
				term_degree.first[i]
					= float_to_string(atof(term_degree.first[i].c_str())
							+ atof(term_degree.first[start].c_str()));
				term_degree.first.erase(term_degree.first.begin() + start);
				term_degree.second.erase(term_degree.second.begin() + start);
				start--;
			}
		}
	}
	return (1);
}

void	Parse::set_equation_type(void)
{
	for (size_t i = 0; i < this->_degree.size(); i++)
	{
		if (this->_degree[i] < 0)
		{
			this->_equation_type = TYPE_FRACTIONAL;
			return ;
		}
	}

	int	max;

	if (this->_degree.size() == 0 && this->_reduced_form.size() == 0)
	{
		this->_equation_type = TYPE_ZERO;
		return ;
	}
	max = this->_degree[0];
	for (size_t i = 1; i < this->_degree.size(); i++)
	{
		if (max < this->_degree[i])
			max = this->_degree[i];
	}
	this->_max_degree = max;
	if (max > 2)
		this->_equation_type = TYPE_HIGH_DEGREE;
	else
		this->_equation_type = max;
}

void	Parse::make_form_ascending_order(void)
{
	if (this->_equation_type == TYPE_ZERO)
	{
		std::vector<float>	form(1, 0);
		std::vector<float>	degree(1, 0);

		if (this->_reduced_form.size() != 0)
			form[0] = this->_reduced_form[0];
		this->_reduced_form = form;
		this->_degree = degree;
	}
	else if (this->_equation_type != TYPE_FRACTIONAL)
	{
		std::vector<float>	form(this->_max_degree + 1, 0);
		std::vector<float>	degree(this->_max_degree + 1, 0);

		for (size_t i = 0; i < form.size(); i++)
		{
			for (size_t j = 0; j < this->_degree.size(); j++)
			{
				if (this->_degree[j] == i)
					form[i] = this->_reduced_form[j];
			}
			degree[i] = i;
		}
		this->_reduced_form = form;
		this->_degree = degree;
	}
	else
	{
		for (size_t i = 0; i < this->_degree.size(); i++)
		{
			for (size_t j = i + 1; j < this->_degree.size(); j++)
			{
				if (this->_degree[i] > this->_degree[j])
				{
					std::swap(this->_degree[i], this->_degree[j]);
					std::swap(this->_reduced_form[i], this->_reduced_form[j]);
				}
			}
		}
	}
}

void	Parse::set_equation_str(void)
{
	std::string	str  = "";
	if (this->_equation_type == TYPE_ZERO)
	{
		this->_equation_str = float_to_string(this->_reduced_form[0]) + " = 0";
		return ;
	}
	if (!this->_flag_bonus)
	{
		for (size_t i = 0; i < this->_reduced_form.size(); i++)
		{
			if (this->_reduced_form[i] < 0)
				str += "- ";
			else
				str += "+ ";

			if (this->_reduced_form[i] != 0)
				str += float_to_string(std::abs(this->_reduced_form[i]));
			else
				str += "0";
			str += " * " + std::string(1, this->_variable);
			str += "^";
			str += float_to_string(this->_degree[i]);
			str += " ";
		}
		str += "= 0";
	}
	else
	{
		for (size_t i = 0; i < this->_reduced_form.size(); i++)
		{
			if (this->_reduced_form[i] != 0)
			{
				if (this->_reduced_form[i] < 0)
					str += "- ";
				else
					str += "+ ";

				str += float_to_string(std::abs(this->_reduced_form[i]));
				str += " ";
				if (this->_degree[i] != 0)
				{
					str += "* " + std::string(1, this->_variable);
					if  (this->_degree[i] != 1)
					{
						str += "^";
						str += float_to_string(this->_degree[i]);
					}
					str += " ";
				}
			}
		}
		str += "= 0";
	}

	size_t	i = 0;

	while (!(('0' <= str[i] && str[i] <= '9') || str[i] == '-'))
		i++;
	str = str.substr(i, std::string::npos);
	this->_equation_str = str;
}

void	Parse::make_reduced_form(void)
{
	for (size_t i = 0; i < this->_reduced_form.size(); i++)
	{
		for (size_t j = i + 1; j < this->_reduced_form.size(); j++)
		{
			if (this->_degree[i] == this->_degree[j])
			{
				this->_reduced_form[i]
					= this->_reduced_form[i] + this->_reduced_form[j];
				this->_reduced_form[j] = 0;
			}
		}
		if (this->_reduced_form[i] == 0)
		{
			this->_reduced_form.erase(this->_reduced_form.begin() + i);
			this->_degree.erase(this->_degree.begin() + i);
			i--;
		}
	}
	set_equation_type();
	make_form_ascending_order();
	set_equation_str();
}

int	Parse::check_str(std::string str)
{
	if (!(is_equation_form(str) && check_variable(str)
		&& check_invalid_character(str) && check_number(str)))
		return (0);

	remove_space(str);
	if (!check_syntax(str))
		return (0);

	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(remove_bracket(left_str) && remove_bracket(right_str)))
		return (0);

	str = left_str + "=" + right_str;

	std::pair<std::vector<std::string>, std::vector<float>>	l_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>>	r_term_degree;

	if (!(get_term(str.substr(0, str.find("=")), l_term_degree)
		&& get_term(str.substr(str.find("=") + 1, std::string::npos), r_term_degree)))
		return (0);

	for (size_t i = 0; i < l_term_degree.first.size(); i++)
	{
		this->_reduced_form.push_back(atof(l_term_degree.first[i].c_str()));
		this->_degree.push_back(l_term_degree.second[i]);
	}
	for (size_t i = 0; i < r_term_degree.first.size(); i++)
	{
		this->_reduced_form.push_back(-1 * atof(r_term_degree.first[i].c_str()));
		this->_degree.push_back(r_term_degree.second[i]);
	}

	make_reduced_form();
	return (1);
}
