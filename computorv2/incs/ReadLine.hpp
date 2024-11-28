/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadLine.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:40:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/29 00:12:06 by yhwang           ###   ########.fr       */
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

class	ReadLine
{
public:
	ReadLine(int fd);
	ReadLine(const ReadLine& readline);
	ReadLine& operator=(const ReadLine& readline);
	~ReadLine();

	void		enable_raw_mode(void);
	void		disable_raw_mode(void);
	void		read_line(std::string &input);

private:
	ReadLine();

	int		is_escape_sequence(char c);
	void		handle_backspace(std::string &input);
	int		is_printable(char c);

	int		_fd;
};

# endif
