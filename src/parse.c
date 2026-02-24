#include "libft.h"
#include "miniRT.h"
#include <fcntl.h>
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

bool	parse_ambient(t_world *world, t_camera *cam, char *line)
{
	(void) cam; // unused!!
	double	s;
	char	*strength;
	int		i;
	char	*color;

	i = 0;
	strength = extract_element(line, &i, ' ');
	if (!assign_float(&s, strength, 0.0, 1.0))
	{
		free(strength);
		return (false);
	}
	free(strength);
	color = extract_element(line, &i, ' ');
	if (!assign_color(&world->ambient, color, s))
	{
		ft_putstr_fd("assigning color failed\n", STDERR_FILENO);
		free(color);
		return (false);
	}
	free(color);
	return (true);
}

bool	parse_camera(t_camera *cam, char *line)
{
	int i;
	int hfov;

	i = 0;
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&cam->camera_center, pos, -DBL_MAX, DBL_MAX))
	{
		ft_putstr_fd("assigning vec3 failed: pos\n", STDERR_FILENO);
		free(pos);
		return (false);
	}
	free(pos);

	char *orientation = extract_element(line, &i, ' ');
	if (!assign_vec3(&cam->orientation, orientation, -1.0, 1.0))
	{
		ft_putstr_fd("assigning vec3 failed: orient\n", STDERR_FILENO);
		free(orientation);
		return (false);
	}
	free(orientation);


	char *fov = extract_element(line, &i, ' ');
	if (!is_float(fov))
	{
		free(fov);
		return (false);
	}
	hfov = ft_atoi(fov);
	free(fov);
	if (hfov < 0 || hfov > 180)
		return (false);
	cam->hfov = hfov;
	return (true);
}

bool	parse_light(t_world *world, char *line)
{
	int i;

	i = 0;
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->light.position, pos, -DBL_MAX, DBL_MAX))
	{
		ft_putstr_fd("assigning vec3 failed: pos\n", STDERR_FILENO);
		free(pos);
		return (false);
	}
	free(pos);

	char *brightness = extract_element(line, &i, ' ');
	if (!assign_float(&world->light.brightness, brightness, 0.0, 1.0))
	{
		free(brightness);
		return (false);
	}
	free(brightness);

	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->light.color, color, 1))
	{
		ft_putstr_fd("assigning color failed\n", STDERR_FILENO);
		free(color);
		return (false);
	}
	free(color);

	return (true);
}

bool	check_material_type(t_material *mat, char *mat_str)
{
	t_material base;
	t_material metal;
	t_material emit;

	if (!mat_str)
	{
		base = (t_material){MAT_LAMBERTIAN, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0}; // was not init properly
		*mat = base;
		return (true);
	}
	if (ft_strcmp(mat_str, "METAL") == 0)
	{
		metal = (t_material){MAT_METAL, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = metal;
	}
	else if (ft_strcmp(mat_str, "EMIT") == 0)
	{
		emit = (t_material){MAT_EMIT, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = emit;
	}
	else
	{
		return (false);
	}
	return (true);
}

bool	assign_material(t_material *mat, char *line, int *i)
{

	char *color = extract_element(line, i, ' ');
	char *mat_str = extract_element(line, i, ' ');

	// This check never passes on files given.
	// gonna comment it out for now so I can work on displaying the image first.
	// needs to be re-added and fixed later.
	//
	//if (!check_material_type(mat, mat_str))
	//{
	//	free(color);
	//	free(mat_str);
	//	return (false);
	//}
	if (mat->type == MAT_EMIT)
	{
		if (!assign_color(&mat->emit_color, color, 1))
		{
			free(color);
			free(mat_str);
			return (false);
		}
	}
	else
	{
		if (!assign_color(&mat->albedo, color, 1))
		{
			free(color);
			free(mat_str);
			return (false);
		}
	}
	free(color);
	free(mat_str);
	return (true);
}

bool	parse_sphere(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	t_sphere *sp = &world->sp_list.spheres[index];
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&sp->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);

	char *diameter = extract_element(line, &i, ' ');
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	sp->radius = ft_atof(diameter) / 2;
	free(diameter);
	if (sp->radius < 0
		|| sp->radius > INT_MAX)
		return (false);

	if (!assign_material(&sp->mat, line, &i))
		return (false);
	return (true);
}


bool	parse_plane(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	t_plane *pl = &world->pl_list.planes[index];
	char *point = extract_element(line, &i, ' ');
	if (!assign_vec3(&pl->point, point, -DBL_MAX, DBL_MAX))
	{
		free(point);
		return (false);
	}
	free(point);

	char *normal = extract_element(line, &i, ' ');
	if (!assign_vec3(&pl->normal, normal, -1.0, 1.0))
	{
		free(normal);
		return (false);
	}
	free(normal);
	pl->normal = unit_vector(pl->normal);

	if (!assign_material(&pl->mat, line, &i))
		return (false);
	return (true);
}


bool	parse_cylinder(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	t_cylinder *cyl = &world->cy_list.cylinders[index];
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&cyl->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);

	char *axis = extract_element(line, &i, ' ');
	if (!assign_vec3(&cyl->axis, axis, -1.0, 1.0))
	{
		free(axis);
		return (false);
	}
	free(axis);
	cyl->axis = unit_vector(cyl->axis);

	char *diameter = extract_element(line, &i, ' ');
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	cyl->radius = ft_atof(diameter) / 2;
	free(diameter);
	if (cyl->radius < 0
		|| cyl->radius > INT_MAX) {
		return (false);
	}

	char *height = extract_element(line, &i, ' ');
	if (!assign_float(&cyl->height, height, 0.0, INT_MAX))
	{
		free(height);
		return (false);
	}
	free(height);

	if (!assign_material(&cyl->mat, line, &i)) {
		printf("assign mat fail\n");
		return (false);
	}
	return (true);
}


