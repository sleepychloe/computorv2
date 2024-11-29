/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadLine.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:40:49 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/29 11:57:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_HPP
# define READ_LINE_HPP

#include <iostream>
#include <unistd.h>
#include <csignal>
#include <termios.h>
#include <unordered_set>
#include <algorithm>
#include "./EscapeSequence.hpp"

# define BLACK					"\x1b[0m"

# define NONE					0
# define SEQUENCE_ALT				1
# define SEQUENCE_ARROW				2
# define SEQUENCE_FUNCTION_NAVIGATION		3
# define UNRECOGNIZED_SEQUENCE			4
# define SEQUENCE_DELETE			5

class	ReadLine
{
public:
	ReadLine(int fd);
	ReadLine(const ReadLine& readline);
	ReadLine& operator=(const ReadLine& readline);
	~ReadLine();

	void		enable_raw_mode(void);
	void		disable_raw_mode(void);
	void		read_line(std::string prompt, std::string &input);
	void		read_line(std::string prompt, std::string color, std::string &input);

private:
	ReadLine();

	int		is_escape_sequence(std::string &input, char c);
	void		handle_arrow(std::string &input, size_t &cursor);
	void		handle_backspace(std::string &input, size_t &cursor);
	int		is_printable(char c);
	void		update_display(std::string prompt, std::string &input, size_t cursor);

	int		_fd;
};

# endif
