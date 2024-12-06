/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:48:03 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/06 14:45:23 by yhwang           ###   ########.fr       */
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
	if (map.count(c))
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