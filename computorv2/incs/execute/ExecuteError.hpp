/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteError.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:12:07 by yhwang            #+#    #+#             */
/*   Updated: 2024/12/18 20:05:03 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_ERROR_HPP
# define EXECUTE_ERROR_HPP

#include <string>
#include <sstream>
#include <exception>
#include "../Color.hpp"

namespace ExecuteError
{
	typedef struct s_error
	{
		std::string	file_name;
		std::string	cat;
		std::string	function;
		std::string	msg;
		size_t		term_idx;
		std::string	term_str;
	}	t_error;

	class ExecuteException: public std::exception
	{
	public:
		ExecuteException(const t_error &error): _error(error) {}

		virtual const char* what() const throw()
		{
			std::ostringstream	oss;

			oss << this->_error.file_name << ": "
				<< this->_error.function << std::endl
				<< RED << "error: " << this->_error.cat << ": "
				<< YELLOW << this->_error.msg << ": " << BLACK
				<< "at term " << this->_error.term_idx << std::endl
				<< this->_error.term_str << std::endl;
			this->_what_msg = oss.str();
			return (_what_msg.c_str());
		}

	private:
		t_error			_error;
		mutable std::string	_what_msg;
	};
}

#endif
