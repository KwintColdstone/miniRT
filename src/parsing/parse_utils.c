#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include <unistd.h>

bool	is_float(char *s)
{
	int		i;
	int		fractals;
	int		minuses;
	bool	in_fractal;

	i = 0;
	fractals = 0;
	minuses = 0;
	in_fractal = false;
	while (s[i])
	{
		if (s[i] == '-')
		{
			minuses++;
			i++;
		}
		if (minuses > 1)
		{
			printf("too many minuses\n");
			return (false);
		}
		if (!in_fractal)
		{
			if (!ft_isdigit(s[i]))
			{
				if (s[i] != '.')
				{
					printf("non digit is not a point\n");
					return (false);
				}
				else
					in_fractal = true;
			}
			i++;
		}
		else
		{
			if (!ft_isdigit(s[i]) || fractals > 1)
			{
				printf("fractal not a digit or more than one fractal\n");
				return (false);
			}
			i++;
			fractals++;
		}
	}
	return (true);
}

char *extract_element(char *s, int *i, char delim)
{
	char	*element;
	int 	start;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
	{
		element = ft_strdup("");
		if (!element)
			return (external_perror("malloc error on extracting element"),
				NULL);
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

bool	assign_float(double *f, char *s, double min, double max)
{
	int i = 0;

	char *elem = extract_element(s, &i, ' ');
	if (!is_float(elem))
	{
		ft_putstr_fd("not a float\n", STDERR_FILENO);
		free(elem);
		return (false);
	}
	*f = ft_atof(elem);
	free(elem);
	if (*f < min || *f > max)
	{
		ft_putstr_fd("float outside range\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

