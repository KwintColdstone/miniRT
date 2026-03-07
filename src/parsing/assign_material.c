/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   assign_material.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 16:49:10 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 17:03:01 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	check_material_type(t_material *mat, char *mat_str)
{
	t_material	base;
	t_material	metal;
	t_material	emit;

	if (!mat_str || mat_str[0] == '\0')
	{
		base = (t_material){MAT_LAMBERTIAN,
			(t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = base;
		return (true);
	}
	if (ft_strcmp(mat_str, "METAL") == 0)
	{
		metal = (t_material){MAT_METAL,
			(t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = metal;
	}
	else if (ft_strcmp(mat_str, "EMIT") == 0)
	{
		emit = (t_material){MAT_EMIT, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = emit;
	}
	else
		return (minirt_perror("Unknown material type"), false);
	return (true);
}

static bool	assign_color_based_on_mat(t_material *mat, char *color)
{
	if (mat->type == MAT_EMIT)
		return (assign_color(&mat->emit_color, color, 1));
	else
		return (assign_color(&mat->albedo, color, 1));
}

bool	assign_material(t_material *mat, char *line, int *i)
{
	char	*color;
	char	*mat_str;
	bool	err_check;

	color = extract_element(line, i, ' ');
	if (!color)
		return (false);
	mat_str = extract_element(line, i, ' ');
	if (!mat_str)
	{
		free(color);
		return (false);
	}
	if (!check_material_type(mat, mat_str))
	{
		free(color);
		free(mat_str);
		return (false);
	}
	err_check = assign_color_based_on_mat(mat, color);
	free(color);
	free(mat_str);
	return (err_check);
}
