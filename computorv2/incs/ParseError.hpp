/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseError.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:48:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/15 13:52:16 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ERROR_HPP
# define PARSE_ERROR_HPP

#include <string>
#include <sstream>
#include <exception>
#include "./Color.hpp"

namespace Error
{
	typedef struct s_error
	{
		std::string	file_name;
		std::string	cat;
		std::string	function;
		std::string	msg;
		size_t		pos;
		std::string	pos_str;
	}	t_error;

	class ParseException: public std::exception
	{
	public:
		ParseException(const t_error &error): _error(error) {}

		virtual const char* what() const throw()
		{
			std::ostringstream	oss;

			oss << this->_error.file_name << ": "
				<< this->_error.function << std::endl
				<< RED << "error: " << this->_error.cat << ": "
				<< YELLOW << this->_error.msg << ": " << BLACK
				<< "at position " << this->_error.pos << std::endl
				<< this->_error.pos_str << std::endl;
			this->_what_msg = oss.str();
			return (_what_msg.c_str());
		}

	private:
		t_error			_error;
		mutable std::string	_what_msg;
	};
}

# endif
