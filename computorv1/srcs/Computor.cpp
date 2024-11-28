/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/27 00:25:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Computor.hpp"

Computor::Computor(): _type_solution(""), _discriminant(0)
{
}

Computor::Computor(char *argv, int flag_bonus)
{
	Parse::parse_start(argv, flag_bonus);
	print_info();

	if (this->_equation_type >= 0)
	{
		for (size_t i = this->_reduced_form.size(); i > 0; i--)
			this->_term_descending_order.push_back(this->_reduced_form[i - 1]);
		if (this->_term_descending_order[0] < 0)
		{
			for (size_t i = 0; i < this->_term_descending_order.size(); i++)
				this->_term_descending_order[i] *= -1;
		}
		solve_equation();
	}
}

Computor::Computor(const Computor& computor): Parse(computor)
{
	*this = computor;
}

Computor& Computor::operator=(const Computor& computor)
{
	if (this == &computor)
		return (*this);
	Parse::operator=(computor);
	this->_type_solution = computor._type_solution;
	this->_discriminant = computor._discriminant;
	this->_solution = computor._solution;
	this->_term_descending_order = computor._term_descending_order;
	return (*this);
}

Computor::~Computor()
{
}

void	Computor::print_info(void)
{
	std::cout << CYAN << "Reduced form\t\t: " << BLACK;
	std::cout << this->_equation_str << std::endl;

	std::cout << CYAN << "Polynomial degree\t: " << BLACK;
	if (this->_equation_type == TYPE_FRACTIONAL)
	{
		std::cout << "The equation is fractional equation." << std::endl;
		std::cout << YELLOW << "The equation is not a polynomial equation, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
	std::cout << this->_max_degree << std::endl;
	if (this->_equation_type == TYPE_HIGH_DEGREE)
	{
		std::cout << YELLOW <<
			"The polynomial degree is strictly greater than 2, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
}

void	Computor::solve_constant(void)
{
	if (this->_reduced_form[0] == 0)
	{
		this->_type_solution = SOLUTION_INDETERMINATE;

		std::cout << CYAN
			<< "The equation is an indeterminate equation: "
			<< "It has infinitely many solutions"
			<< BLACK << std::endl;
	}
	else
	{
		this->_type_solution = SOLUTION_ZERO;

		std::cout << CYAN
			<< "The equation is an inconsistent equation: "
			<< "It has no solution"
			<< BLACK << std::endl;
	}
}

void	Computor::print_process_linear(void)
{
	float		a = this->_term_descending_order[0];
	float		b = this->_term_descending_order[1];
	float		tmp_a = a;
	float		tmp_b = b;
	std::string	tmp;
	
	std::cout << MAGENTA
		<< "Intermediate steps:" << BLACK << std::endl;

	tmp = float_to_string(a) + " * " + std::string(1, this->_variable);
	if (b > 0)
		tmp += " + ";
	else if (b < 0)
		tmp += " - ";
	if (b != 0)
		tmp += float_to_string(std::abs(b));
	tmp += " = 0";
	std::cout << "\t" << tmp << std::endl;

	if (b != 0)
	{
		tmp = " → " + float_to_string(a) + " * "
			+ std::string(1, this->_variable) + " = ";
		if (-b < 0)
			tmp += "-";
		tmp += float_to_string(std::abs(-b));
		std::cout << "\t" << tmp << std::endl;
	}

	tmp = "∴ " + std::string(1, this->_variable) + " = ";
	if (b == 0)
		tmp += "0";
	else
	{
		if (-b < 0)
			tmp += "-";
		tmp += float_to_string(std::abs(-b)) + "/" + float_to_string(a) + " = ";
		fraction_reduction(tmp_a, tmp_b);
		if (a != tmp_a)
		{
			if (-b < 0)
				tmp += "-";
			tmp += float_to_string(std::abs(tmp_b)) + "/" + float_to_string(tmp_a) + " = ";
		}
		tmp += float_to_string(this->_solution[0]);
	}

	std::cout << "\t" << tmp << std::endl;
}

void	Computor::solve_linear(void)
{
	float	a = this->_term_descending_order[0];
	float	b = this->_term_descending_order[1];

	this->_type_solution = SOLUTION_ONE;
	this->_solution.push_back(-1 * b / a);

	if (this->_solution[0] == -0)
		this->_solution[0] = 0;

	std::cout << CYAN << "The solution is\t\t: " << BLACK;
	std::cout << this->_variable << " = " << this->_solution[0] << std::endl;

	if (this->_flag_bonus)
		print_process_linear();
}

void	Computor::print_descending_order(std::vector<float> num)
{
	std::string	tmp = "";

	if (num[A] != 1)
		tmp += float_to_string(num[A]) + " * ";
	tmp += std::string(1, this->_variable) + "²";
	if (num[B] != 0)
	{
		if (num[B] < 0)
			tmp += " - ";
		else
			tmp += " + ";

		if (num[B] != 1)
			tmp += float_to_string(std::abs(num[B])) + " * ";
		tmp += std::string(1, this->_variable);
	}
	if (num[C] != 0)
	{
		if (num[C] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += float_to_string(std::abs(num[C]));
	}
	tmp += " = 0";
	std::cout << "\t" << tmp << std::endl;
}

int	Computor::is_int(float num)
{
	if (std::abs(num - (int)num) <= 1e-6)
		return (1);
	return (0);
}

void	Computor::divide_by_quad_coefficient(std::vector<float> &num,
						std::vector<std::string> &str)
{	
	// set variable
	num[B_PRIME] = num[B] / num[A];
	num[C_PRIME] = num[C] / num[A];

	if (num[B_PRIME] == 1)
		str[B_PRIME] = std::string(1, this->_variable);
	else
	{
		if (!is_int(num[B_PRIME]))
			str[B_PRIME] = float_to_string(std::abs(num[B]))
				+ "/" + float_to_string(num[A])
				+ std::string(1, this->_variable);
		else
		{
			if (num[B_PRIME] != 1)
				str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]))
					+ " * " + std::string(1, this->_variable);
			else
				str[B_PRIME] = std::string(1, this->_variable);
		}
			
	}
	if (!is_int(num[C_PRIME]))
		str[C_PRIME] = float_to_string(std::abs(num[C]))
			+ "/" + float_to_string(num[A]);
	else
		str[C_PRIME] = float_to_string(std::abs(num[C_PRIME]));

	// print
	std::string	tmp = "";

	if (num[A] != 1)
	{
		tmp += " → " + std::string(1, this->_variable) + "²";
		if (num[B_PRIME] != 0)
		{
			if (num[B_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[B_PRIME];
		}
		if (num[C_PRIME] != 0)
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
		tmp += " = 0";
		std::cout << "\t" << tmp << std::endl;
	}
}

void	Computor::find_perfect_square_coefficient(std::vector<float> &num,
						std::vector<std::string> &str)
{
	// set variable
	num[SQUARE_CONSTANT] = num[B] * num[B] / (4 * num[A] * num[A]);
	str[SQUARE_CONSTANT] = float_to_string(std::abs(num[B])) + "²/"
					+ "(2²*" + float_to_string(num[A]) + "²)";

	std::string	tmp = "";
	// print
	if (num[B_PRIME] != 0)
	{
		tmp += " → (" + std::string(1, this->_variable) + "²";
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME];

		tmp += " + " + str[SQUARE_CONSTANT] + ") - " + str[SQUARE_CONSTANT];

		if (num[C_PRIME] != 0)
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
		tmp += " = 0";
		std::cout << "\t" << tmp << std::endl;
	}
}

void	Computor::make_perfect_square_form(std::vector<float> &num,
						std::vector<std::string> &str)
{
	//set variable
	num[B_PRIME] /= 2;
	num[C_PRIME] *= -1;

	float	tmp1 = std::abs(num[B]);
	float	tmp2 = 2 * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[B_PRIME]))
		str[B_PRIME] = float_to_string(tmp1)
				+ "/" + float_to_string(tmp2);
	else
		str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]));

	//print
	std::string	tmp = "";

	if (num[B_PRIME] != 0)
	{
		tmp += " → (" + std::string(1, this->_variable);
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME] + ")²";
		tmp += " = " + str[SQUARE_CONSTANT];
		if (num[C_PRIME])
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
	}
	else
	{
		tmp += " → " + std::string(1, this->_variable) + "²";
		tmp += " = ";
		if (num[C_PRIME] < 0)
			tmp += "-";
		tmp += str[C_PRIME];
	}

	tmp1 = num[B] * num[B];
	tmp2 = 4 * num[A] * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[SQUARE_CONSTANT]))
		str[SQUARE_CONSTANT] = float_to_string(tmp1)
					+ "/" + float_to_string(tmp2);
	else
		str[SQUARE_CONSTANT] = float_to_string(num[SQUARE_CONSTANT]);

	if (num[SQUARE_CONSTANT] && num[C_PRIME])
	{
		tmp += " = " + str[SQUARE_CONSTANT];
		if (num[C_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[C_PRIME];
	}

	// calculate right term, update it to new_c
	num[C_PRIME] = num[SQUARE_CONSTANT] + num[C_PRIME];
	tmp1 = std::abs(num[B] * num[B] - 4 * num[A] * num[C]);
	tmp2 = 4 * num[A] * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[C_PRIME]))
		str[C_PRIME] = float_to_string(tmp1)
			+ "/" + float_to_string(tmp2);
	else
		str[C_PRIME] = float_to_string(num[C_PRIME]);

	//print
	if (num[SQUARE_CONSTANT])
	{
		tmp += " = ";
		if (this->_discriminant < 0)
			tmp += "-";
		if (str[C_PRIME][0] == '-')
			tmp += str[C_PRIME].substr(1, std::string::npos);
		else
			tmp += str[C_PRIME];
	}
	std::cout << "\t" << tmp << std::endl;
}

