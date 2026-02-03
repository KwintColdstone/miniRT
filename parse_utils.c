#include "libft/libft.h"
#include "miniRT.h"
#include <unistd.h>

bool	is_float(char *s)
{
	int i = 0;
	int	fractals;
	bool	in_fractal;

	fractals = 0;
	in_fractal = false;
	while (s[i])
	{
		if (!in_fractal)
		{
			if (!ft_isdigit(s[i]))
			{
				if (s[i] != '.')
					return (false);
				else
					in_fractal = true;
			}
			i++;
		}
		else
		{
			if (!ft_isdigit(s[i]) || fractals > 1)
				return (false);
			i++;
			fractals++;
		}
	}
	return (true);
}

char	*subtract_element(char *s, int *i, char delim)
{
	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	int j = *i;
	while (s[j] && !ft_isspace(s[j]) && s[j] != delim)
		j++;
	if (s[j] == delim)
		j++;
	*i += j;
	return (ft_substr(s, *i, j - 1));
}


bool	assign_float(double *f, char *s, double min, double max)
{
	int i = 0;

	char *elem = subtract_element(s, &i, ' ');
	if (!is_float(elem))
	{
		free(elem);
		return (false);
	}
	*f = ft_atof(elem);
	free(elem);
	if (*f < min || *f > max)
		return (false);
	return (true);
}

bool	assign_vec3(t_vec3 *v, char *s, double min, double max)
{
	int i = 0;
	char *x_str = subtract_element(s, &i, ',');
	char *y_str = subtract_element(s, &i, ',');
	char *z_str = subtract_element(s, &i, ' ');
	if (!is_float(x_str) || !is_float(y_str) || !is_float(z_str))
	{
		free(x_str);
		free(y_str);
		free(z_str);
		return (false);
	}
	double x;
	double y;
	double z;
	x = ft_atof(x_str);
	y = ft_atof(y_str);
	z = ft_atof(z_str);
	free(x_str);
	free(y_str);
	free(z_str);
	if (x < min || x > max || y < min || y > max || z < min || z > max)
	{
		return (false);
	}
	v->x = x;
	v->y = y;
	v->z = z;
	return (true);
}

bool	count_objects(int fd, t_object_counter *counts)
{
	char	*line;

	ft_memset(counts, 0, sizeof(t_object_counter));
	line = get_next_line(fd);
	while (line) {
		int i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i])
		{
			if (line[i] == 'A')
			{
			}
			else if (line[i] == 'C')
			{
			}
			else if (line[i] == 'L')
			{
				counts->light_cap++;
			}
			else if (line[i] == 's' && line[i+1] == 'p')
			{
				counts->sphere_cap++;
			}
			else if (line[i] == 'p' && line[i+1] == 'l')
			{
				counts->plane_cap++;
			}
			else if (line[i] == 'c' && line[i+1] == 'y')
			{
				counts->cylinder_cap++;
			}
			else if (line[i] == 'q' && line[i+1] == 'u')
			{
				counts->quad_cap++;
			}
			else
			{
				ft_putstr_fd("parsing failed: not an element", STDERR_FILENO);
				close(fd);
				free(line);
				return (false);
			}
		}
		
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
