#include "miniRT.h"

bool sphere_list_init(t_sphere_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->centers = malloc(capacity * sizeof(t_vec3));
	list->materials = malloc(capacity * sizeof(t_material));
	list->radii = malloc(capacity * sizeof(double));
	if (!list->centers || !list->materials || !list->radii)
	{
		free(list->centers);
		free(list->materials);
		free(list->radii);
		return (false);
	}
	list->count = 0;
	list->capacity = capacity;
	return (true);
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
	free(list->materials);
	free(list->radii);
	list->centers = NULL;
	list->materials = NULL;
	list->radii = NULL;
}

bool plane_list_init(t_plane_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->corners = malloc(capacity * sizeof(t_vec3));
	list->u = malloc(capacity * sizeof(t_vec3));
	list->v = malloc(capacity * sizeof(t_vec3));
	list->materials = malloc(capacity * sizeof(t_material));
	if (!list->corners || !list->u || !list->v || !list->materials) {
		free(list->corners);
		free(list->u);
		free(list->v);
		free(list->materials);
		return (false);
	}
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool plane_list_add(t_plane_list *list, const t_plane *p)
{
	if (!list || list->count >= list->capacity)
		return (false);
	list->corners[list->count] = p->corner;
	list->u[list->count] = p->u;
	list->v[list->count] = p->v;
	list->materials[list->count] = p->mat;
	list->count += 1;
	return (true);
}

void	plane_list_destroy(t_plane_list *list)
{
	if (!list)
		return ;
	free(list->corners);
	free(list->u);
	free(list->v);
	free(list->materials);
	list->corners = NULL;
	list->u = NULL;
	list->v = NULL;
	list->materials = NULL;
}

bool	world_init(t_world *world)
{
	t_material blue_metal;
	t_material orange_metal;
	t_material blue_metal_fuzz;
	t_material orange_metal_fuzz;
	t_material red_lamb;

	blue_metal = (t_material){MAT_METAL, (t_vec3){0.1, 0.2, 0.5}, 0.1};
	orange_metal = (t_material){MAT_METAL, (t_vec3){0.8, 0.6, 0.2}, 0.1};
	blue_metal_fuzz = (t_material){MAT_METAL, (t_vec3){0.1, 0.2, 0.5}, 0.2};
	orange_metal_fuzz = (t_material){MAT_METAL, (t_vec3){0.8, 0.6, 0.2}, 0.8};
	red_lamb = (t_material){MAT_LAMBERTIAN, (t_vec3){0.37, 0.04, 0.08}, 0};
	if (!world)
	{
		return (false);
	}
	ft_memset(world, 0, sizeof(t_world));
	if (!sphere_list_init(&world->spheres, 10))
	{
		printf("from sphere list\n");
		return (false);
	}
	sphere_list_add(&world->spheres, (t_vec3){-1, 1, 5}, 0.5, blue_metal_fuzz);
	sphere_list_add(&world->spheres, (t_vec3){0,-100.5,-1}, 100, orange_metal);
	sphere_list_add(&world->spheres, (t_vec3){0, -1, 5}, 0.5, blue_metal);
	sphere_list_add(&world->spheres, (t_vec3){1, 0, 6}, 0.4, orange_metal_fuzz);

	if (!plane_list_init(&world->planes, 10))
	{
		printf("from plane list\n");
		return (false);
	}
	t_plane p1 = {(t_vec3){-3,-2, 5}, (t_vec3){0, 0,-4}, (t_vec3){0, 4, 0}, red_lamb};
	t_plane p2 = {(t_vec3){-2,-2, 0}, (t_vec3){4, 0, 0}, (t_vec3){0, 4, 0}, orange_metal};
	t_plane p3 = {(t_vec3){ 3,-2, 1}, (t_vec3){0, 0, 4}, (t_vec3){0, 4, 0}, orange_metal_fuzz};
	t_plane p4 = {(t_vec3){-2, 3, 1}, (t_vec3){4, 0, 0}, (t_vec3){0, 0, 4}, blue_metal};
	t_plane p5 = {(t_vec3){-2,-3, 5}, (t_vec3){4, 0, 0}, (t_vec3){0, 0,-4}, blue_metal_fuzz};
	plane_list_add(&world->planes, &p1);
	plane_list_add(&world->planes, &p2);
	plane_list_add(&world->planes, &p3);
	plane_list_add(&world->planes, &p4);
	plane_list_add(&world->planes, &p5);

	return (true);
}

void world_destroy(t_world *world)
{
	if (!world)
		return;
	sphere_list_destroy(&world->spheres);
	plane_list_destroy(&world->planes);
}