void	Computor::remove_square(std::vector<float> &num,
						std::vector<std::string> &str)
{
	std::string	tmp = "";

	tmp += "↔ " + std::string(1, this->_variable);
	if (num[B_PRIME] != 0)
	{
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME];
	}
	tmp += " = ";
	if (num[C_PRIME] > 0)
		tmp += "± √(" + str[C_PRIME] + ")";
	else if (num[C_PRIME] == 0)
		tmp += "0";
	else
	{
		if (str[C_PRIME][0] == '-')
			str[C_PRIME] = str[C_PRIME].substr(1, std::string::npos);
		tmp += "± √(" + str[C_PRIME] + ")" + "i";
	}
	std::cout << "\t" << tmp << std::endl;
}

void	Computor::find_x(std::vector<float> &num,
						std::vector<std::string> &str)
{
	// set variable
	num[B_PRIME] *= -1;
	if (str[B_PRIME][0] == '-')
		str[B_PRIME] = str[B_PRIME].substr(1, std::string::npos);
	if (num[B_PRIME] < 0)
		str[B_PRIME] = "-" + str[B_PRIME];

	// print
	std::string tmp = "";

	if (num[B_PRIME] != 0 && num[C_PRIME] != 0)
	{
		tmp = " → " + std::string(1, this->_variable);
		tmp += " = ";
		tmp += str[B_PRIME];
		tmp += " ± ";
		if (num[C_PRIME] > 0)
		{
			if (!is_int(sqrt(num[C_PRIME])))
				tmp += "√(" + str[C_PRIME] + ")";
			else
				tmp += float_to_string(sqrt(num[C_PRIME]));
		}
		else
		{
			if (!is_int(sqrt(num[C_PRIME])))
				tmp += "√(" + str[C_PRIME] + ")" + "i";
			else
				tmp += float_to_string(sqrt(num[C_PRIME])) + "i";
		}
		std::cout << "\t" << tmp << std::endl;
	}
}

