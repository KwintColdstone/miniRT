/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   atof.c                                                  :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/11 16:23:26 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/11 16:23:30 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	skip_spaces_and_signs(char *str, int *i)
{
	int	sign;

	sign = 1;
	while (ft_isspace(str[*i]))
		i++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (sign);
}

static void	add_digit_to_fraction(double *fraction, int digit, double *divisor,
				int *fract_count)
{
	*fraction += digit / *divisor;
	*divisor *= 10.0;
	(*fract_count)++;
}

static int	parse_next_digit(char *str, int *i, bool *is_fraction)
{
	if (str[*i] == '.')
	{
		*is_fraction = true;
		(*i)++;
	}
	return (str[*i] - '0');
}

static double	iterate_chars(char *str, int i, int sign, double *fraction)
{
	int		fract_count;
	int		digit;
	double	result;
	double	divisor;
	bool	is_fraction;

	divisor = 10.0;
	is_fraction = false;
	result = 0.0;
	fract_count = 0;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == '.'))
	{
		if (fract_count >= 3)
			return (sign * (result + *fraction));
		digit = parse_next_digit(str, &i, &is_fraction);
		if (is_fraction == true)
			add_digit_to_fraction(fraction, digit, &divisor, &fract_count);
		else
			result = result * 10 + digit;
		if (result >= INT_MAX)
			return (result);
		i++;
	}
	return (result);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		i;
	int		sign;

	fraction = 0.0;
	i = 0;
	sign = skip_spaces_and_signs(str, &i);
	result = iterate_chars(str, i, sign, &fraction);
	return (sign * (result + fraction));
}
