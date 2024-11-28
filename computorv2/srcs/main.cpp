/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:09:01 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/28 11:10:38 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"
#include "../incs/Color.hpp"

void	print_msg(std::string color, std::string msg)
{
	std::cout << color << msg << BLACK << std::endl;
}

void	show_prompt(char c)
{
	std::cout << CYAN << " " << c << ' '; 
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
	std::string	exit;

	print_msg(CYAN, "🐣 Welcom to the computorv2 🐣");
	print_msg(CYAN, "Type your input or type 'exit' to quit !\n");
	while (1)
	{
		show_prompt('>');
		std::getline(std::cin, input);

		/* check eof */
		if (std::cin.eof())
		{
			std::cout << "^D" << std::endl;
			break ;
		}
		/* check empty string */
		else if (input == "")
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
			std::cout << BLACK << "input: " << input << std::endl;
			//parse start
			continue ;
		}
	}
	return (0);
}