void	Computor::split_square_num(float &num_int, float &num_real)
{
	float			copy_real = num_real;
	std::vector<int>	tmp;

	for (int i = 2; i <= copy_real; i++)
	{
		if (is_int(copy_real / i))
		{
			tmp.push_back(i);
			copy_real /= i;
			i = 1;
		}
	}

	for (size_t i = 1; i < tmp.size(); i++)
	{
		if (tmp[i - 1] == tmp[i])
		{
			num_int *= tmp[i];
			i = i + 2;
		}
	}
	num_real /= num_int * num_int;
}

void	Computor::fraction_reduction(float &n1, float &n2)
{
	std::vector<int>	tmp;
	float			common = 1;

	for (size_t i = 2; i <= std::abs(n1); i++)
	{
		if (is_int(n1 / i))
			tmp.push_back(i);
	}
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (is_int(n2 / tmp[i]))
			common = tmp[i];
	}
	n1 /= common;
	n2 /= common;
}

void	Computor::fraction_reduction(float &n1, float &n2, float &n3)
{
	std::vector<int>	tmp;
	float			common = 1;

	for (size_t i = 2; i <= std::abs(n1); i++)
	{
		if (is_int(n1 / i))
			tmp.push_back(i);
	}
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (is_int(n2 / tmp[i]) && is_int(n3 / tmp[i]))
			common = tmp[i];
	}
	n1 /= common;
	n2 /= common;
	n3 /= common;
}

