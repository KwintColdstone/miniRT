#include "miniRT.h"

// Sphere list functions
bool	sphere_list_init(t_sphere_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->spheres = malloc(capacity * sizeof(t_sphere));
	if (!list->spheres)
		return (false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool	sphere_list_add(t_sphere_list *list, t_vec3 center, double radius, t_material material)
{
	if (!list || list->count >= list->capacity)
		return (false);

	list->spheres[list->count].center = center;
	list->spheres[list->count].radius = radius;
	list->spheres[list->count].mat = material;
	list->count += 1;
	return (true);
}

void	sphere_list_destroy(t_sphere_list *list)
{
	if (!list)
		return;
	
	free(list->spheres);
	list->spheres = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Quad list functions
bool	quad_list_init(t_quad_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	
	list->quads = malloc(capacity * sizeof(t_quad));
	if (!list->quads)
		return (false);
	
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool	quad_list_add(t_quad_list *list, const t_quad *quad)
{
	if (!list || !quad || list->count >= list->capacity)
		return (false);
	
	list->quads[list->count] = *quad;
	list->count += 1;
	return (true);
}

void	quad_list_destroy(t_quad_list *list)
{
	if (!list)
		return;
	
	free(list->quads);
	list->quads = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Cylinder list functions
bool	cylinder_list_init(t_cylinder_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	
	list->cylinders = malloc(capacity * sizeof(t_cylinder));
	if (!list->cylinders)
		return (false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool	cylinder_list_add(t_cylinder_list *list, const t_cylinder *cyl)
{
	if (!list || !cyl || list->count >= list->capacity)
		return (false);
	
	list->cylinders[list->count] = *cyl;
	list->count += 1;
	return (true);
}

void	cylinder_list_destroy(t_cylinder_list *list)
{
	if (!list)
		return;
	
	free(list->cylinders);
	list->cylinders = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Plane list functions
bool	plane_list_init(t_plane_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	
	list->planes = malloc(capacity * sizeof(t_plane));
	if (!list->planes)
		return (false);
	
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool	plane_list_add(t_plane_list *list, const t_plane *plane)
{
	if (!list || !plane || list->count >= list->capacity)
		return (false);
	
	list->planes[list->count] = *plane;
	list->count += 1;
	return (true);
}

void	plane_list_destroy(t_plane_list *list)
{
	if (!list)
		return;
	
	free(list->planes);
	list->planes = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Light list functions
bool	light_list_init(t_light_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	
	list->lights = malloc(capacity * sizeof(t_light));
	if (!list->lights)
		return (false);
	
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool	light_list_add(t_light_list *list, const t_light *light)
{
	if (!list || !light || list->count >= list->capacity)
		return (false);
	
	list->lights[list->count] = *light;
	list->count += 1;
	return (true);
}

void	light_list_destroy(t_light_list *list)
{
	if (!list)
		return;
	
	free(list->lights);
	list->lights = NULL;
	list->count = 0;
	list->capacity = 0;
}

bool	world_init(t_world *world, t_object_counter *c)
{
	if (!world)
	{
		return (false);
	}
	ft_memset(world, 0, sizeof(t_world));
	if (!sphere_list_init(&world->sp_list, c->sphere_cap))
	{
		return (false);
	}
	if (!quad_list_init(&world->qu_list, c->quad_cap))
	{
		return (false);
	}
	if (!cylinder_list_init(&world->cy_list, c->cylinder_cap))
	{
		return (false);
	}
	if (!plane_list_init(&world->pl_list, c->plane_cap))
	{
		return (false);
	}
	if (!light_list_init(&world->l_list, c->light_cap))
	{
		return (false);
	}
	//cornell_box_scene(world);
	return (true);
}

void world_destroy(t_world *world)
{
	if (!world)
		return;
	sphere_list_destroy(&world->sp_list);
	quad_list_destroy(&world->qu_list);
	cylinder_list_destroy(&world->cy_list);
	light_list_destroy(&world->l_list);
	plane_list_destroy(&world->pl_list);
}
