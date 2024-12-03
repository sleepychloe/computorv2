/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:47:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/03 13:52:02 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

int		is_element_of_set(std::unordered_set<char> set, char c);
std::vector<std::string>	split(std::string str, char delimeter);

#endif