void	Computor::calc_x(std::vector<float> &num, std::vector<std::string> &str)
{
	int	flag_imaginary = 0;

	if (num[C_PRIME] < 0)
	{
		flag_imaginary = 1;
		num[C_PRIME] *= -1;
	}

	float	x1 = -1 * num[B];
	float	x2_int = 1;
	float	x2_real = num[B] * num[B] - (4 * num[A] * num[C]);
	float	x3 = 2 * num[A];

	if (flag_imaginary)
		x2_real *= -1;

	split_square_num(x2_int, x2_real);

	std::string	solution_1 = "";
	std::string	solution_2 = "";

	if (is_int(sqrt(x2_real)))
	{
		if (!flag_imaginary)
		{
			x2_int *= sqrt(x2_real);

			float 	tmp1 = x1 - x2_int;
			float	tmp2 = x3;
			fraction_reduction(tmp1, tmp2);

			float	tmp3 = x1 + x2_int;
			float	tmp4 = x3;
			fraction_reduction(tmp3, tmp4);

			solution_1 += float_to_string(tmp1);
			if (tmp2 != 1)
				solution_1 += "/" + float_to_string(tmp2);
			solution_2 += float_to_string(tmp3);
			if (tmp4 != 1)
				solution_2 += "/" + float_to_string(tmp4);
		}
		else
		{
			solution_1 += str[B_PRIME] + " + ";
			solution_1 += float_to_string(sqrt(num[C_PRIME])) + "i";

			solution_2 += str[B_PRIME] + " - ";
			solution_2 += float_to_string(sqrt(num[C_PRIME])) + "i";
		}
	}
	else
	{
		if (x1 != 0)
			fraction_reduction(x1, x2_int, x3);
		else
			fraction_reduction(x2_int, x3);

		// solution_1
		if (x1 && x2_int && x3 != 1)
			solution_1 += "(";
		if (x1 != 0)
			solution_1 += float_to_string(x1) + " ";
		solution_1 += "- ";
		if (x2_int != 1)
			solution_1 += float_to_string(x2_int);
		solution_1 += "√(" + float_to_string(x2_real) + ")";
		if (flag_imaginary)
			solution_1 += "i";
		if (x1 && x2_int && x3 != 1)
			solution_1 += ")";
		if (x3 != 1)
			solution_1 += "/" + float_to_string(x3);

		// solution_2
		if (x1 && x2_int && x3 != 1)
			solution_2 += "(";
		if (x1 != 0)
			solution_2 += float_to_string(x1) + " ";
		solution_2 += "+ ";
		if (x2_int != 1)
			solution_2 += float_to_string(x2_int);
		solution_2 += "√(" + float_to_string(x2_real) + ")";
		if (flag_imaginary)
			solution_2 += "i";
		if (x1 && x2_int && x3 != 1)
			solution_2 += ")";
		if (x3 != 1)
			solution_2 += "/" + float_to_string(x3);
	}

	//print
	std::string	tmp = "";

	tmp += " ∴ " + std::string(1, this->_variable);
	tmp += " = " + solution_1 + ",";
	tmp += "\n\t   " + std::string(1, this->_variable);
	tmp += " = " + solution_2;

	std::cout << "\t" << tmp << std::endl;
}

