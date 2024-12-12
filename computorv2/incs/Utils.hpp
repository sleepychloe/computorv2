/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:47:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/12 00:45:34 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>

int				is_element_of_set(std::unordered_set<char> set, char c);
int				is_key_of_map(std::unordered_map<int, std::string> map, char c);
int				is_key_of_map(std::map<std::string, std::string> map, std::string str);
std::vector<std::string>	split(std::string str, char delimeter);
int				check_round_brackets(std::string str);
std::string			get_function_name(std::string term);
std::string			get_function_variable(std::string term);

#endif
