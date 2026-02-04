#include "libft/libft.h"
#include "miniRT.h"
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <unistd.h>

bool	parse_ambient(t_camera *cam, char *line)
{
	double s;
	int i;

	i = 0;
	char *strength = extract_element(line, &i, ' ');
	if (!assign_float(&s, strength, 0.0, 1.0))
	{
		free(strength);
		return (false);
	}
	free(strength);

	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&cam->background, color, s))
	{
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
	if (!assign_vec3(&cam->camera_center, pos, DBL_MIN, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);

	char *orientation = extract_element(line, &i, ' ');
	if (!assign_vec3(&cam->orientation, orientation, -1.0, 1.0))
	{
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


bool	parse_light(t_world *world, char *line, int index)
{
	double s;
	double base_light_radius;
	int i;
	int light_multiplier;

	i = 0;
	light_multiplier = 10;
	base_light_radius = 5;
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->sp_list.spheres[index].center, pos, DBL_MIN, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);

	world->sp_list.spheres[index].radius = base_light_radius;

	char *strength = extract_element(line, &i, ' ');
	if (!assign_float(&s, strength, 0.0, 1.0))
	{
		free(strength);
		return (false);
	}
	s *= light_multiplier;
	free(strength);

	t_material base;
	base = (t_material){MAT_EMIT, (t_vec3){0, 0, 0}, 0};
	world->sp_list.spheres[index].mat = base;
	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->sp_list.spheres[index].mat.albedo, color, s))
	{
		free(color);
		return (false);
	}
	free(color);
	return (true);
}


bool	parse_sphere(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->sp_list.spheres[index].center, pos, DBL_MIN, DBL_MAX))
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
	world->sp_list.spheres[index].radius = ft_atof(diameter) / 2;
	free(diameter);
	if (world->sp_list.spheres[index].radius < 0
		|| world->sp_list.spheres[index].radius > INT_MAX)
		return (false);

	t_material base;
	base = (t_material){MAT_LAMBERTIAN, (t_vec3){0, 0, 0}, 0};
	world->sp_list.spheres[index].mat = base;
	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->sp_list.spheres[index].mat.albedo, color, 1))
	{
		free(color);
		return (false);
	}
	free(color);
	return (true);
}


bool	parse_plane(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	char *point = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->pl_list.planes[index].point, point, DBL_MIN, DBL_MAX))
	{
		free(point);
		return (false);
	}
	free(point);

	char *normal = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->pl_list.planes[index].normal, normal, -1.0, 1.0))
	{
		free(normal);
		return (false);
	}
	free(normal);

	t_material base;
	base = (t_material){MAT_LAMBERTIAN, (t_vec3){0, 0, 0}, 0};
	world->pl_list.planes[index].mat = base;
	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->pl_list.planes[index].mat.albedo, color, 1))
	{
		free(color);
		return (false);
	}
	free(color);
	return (true);
}


bool	parse_cylinder(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	char *pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->cy_list.cylinders[index].center, pos, DBL_MIN, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);

	char *axis = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->cy_list.cylinders[index].axis, axis, -1.0, 1.0))
	{
		free(axis);
		return (false);
	}
	free(axis);

	char *diameter = extract_element(line, &i, ' ');
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	world->cy_list.cylinders[index].radius = ft_atof(diameter) / 2;
	free(diameter);
	if (world->cy_list.cylinders[index].radius < 0
		|| world->cy_list.cylinders[index].radius > INT_MAX)
		return (false);

	char *height = extract_element(line, &i, ' ');
	if (!assign_float(&world->cy_list.cylinders[index].height, height, 0.0, INT_MAX))
	{
		free(height);
		return (false);
	}
	free(height);

	t_material base;
	base = (t_material){MAT_LAMBERTIAN, (t_vec3){0, 0, 0}, 0};
	world->cy_list.cylinders[index].mat = base;
	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->cy_list.cylinders[index].mat.albedo, color, 1))
	{
		free(color);
		return (false);
	}
	free(color);
	return (true);
}


bool	parse_quad(t_world *world, char *line, int index)
{
	int i;

	i = 0;
	char *corner = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->qu_list.quads[index].corner, corner, DBL_MIN, DBL_MAX))
	{
		free(corner);
		return (false);
	}
	free(corner);

	char *u = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->qu_list.quads[index].u, u, DBL_MIN, DBL_MAX))
	{
		free(u);
		return (false);
	}
	free(u);

	char *v = extract_element(line, &i, ' ');
	if (!assign_vec3(&world->qu_list.quads[index].v, v, DBL_MIN, DBL_MAX))
	{
		free(v);
		return (false);
	}
	free(v);

	t_material base;
	base = (t_material){MAT_LAMBERTIAN, (t_vec3){0, 0, 0}, 0};
	world->qu_list.quads[index].mat = base;
	char *color = extract_element(line, &i, ' ');
	if (!assign_color(&world->qu_list.quads[index].mat.albedo, color, 1))
	{
		free(color);
		return (false);
	}
	free(color);
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
		if (line[i])
		{
			if (line[i] == 'A')
			{
				succes = parse_ambient(cam, &line[i]);
			}
			else if (line[i] == 'C')
			{
				succes = parse_camera(cam, &line[i]);
			}
			else if (line[i] == 'L')
			{
				succes = parse_light(world, &line[i], world->sp_list.count);
				if (succes)
					world->sp_list.count += 1;
			}
			else if (line[i] == 's' && line[i+1] == 'p')
			{
				succes = parse_sphere(world, &line[i], world->sp_list.count);
				if (succes)
					world->sp_list.count += 1;
			}
			else if (line[i] == 'p' && line[i+1] == 'l')
			{
				succes = parse_plane(world, &line[i], world->pl_list.count);
				if (succes)
					world->pl_list.count += 1;
			}
			else if (line[i] == 'c' && line[i+1] == 'y')
			{
				succes = parse_cylinder(world, &line[i], world->cy_list.count);
				if (succes)
					world->cy_list.count += 1;
			}
			else if (line[i] == 'q' && line[i+1] == 'u')
			{
				succes = parse_quad(world, &line[i], world->qu_list.count);
				if (succes)
					world->qu_list.count += 1;
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

bool	parse(char *file, t_world *world, t_camera *cam)
{
	t_object_counter	counter;
	int fd;

	fd = open(file, O_RDONLY);
	if (fd <= -1)
	{
		ft_putstr_fd("failed to open file\n", STDERR_FILENO);
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
