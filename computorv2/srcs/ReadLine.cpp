/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadLine.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:40:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/28 18:49:30 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ReadLine.hpp"

void	enable_raw_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	disable_raw_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);

	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int	is_escape_sequence(int fd, char c)
{
	char		seq[2];
	std::string	escape_sequence(1, c);

	std::vector<std::string>	vec_sequence({ESCAPE_UP_ARROW, ESCAPE_DOWN_ARROW,
						ESCAPE_RIGHT_ARROW, ESCAPE_LEFT_ARROW,
						ESCAPE_F1, ESCAPE_F2, ESCAPE_F3, ESCAPE_F4,
						ESCAPE_F5, ESCAPE_F6, ESCAPE_F7, ESCAPE_F8,
						ESCAPE_F9, ESCAPE_F10, ESCAPE_F11, ESCAPE_F12,
						ESCAPE_INSERT, ESCAPE_DELETE,
						ESCAPE_HOME, ESCAPE_END,
						ESCAPE_PAGE_UP, ESCAPE_PAGE_DOWN,
						ESCAPE_ALT_A, ESCAPE_ALT_B,
						ESCAPE_ALT_C, ESCAPE_ALT_D});
	if (c == '\033')
	{
		if (read(fd, seq, 2) == 2)
		{
			escape_sequence += std::string(seq);
			if (std::find(vec_sequence.begin(), vec_sequence.end(), escape_sequence) == vec_sequence.end())
				return (1);
		}
	}
	return (0);
}

void	handle_backspace(std::string &input)
{
	if (!input.empty() && input.length() >= 1)
	{
		input.pop_back();
		std::cout << "\b \b";
		std::cout.flush();
	}
}

int	is_printable(char c)
{
	if (32 <= c && c <= 126)
		return (c);
	return (0);
}

void	read_line(int fd, std::string &input)
{
	char		c;

	input.clear();
	enable_raw_mode();

	while (1)
	{
		read(fd, &c, 1);

		if (is_escape_sequence(fd, c))
			continue ;
		if (c == 127 || c == '\b')
		{
			handle_backspace(input);
			continue ;
		}
		if (c == '\n')
			break ;
		if (!is_printable(c))
			continue ;

		input += c;
		std::cout << c;
		std::cout.flush();
	}
	disable_raw_mode();
	std::cout << std::endl;
}
