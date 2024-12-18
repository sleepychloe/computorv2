/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:47:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 20:48:44 by yhwang           ###   ########.fr       */
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
#include "./Define.hpp"

int				is_element_of_set(std::unordered_set<char> set, char c);
int				is_key_of_map(std::unordered_map<int, std::string> map, char c);
int				is_key_of_map(std::map<std::string, std::string> map, std::string str);
std::vector<std::string>	split(std::string str, char delimeter);
int				skip_bracket(int type, std::string str, size_t i);
std::string			get_function_name(std::string term);
std::string			get_function_variable(std::string term);
std::string			get_bracket_str(std::string str);
int				is_bracket_for_function(std::string str, size_t bracket_open_idx);
std::string			revert_str(std::unordered_map<int, std::string> op, std::string str);

#endif
