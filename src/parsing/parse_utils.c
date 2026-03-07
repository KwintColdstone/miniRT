/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_utils.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 18:21:58 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 18:29:33 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include <unistd.h>

char	*extract_element(char *s, int *i, char delim)
{
	char	*element;
	int		start;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
	{
		element = ft_strdup("");
		if (!element)
		{
			external_perror("malloc error on extracting element");
			return (NULL);
		}
		return (element);
	}
	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && s[*i] != delim)
		*i += 1;
	element = ft_substr(s, start, *i - start);
	if (!element)
		return (external_perror("malloc error on extracting element"), NULL);
	if (s[*i] && s[*i] == delim)
		*i += 1;
	return (element);
}

static bool	check_minuses(char *s, int *i)
{
	int	minuses;

	minuses = 0;
	if (s[*i] == '-')
	{
		minuses++;
		(*i)++;
	}
	if (minuses > 1)
		return (minirt_perror("Too many minuses"), false);
	return (true);
}

static bool	check_fractals(char *s, int *i, bool *in_fractal, int *fractals)
{
	if (!*in_fractal)
	{
		if (!ft_isdigit(s[*i]))
		{
			if (s[*i] != '.')
				return (minirt_perror("Non digit is not a point"), false);
			else
				*in_fractal = true;
		}
		(*i)++;
	}
	else
	{
		if (!ft_isdigit(s[*i]) || *fractals > 1)
		{
			minirt_perror("Fractal not a digit or more than one fractal");
			return (false);
		}
		(*i)++;
		(*fractals)++;
	}
	return (true);
}

bool	is_float(char *s)
{
	int		i;
	int		fractals;
	bool	in_fractal;

	i = 0;
	fractals = 0;
	in_fractal = false;
	while (s[i])
	{
		if (!check_minuses(s, &i))
		{
			ft_putstr_fd("Value is not a float\n", STDERR_FILENO);
			return (false);
		}
		if (!check_fractals(s, &i, &in_fractal, &fractals))
		{
			ft_putstr_fd("Value is not a float\n", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

bool	assign_float(double *f, char *s, double min, double max)
{
	int		i;
	char	*elem;

	i = 0;
	elem = extract_element(s, &i, ' ');
	if (!elem)
		return (false);
	if (!is_float(elem))
	{
		free(elem);
		return (false);
	}
	*f = ft_atof(elem); // atof function needs to be normed!
	free(elem);
	if (*f < min || *f > max)
		return (minirt_perror("Float outside of range"), NULL);
	return (true);
}
