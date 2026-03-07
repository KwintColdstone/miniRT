/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   utils.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 19:04:02 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:04:54 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

// Returns a random real in [0,1).
double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

// Returns a random real in [min,max).
double	random_double_mm(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp_interval(double x, t_interval i)
{
	if (x < i.min)
	{
		return (i.min);
	}
	if (x > i.max)
	{
		return (i.max);
	}
	return (x);
}

bool	interval_contains(t_interval i, double x)
{
	return (i.min <= x && x <= i.max);
}
