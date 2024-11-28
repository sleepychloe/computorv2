/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadLine.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:40:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/28 18:27:19 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_HPP
# define READ_LINE_HPP

#include <iostream>
#include <unistd.h>
#include <csignal>
#include <termios.h>
#include <vector>
#include <algorithm>
#include "./EscapeSequence.hpp"

# define BLACK			"\x1b[0m"

void	enable_raw_mode(void);
void	disable_raw_mode(void);
int	is_escape_sequence(int fd, char c);
void	handle_backspace(std::string &input);
void	read_line(int fd, std::string &input);

# endif
