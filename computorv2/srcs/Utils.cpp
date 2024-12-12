/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:48:03 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/12 12:31:59 by yhwang           ###   ########.fr       */
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

int	check_round_brackets(std::string str)
{
	std::stack<char>	stack;
	int			cnt = 0;
	size_t			i = 0;

	if (str.find(std::string(1, ')')) == std::string::npos
		&& str.find(std::string(1, '(')) == std::string::npos)
		return (0);

	while (i < str.length())
	{
		if (str[i] == '(')
		{
			stack.push(str[i]);
			cnt++;
		}
		if (str[i] == ')')
		{
			if ((str[i - 1] && str[i - 1] == '(')
				|| stack.empty())
				return (0);
			stack.pop();
		}
		i++;
	}
	if (!stack.empty())
		return (0);
	return (cnt);
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
