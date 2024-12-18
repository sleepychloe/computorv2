/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:48:03 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/19 00:10:59 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Utils.hpp"

int	is_element_of_set(std::unordered_set<char> set, char c)
{
	if (set.find(c) != set.end())
		return (1);
	return (0);
}

int	is_key_of_map(std::unordered_map<int, std::string> map, char c)
{
	if (map.find(c) != map.end())
		return (1);
	return (0);
}

int	is_key_of_map(std::map<std::string, std::string> map, std::string str)
{
	if (map.find(str) != map.end())
		return (1);
	return (0);
}

std::vector<std::string>	split(std::string str, char delimeter)
{
	std::vector<std::string>	res;
	std::string			token;
	std::stringstream		ss(str);

	while (std::getline(ss, token, delimeter))
		res.push_back(token);
	return (res);
}

int	skip_bracket(int type, std::string str, size_t i)
{
	char			bracket[2];
	std::stack<char>	stack;

	bracket[OPEN] = (type == SQUARE_BRACKET) ? '[': '(';
	bracket[CLOSE] = (type == SQUARE_BRACKET) ? ']': ')';

	if (str[i] == bracket[OPEN])
		stack.push(str[i]);
	else
		return (i);
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

std::string	get_bracket_str(std::string str)
{
	size_t	start;
	size_t	end;
	size_t	i = 0;

	if (str.find("(") == std::string::npos
		&& str.find(")") == std::string::npos)
		return ("");

	while (str[i] != ')')
		i++;
	end = i;
	while (str[i] != '(')
		i--;
	start = i;
	return (str.substr(start, end - start + 1));
}

std::string	get_function_name(std::string term)
{
	return (term.substr(0, term.find("(")));
}

std::string	get_function_variable(std::string term)
{
	if (term[term.length() - 1] == '\0')
		term = term.substr(0, term.length() - 1);
	return (term.substr(term.find("(") + 1, term.length() - term.find("(") - 2));
}

int	is_bracket_for_function(std::string str, size_t bracket_open_idx)
{
	if (str[bracket_open_idx] != '(' || bracket_open_idx == 0)
		return (0);
	if (('a' <= str[bracket_open_idx - 1] && str[bracket_open_idx - 1] <= 'z')
		&& str.find(')') != std::string::npos
		&& bracket_open_idx < str.find(")", bracket_open_idx + 1))
		return (1);
	return (0);
}

std::string	revert_str(std::unordered_map<int, std::string> op, std::string str)
{
	std::string	new_str = "";

	for (size_t i = 0; i < str.length(); i++)
	{
		if (is_key_of_map(op, str[i]))
			new_str += op[str[i]];
		else
			new_str += str[i];
	}
	return (new_str);
}
