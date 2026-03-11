/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   assign_color.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 17:04:50 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 18:05:53 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"

static void	free_color_strings(char *r, char *g, char *b)
{
	if (r)
		free(r);
	if (g)
		free(g);
	if (b)
		free(b);
}

static t_vec3	color_to_vec3(double r, double g, double b)
{
	return ((t_vec3){r / 255.0, g / 255.0, b / 255.0});
}

static bool	string_rgb_to_vec3(t_vec3 *v, double strength, char *color_str[3])
{
	double	r;
	double	g;
	double	b;

	r = ft_atof(color_str[0]);
	g = ft_atof(color_str[1]);
	b = ft_atof(color_str[2]);
	free_color_strings(color_str[0], color_str[1], color_str[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (minirt_perror("color values outside of RGB range"), false);
	*v = color_to_vec3(r * strength, g * strength, b * strength);
	return (true);
}

bool	assign_color(t_vec3 *v, char *s, double strength)
{
	int		i;
	char	*r_str;
	char	*g_str;
	char	*b_str;

	i = 0;
	r_str = extract_element(s, &i, ',');
	if (!r_str)
		return (free_color_strings(r_str, NULL, NULL), false);
	g_str = extract_element(s, &i, ',');
	if (!g_str)
		return (free_color_strings(r_str, g_str, NULL), false);
	b_str = extract_element(s, &i, ' ');
	if (!b_str)
		return (free_color_strings(r_str, g_str, b_str), false);
	if (!is_float(r_str) || !is_float(g_str) || !is_float(b_str))
		return (free_color_strings(r_str, g_str, b_str), false);
	if (!string_rgb_to_vec3(v, strength, (char *[3]){r_str, g_str, b_str}))
		return (false);
	return (true);
}
