#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include <unistd.h>

bool	is_float(char *s)
{
	int	i;
	int	fractals;
	int	minuses;
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
	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
		return ft_strdup("");
	int start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && s[*i] != delim)
		*i += 1;
	char *element = ft_substr(s, start, *i - start);
	if (s[*i] && s[*i] == delim)
		*i += 1;

	return element;
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

bool	assign_vec3(t_vec3 *v, char *s, double min, double max)
{
	int i = 0;
	char *x_str = extract_element(s, &i, ',');
	char *y_str = extract_element(s, &i, ',');
	char *z_str = extract_element(s, &i, ' ');
	if (!is_float(x_str) || !is_float(y_str) || !is_float(z_str))
	{
		printf("vec3 float test failed\n");
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
		printf("vec3 outside range\n");
		return (false);
	}
	v->x = x;
	v->y = y;
	v->z = z;
	return (true);
}

static t_vec3	color_to_vec3(double r, double g, double b)
{
	return (t_vec3){r / 255.0, g / 255.0, b / 255.0};
}

bool	assign_color(t_vec3 *v, char *s, double strength)
{
	int i = 0;
	char *r_str = extract_element(s, &i, ',');
	char *g_str = extract_element(s, &i, ',');
	char *b_str = extract_element(s, &i, ' ');
	if (!is_float(r_str) || !is_float(g_str) || !is_float(b_str))
	{
		free(r_str);
		free(g_str);
		free(b_str);
		return (false);
	}
	double r;
	double g;
	double b;
	r = ft_atof(r_str);
	g = ft_atof(g_str);
	b = ft_atof(b_str);
	free(r_str);
	free(g_str);
	free(b_str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		return (false);
	}
	*v = color_to_vec3(r*strength, g*strength, b*strength);
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
				counts->ambient++;
			}
			else if (line[i] == 'C')
			{
				counts->camera++;
			}
			else if (line[i] == 'L')
			{
				counts->light++;
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
				printf("parsing failed at line %d: not an element\n", i);
				close(fd);
				free(line);
				return (false);
			}
			if (counts->ambient > 1 || counts->light > 1 || counts->light > 1)
			{
				ft_putstr_fd("parsing failed: more than one capitalized element", STDERR_FILENO);
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
