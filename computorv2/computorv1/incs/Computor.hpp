/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/24 23:20:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include "./Parse.hpp"

# define TYPE_CONSTANT			0
# define TYPE_LINEAR			1
# define TYPE_QUADRATIC			2

# define SOLUTION_INDETERMINATE		"INDETERMINATE"
# define SOLUTION_ZERO			"NO SOLUTION"
# define SOLUTION_ONE			"1"
# define SOLUTION_TWO			"2"

# define A				0
# define B				1
# define C				2
# define B_PRIME			3
# define C_PRIME			4
# define SQUARE_CONSTANT		5

class Computor: public Parse
{
public:
	Computor(char *argv, int flag_bonus);
	Computor(const Computor& computor);
	Computor& operator=(const Computor& computor);
	~Computor();

	void				print_info(void);

private:
	Computor();

	void				solve_constant(void);

	void				print_process_linear(void);
	void				solve_linear(void);

	void				print_descending_order(std::vector<float> num);
	int				is_int(float num);
	void				divide_by_quad_coefficient(std::vector<float> &num,
						std::vector<std::string> &str);
	void				find_perfect_square_coefficient(std::vector<float> &num,
						std::vector<std::string> &str);
	void				make_perfect_square_form(std::vector<float> &num,
						std::vector<std::string> &str);
	void				remove_square(std::vector<float> &num,
						std::vector<std::string> &str);
	void				find_x(std::vector<float> &num,
						std::vector<std::string> &str);
	void				split_square_num(float &num_int, float &num_real);
	void				fraction_reduction(float &n1, float &n2);
	void				fraction_reduction(float &n1, float &n2, float &n3);
	void				calc_x(std::vector<float> &num,
						std::vector<std::string> &str);
	void				print_process_quadratic(void);
	void				solve_quadratic(void);

	void				solve_equation(void);

	std::string			_type_solution;
	float				_discriminant;
	std::vector<float>		_solution;
	std::vector<float>		_term_descending_order;
};

# endif
