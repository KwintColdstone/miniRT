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

bool cylinder_list_init(t_cylinder_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->centers = malloc(capacity * sizeof(t_vec3));
	list->materials = malloc(capacity * sizeof(t_material));
	list->radii = malloc(capacity * sizeof(double));
	list->heights = malloc(capacity * sizeof(double));
	if (!list->centers || !list->materials || !list->radii || !list->heights)
	{
		free(list->centers);
		free(list->materials);
		free(list->radii);
		free(list->heights);
		return (false);
	}
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

bool cylinder_list_add(t_cylinder_list *list, const t_cylinder *c)
{
	if (!list || list->count >= list->capacity)
		return (false);
	list->centers[list->count] = c->center;
	list->materials[list->count] = c->mat;
	list->radii[list->count] = c->radius;
	list->heights[list->count] = c->height;
	list->count += 1;
	return (true);
}

void	cylinder_list_destroy(t_cylinder_list *list)
{
	if (!list)
		return ;
	free(list->centers);
	free(list->materials);
	free(list->radii);
	free(list->heights);
	list->centers = NULL;
	list->materials = NULL;
	list->radii = NULL;
	list->heights = NULL;
}

void	planes_and_spheres(t_world *world)
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
	sphere_list_add(&world->spheres, (t_vec3){-1, 1, 5}, 0.5, blue_metal_fuzz);
	sphere_list_add(&world->spheres, (t_vec3){0,-100.5,-1}, 100, orange_metal);
	sphere_list_add(&world->spheres, (t_vec3){0, -1, 5}, 0.5, blue_metal);
	sphere_list_add(&world->spheres, (t_vec3){1, 0, 6}, 0.4, orange_metal_fuzz);

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
}



t_material make_lambertian(t_vec3 albedo)
{
	return (t_material){MAT_LAMBERTIAN, albedo, (t_vec3){0, 0, 0}, 0.0 };
}

t_material make_metal(t_vec3 albedo, double fuzz)
{
	return (t_material){MAT_METAL, albedo, (t_vec3){0, 0, 0}, fuzz};
}

t_material make_light(t_vec3 emit_color)
{
	return (t_material){MAT_EMIT, (t_vec3){0, 0, 0}, emit_color, 0.0};
}

void cornell_box_scene(t_world *world)
{
	t_material red = make_lambertian((t_vec3){0.65, 0.05, 0.05});
	t_material white = make_lambertian((t_vec3){0.73, 0.73, 0.73});
	t_material green = make_lambertian((t_vec3){0.12, 0.45, 0.15});
	t_material light = make_light((t_vec3){15, 15, 15}); // Very bright light
	t_plane green_wall = {
		.corner = {5.55, 0, 0},      // Scaled: 555/100
		.u = {0, 5.55, 0},           // Scaled: (0,555,0)/100
		.v = {0, 0, 5.55},           // Scaled: (0,0,555)/100
		.mat = green
	};
	t_plane red_wall = {
		.corner = {0, 0, 0},
		.u = {0, 5.55, 0},
		.v = {0, 0, 5.55},
		.mat = red
	};
	t_plane ceiling_light = {
		.corner = {1.13, 5.54, 1.27},     // 343/100, 554/100, 332/100
		.u = {3.30, 0, 0},               // -130/100
		.v = {0, 0, 3.05},               // -105/100
		.mat = light
	};
	t_plane floor = {
		.corner = {0, 0, 0},
		.u = {5.55, 0, 0},
		.v = {0, 0, 5.55},
		.mat = white
	};
	t_plane ceiling = {
		.corner = {5.55, 5.55, 5.55},
		.u = {-5.55, 0, 0},
		.v = {0, 0, -5.55},
		.mat = white
	};
	t_plane back_wall = {
		.corner = {0, 0, 5.55},
		.u = {5.55, 0, 0},
		.v = {0, 5.55, 0},
		.mat = white
	};
	plane_list_add(&world->planes, &green_wall);
	plane_list_add(&world->planes, &red_wall);
	plane_list_add(&world->planes, &ceiling_light);
	plane_list_add(&world->planes, &floor);
	plane_list_add(&world->planes, &ceiling);
	plane_list_add(&world->planes, &back_wall);
	t_material metal = make_metal((t_vec3){0.8, 0.8, 0.8}, 0.0);
	sphere_list_add(&world->spheres, (t_vec3){1.77, 1.0, 4.44}, 1.0, metal); // Metal sphere
	t_cylinder c = {
		.height = 2,
		.radius = 1,
		.mat = metal,
		.center = {4, 1, 1}
	};
	cylinder_list_add(&world->cylinders, &c);
}

bool	world_init(t_world *world)
{
	if (!world)
	{
		return (false);
	}
	ft_memset(world, 0, sizeof(t_world));
	if (!sphere_list_init(&world->spheres, 10))
	{
		return (false);
	}
	if (!plane_list_init(&world->planes, 10))
	{
		return (false);
	}
	if (!cylinder_list_init(&world->cylinders, 10))
	{
		return (false);
	}
	cornell_box_scene(world);
	return (true);
}

void world_destroy(t_world *world)
{
	if (!world)
		return;
	sphere_list_destroy(&world->spheres);
	plane_list_destroy(&world->planes);
	cylinder_list_destroy(&world->cylinders);
}