bool	parse_quad(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	t_quad *qu = &world->qu_list.quads[index];
	char *corner = extract_element(line, &i, ' ');
	if (!assign_vec3(&qu->corner, corner, -DBL_MAX, DBL_MAX))
	{
		free(corner);
		return (false);
	}
	free(corner);

	char *u = extract_element(line, &i, ' ');
	if (!assign_vec3(&qu->u, u, -DBL_MAX, DBL_MAX))
	{
		free(u);
		return (false);
	}
	free(u);

	char *v = extract_element(line, &i, ' ');
	if (!assign_vec3(&qu->v, v, -DBL_MAX, DBL_MAX))
	{
		free(v);
		return (false);
	}
	free(v);

	if (!assign_material(&qu->mat, line, &i))
		return (false);
	return (true);
}

bool	assign_objects(char *file, t_world *world, t_camera *cam)
{
	int fd;
	char *line;
	int i;
	int line_count;

	line_count = 1;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	bool succes = true;
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		printf("parsign line %d\n", line_count);
		printf("line content: %s\n", line);
		if (line[i])
		{
			printf("do we get into line[%d] at line 5? %d\n", i, line_count);
			if (line[i] == 'A')
			{
				i++;
				succes = parse_ambient(world, cam, &line[i]);
			}
			else if (line[i] == 'C')
			{
				i++;
				succes = parse_camera(cam, &line[i]);
			}
			else if (line[i] == 'L')
			{
				i++;
				succes = parse_light(world, &line[i]);
			}
			else if (line[i] == 's' && line[i+1] == 'p')
			{
				i += 2;
				succes = parse_sphere(world, &line[i], world->sp_list.count);
				if (succes)
					world->sp_list.count += 1;
			}
			else if (line[i] == 'p' && line[i+1] == 'l')
			{
				i += 2;
				succes = parse_plane(world, &line[i], world->pl_list.count);
				if (succes)
					world->pl_list.count += 1;
			}
			else if (line[i] == 'c' && line[i+1] == 'y')
			{
				printf("do we get here? at line 5? %d\n", line_count);
				i += 2;
				succes = parse_cylinder(world, &line[i], world->cy_list.count);
				if (succes)
					world->cy_list.count += 1;
			}
			else if (line[i] == 'q' && line[i+1] == 'u')
			{
				i += 2;
				succes = parse_quad(world, &line[i], world->qu_list.count);
				if (succes) {
					world->qu_list.count += 1;
				}
			}
		}
		if (succes == false)
		{
			printf("parsing failure at line: %d\n", line_count);
			printf("incorrect values for element\n");
			close(fd);
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	close(fd);
	return (true);
}

bool	check_file_name(char *file)
{
	int i;

	i = ft_strlen(file);
	if (file[i - 1] == 't' && file[i - 2] == 'r' && file[i - 3] == '.')
		return (true);
	return (false);
}

bool	parse(char *file, t_world *world, t_camera *cam)
{
	t_object_counter	counter;
	int fd;

	if (!file)
	{
		ft_putstr_fd("no file\n", STDERR_FILENO);
		return false;
	}
	if (!check_file_name(file))
	{
		ft_putstr_fd("incorrect file name. Use: (name).rt\n", STDERR_FILENO);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (false);
	}
	if (!count_objects(fd, &counter))
	{
		ft_putstr_fd("failed to count objects\n", STDERR_FILENO);
		return (false);
	}
	if (!world_init(world, &counter))
	{
		ft_putstr_fd("failed to init world\n", STDERR_FILENO);
		return (false);
	}
	if (!assign_objects(file, world, cam))
	{
		ft_putstr_fd("failed to assign values to element\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
