/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadLine.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:40:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/29 00:15:09 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ReadLine.hpp"

ReadLine::ReadLine()
{
}

ReadLine::ReadLine(int fd): _fd(fd)
{
}

ReadLine::ReadLine(const ReadLine& readline)
{
	*this = readline;
}

ReadLine&	ReadLine::operator=(const ReadLine& readline)
{
	if (this == &readline)
		return (*this);
	this->_fd = readline._fd;
	return (*this);
}

ReadLine::~ReadLine()
{
}

void	ReadLine::enable_raw_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	ReadLine::disable_raw_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);

	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int	ReadLine::is_escape_sequence(char c)
{
	char		seq;
	std::string	escape_sequence(1, c);

	std::vector<std::string>	vec_seq({ESCAPE_UP_ARROW, ESCAPE_DOWN_ARROW,
						ESCAPE_RIGHT_ARROW, ESCAPE_LEFT_ARROW,
						ESCAPE_F1, ESCAPE_F2, ESCAPE_F3, ESCAPE_F4,
						ESCAPE_F5, ESCAPE_F6, ESCAPE_F7, ESCAPE_F8,
						ESCAPE_F9, ESCAPE_F10, ESCAPE_F11, ESCAPE_F12,
						ESCAPE_INSERT, ESCAPE_DELETE,
						ESCAPE_HOME, ESCAPE_END,
						ESCAPE_PAGE_UP, ESCAPE_PAGE_DOWN,
						// ESCAPE_ALT_A, ESCAPE_ALT_B,
						// ESCAPE_ALT_C, ESCAPE_ALT_D
						});
	if (c == '\033')
	{
		while (read(this->_fd, &seq, 1) == 1)
		{
			escape_sequence += std::string(1, seq);
			if (seq == '~' || seq == 'P' || seq == 'Q' || seq == 'R'
				|| seq == 'S' || seq == 'H' || seq == 'F'
				|| seq == 'A' || seq == 'B' || seq == 'C' || seq == 'D')
				break ;
		}
		if (std::find(vec_seq.begin(), vec_seq.end(), escape_sequence) == vec_seq.end())
			return (1);
	}
	return (0);
}

void	ReadLine::handle_backspace(std::string &input)
{
	if (!input.empty() && input.length() >= 1)
	{
		input.pop_back();
		std::cout << "\b \b";
		std::cout.flush();
	}
}

int	ReadLine::is_printable(char c)
{
	if (32 <= c && c <= 126)
		return (c);
	return (0);
}

void	ReadLine::read_line( std::string &input)
{
	char		c;

	input.clear();
	enable_raw_mode();

	while (1)
	{
		read(this->_fd, &c, 1);

		if (is_escape_sequence(c))
			continue ;
		else if (c == 127 || c == '\b')
		{
			handle_backspace(input);
			continue ;
		}
		else if (c == '\n')
			break ;
		else if (!is_printable(c))
			continue ;
		else
		{
			input += c;
			std::cout << c;
			std::cout.flush();
		}
	}
	disable_raw_mode();
	std::cout << std::endl;
}
