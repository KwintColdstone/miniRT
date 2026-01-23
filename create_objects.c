#include "miniRT.h"

bool sphere_list_init(t_sphere_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->centers = malloc(capacity * sizeof(t_vec3));
	list->materials = malloc(capacity * sizeof(t_material));
	list->radii = malloc(capacity * sizeof(double));
	if (!list->centers || !list->radii) {
		free(list->centers);
		free(list->radii);
		free(list->materials);
		return (false);
	}
	list->count = 0;
	list->capacity = capacity;
	return (list);
}

bool sphere_list_add(t_sphere_list *list, t_vec3 center, double radius, t_material material)
{
	if (!list || list->count >= list->capacity)
		return (false);
	list->centers[list->count] = center;
	list->radii[list->count] = radius;
	list->materials[list->count] = material;
	list->count += 1;
	return (true);
}

void	sphere_list_destroy(t_sphere_list *list)
{
	if (!list)
		return ;
	free(list->centers);
	free(list->radii);
	list->centers = NULL;
	list->radii = NULL;
}

bool	world_init(t_world *world)
{
	t_material blue_metal;
	t_material orange_metal;
	t_material blue_metal_fuzz;
	t_material orange_metal_fuzz;
	t_material red_lamb;

	blue_metal = (t_material){MAT_METAL, (t_vec3){0.1, 0.2, 0.5}, 0, 0};
	orange_metal = (t_material){MAT_METAL, (t_vec3){0.8, 0.6, 0.2}, 0, 0};
	blue_metal_fuzz = (t_material){MAT_METAL, (t_vec3){0.1, 0.2, 0.5}, 0.2, 0};
	orange_metal_fuzz = (t_material){MAT_METAL, (t_vec3){0.8, 0.6, 0.2}, 0.5, 0};
	red_lamb = (t_material){MAT_LAMBERTIAN, (t_vec3){0.37, 0.04, 0.08}, 0, 0};
	if (!world)
	{
		return (false);
	}
	ft_memset(world, 0, sizeof(t_world));
	if (!sphere_list_init(&world->spheres, 10))
	{
		return (false);
	}
	sphere_list_add(&world->spheres, (t_vec3){0, 0, -1.2}, 0.5, red_lamb);
	sphere_list_add(&world->spheres, (t_vec3){0,-100.5,-1}, 100, orange_metal);
	sphere_list_add(&world->spheres, (t_vec3){1, 0, -1}, 0.5, blue_metal);
	sphere_list_add(&world->spheres, (t_vec3){-1, 0, -1}, 0.4, orange_metal_fuzz);
	return (true);
}

void world_destroy(t_world *world)
{
	if (!world) return;
	sphere_list_destroy(&world->spheres);
}