void	Computor::print_process_quadratic(void)
{

	std::vector<float>		num(6, 0);
	std::vector<std::string>	str(6, "");

	num[A] = this->_term_descending_order[0];
	num[B] = this->_term_descending_order[1];
	num[C] = this->_term_descending_order[2];

	int	tmp = 1;

	while (!(is_int(num[A]) && is_int(num[B]) && is_int(num[C])))
	{
		if (!is_int(num[A]))
		{
			while (!is_int(num[A] * tmp))
				tmp *= 10;
			num[A] *= 10;
			num[B] *= 10;
			num[C] *= 10;
			fraction_reduction(num[A], num[B], num[C]);
		}
		else if (!is_int(num[B]))
		{
			while (!is_int(num[B] * tmp))
				tmp *= 10;
			num[A] *= 10;
			num[B] *= 10;
			num[C] *= 10;
			fraction_reduction(num[A], num[B], num[C]);
		}
		else
		{
			while (!is_int(num[C] * tmp))
				tmp *= 10;
			num[A] *= 10;
			num[B] *= 10;
			num[C] *= 10;
			fraction_reduction(num[A], num[B], num[C]);
		}
	}

	std::cout << MAGENTA
		<< "Intermediate steps:" << BLACK << std::endl;

	// ax² + bx + c = 0
	print_descending_order(num);

	// x² + b/ax + c/a = 0
	divide_by_quad_coefficient(num, str);

	// (x² + b/ax + b²/(2²*a²)) - b²/(2²*a²) + c/a = 0
	find_perfect_square_coefficient(num, str);

	// (x + b/(2a))² = b²/(2²*a²) - c/a
	make_perfect_square_form(num, str);

	// check discriminant value
	if (this->_discriminant < 0)
	{
		std::cout << YELLOW
			<< "\tWithin the real number range," << std::endl
			<< "\tthe square of any number cannot be less than 0." << std::endl << std::endl
			<< "\tIt has no solution within the real number range," << std::endl
			<< "\tbut it has two solution within the imaginary range"<< BLACK << std::endl;
	}

	// ↔ x + b/(2*a) = ± √((b²-4*a*c)/(2*a))
	remove_square(num, str);

	// x = - b/(2*a) ± √((b²-4*a*c)/(2*a))
	find_x(num, str);

	// ∴ x = value
	if (num[C_PRIME] == 0)
	{
		if (num[B_PRIME] == 0)
			return ;
		std::cout << "\t ∴ " + std::string(1, this->_variable)
			+ " = " + str[B_PRIME] << std::endl;
	}
	else
		calc_x(num, str);
}

void	Computor::solve_quadratic(void)
{
	float	a = this->_term_descending_order[0];
	float	b = this->_term_descending_order[1];
	float	c = this->_term_descending_order[2];

	this->_discriminant = b * b - 4 * a * c;
	if (this->_discriminant > 0)
	{
		this->_type_solution = SOLUTION_TWO;
		this->_solution.push_back((-1 * b - std::sqrt(this->_discriminant)) / (2 * a));
		this->_solution.push_back((-1 * b + std::sqrt(this->_discriminant)) / (2 * a));

		std::cout << CYAN << "Discriminant is strictly positive." << std::endl
			<< "The two solutions are\t: " << BLACK;
		std::cout << this->_variable << " = " << this->_solution[0] << "," << std::endl
			<< "\t\t\t  " << this->_variable << " = " << this->_solution[1]
			<< std::endl;
	}
	else if (this->_discriminant == 0)
	{
		this->_type_solution = SOLUTION_ONE;
		this->_solution.push_back(-1 * b / (2 * a));

		std::cout << CYAN << "Discriminant is zero." << std::endl
			<< "The solution is\t\t: " << BLACK;
		std::cout << this->_variable << " = " << this->_solution[0]
			<< std::endl;
	}
	else
	{
		this->_type_solution = SOLUTION_ZERO;

		std::cout << CYAN << "Discriminant is strictly negative." << std::endl
			<< "It has no solution within the real number range" << BLACK << std::endl;
	}

	if (this->_flag_bonus)
		print_process_quadratic();
}

void	Computor::solve_equation(void)
{
	if (this->_equation_type == TYPE_CONSTANT)
		solve_constant();
	else if (this->_equation_type == TYPE_LINEAR)
		solve_linear();
	else
		solve_quadratic();
	for (size_t i = 0; i < this->_solution.size(); i++)
	{
		if (this->_solution[i] == -0)
			this->_solution[i] = 0;
	}
}
