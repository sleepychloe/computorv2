/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:09:01 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/16 16:34:35 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ReadLine/incs/ReadLine.hpp"
#include "../incs/parse/Parse.hpp"
#include "../incs/execute/AST.hpp"
#include "../incs/Color.hpp"

void	ignore_all_signal(void)
{
	sigset_t	mask;

	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);
}

void	print_msg(std::string color, std::string msg)
{
	std::cout << color << msg << BLACK << std::endl;
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		std::cerr << RED << "Error: invalid argument" << BLACK << std::endl;
		return (1);
	}

	std::string	input;
	ReadLine	rl(STDIN_FILENO);
	Parse		p;
	AST		ast;

	//test variable
	p.set_var({{"a", "1.1"}, {"b", "1+1i"},
		{"c", "[[1.1,2.2];[3.3,4.4]]"}, {"d", "[[1+1i,2+2i];[3+3i,4+4i]]"},
		{"e", "[1.1,2.2,3.3]"}, {"f", "[1+1i,2+2i,3+3i]"}});
	p.set_func({{"f", "x^2+1"}});
	////
	ignore_all_signal();
	print_msg(CYAN, "🐣 Welcom to the computorv2 🐣");
	print_msg(CYAN, "type 'exit' to quit !\n");
	
	while (1)
	{
		if (rl.read_line("> ", CYAN, input) == -1)
		{
			std::cerr << RED << "Error: unexpected error from ReadLine::read_line()"
				<< BLACK << std::endl;
			return (1);
		}

		/* check empty string */
		if (input == "" || input.empty())
		{
			print_msg(RED, "Warning: the input is empty");
			continue ;
		}
		/* check exit */
		else if (input == "exit" || input == "EXIT")
		{
			print_msg(CYAN, "Program terminated");
			break ;
		}
		else
		{
			try
			{
				input = p.parse_start(input);
				std::cout << "input: " << input << std::endl;//
			}
			catch(const Error::ParseException& e)
			{
				std::cerr << e.what() << std::endl;
				continue ;
			}
			// try
			// {
			// 	ast.start_syntax_checking(input);
			// }
			// catch(std::string err_msg)
			// {
			// 	std::cerr << RED << "error: invalid term: " << err_msg << BLACK << std::endl;
			// 	continue ;
			// }
		}
	}
	return (0);
}
