#include "miniRT.h"
/*
void	quads_and_spheres(t_world *world)
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

	t_quad p1 = {(t_vec3){-3,-2, 5}, (t_vec3){0, 0,-4}, (t_vec3){0, 4, 0}, red_lamb};
	t_quad p2 = {(t_vec3){-2,-2, 0}, (t_vec3){4, 0, 0}, (t_vec3){0, 4, 0}, orange_metal};
	t_quad p3 = {(t_vec3){ 3,-2, 1}, (t_vec3){0, 0, 4}, (t_vec3){0, 4, 0}, orange_metal_fuzz};
	t_quad p4 = {(t_vec3){-2, 3, 1}, (t_vec3){4, 0, 0}, (t_vec3){0, 0, 4}, blue_metal};
	t_quad p5 = {(t_vec3){-2,-3, 5}, (t_vec3){4, 0, 0}, (t_vec3){0, 0,-4}, blue_metal_fuzz};
	quad_list_add(&world->quads, &p1);
	quad_list_add(&world->quads, &p2);
	quad_list_add(&world->quads, &p3);
	quad_list_add(&world->quads, &p4);
	quad_list_add(&world->quads, &p5);
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

void	create_box(t_world *world, const t_vec3 a, const t_vec3 b, const t_material mat)
{
	// Construct the two opposite vertices with the minimum and maximum coordinates.
	t_vec3 min = (t_vec3){fmin(a.x,b.x), fmin(a.y,b.y), fmin(a.z,b.z)};
	t_vec3 max = (t_vec3){fmax(a.x,b.x), fmax(a.y,b.y), fmax(a.z,b.z)};

	t_vec3 dx = (t_vec3){max.x - min.x, 0, 0};
	t_vec3 dy = (t_vec3){0, max.y - min.y, 0};
	t_vec3 dz = (t_vec3){0, 0, max.z - min.z};

	t_quad front = {
		.corner = (t_vec3){min.x, min.y, max.z},
		.u = dx,
		.v = dy,
		.mat = mat
	};
	t_quad right = {
		.corner = (t_vec3){max.x, min.y, max.z},
		.u = multiply_by_scalar(dz, -1),
		.v = dx,
		.mat = mat
	};
	t_quad back = {
		.corner = (t_vec3){max.x, min.y, min.z},
		.u = multiply_by_scalar(dx, -1),
		.v = dy,
		.mat = mat
	};
	t_quad left = {
		.corner = (t_vec3){min.x, min.y, min.z},
		.u = dz,
		.v = dy,
		.mat = mat
	};
	t_quad top = {
		.corner = (t_vec3){min.x, max.y, max.z},
		.u = dx,
		.v = multiply_by_scalar(dz, -1),
		.mat = mat
	};
	t_quad bottom = {
		.corner = (t_vec3){min.x, min.y, min.z},
		.u = dx,
		.v = dz,
		.mat = mat
	};
	quad_list_add(&world->quads, &front);
	quad_list_add(&world->quads, &right);
	quad_list_add(&world->quads, &back);
	quad_list_add(&world->quads, &left);
	quad_list_add(&world->quads, &top);
	quad_list_add(&world->quads, &bottom);
}

void	cornell_box_scene(t_world *world)
{
	t_material red = make_lambertian((t_vec3){0.65, 0.05, 0.05});
	t_material white = make_lambertian((t_vec3){0.73, 0.73, 0.73});
	t_material green = make_lambertian((t_vec3){0.12, 0.45, 0.15});
	t_material light = make_light((t_vec3){10, 10, 10});
	t_quad green_wall = {
		.corner = {5.55, 0, 0},
		.u = {0, 5.55, 0},
		.v = {0, 0, 5.55},
		.mat = green
	};
	t_quad red_wall = {
		.corner = {0, 0, 0},
		.u = {0, 5.55, 0},
		.v = {0, 0, 5.55},
		.mat = red
	};
	t_quad ceiling_light = {
		.corner = {1.13, 5.54, 1.27},
		.u = {3.30, 0, 0},
		.v = {0, 0, 3.05},
		.mat = light
	};
	t_quad floor = {
		.corner = {0, 0, 0},
		.u = {5.55, 0, 0},
		.v = {0, 0, 5.55},
		.mat = white
	};
	t_quad ceiling = {
		.corner = {5.55, 5.55, 5.55},
		.u = {-5.55, 0, 0},
		.v = {0, 0, -5.55},
		.mat = white
	};
	t_quad back_wall = {
		.corner = {0, 0, 5.55},
		.u = {5.55, 0, 0},
		.v = {0, 5.55, 0},
		.mat = white
	};
	quad_list_add(&world->quads, &green_wall);
	quad_list_add(&world->quads, &red_wall);
	quad_list_add(&world->quads, &ceiling_light);
	quad_list_add(&world->quads, &floor);
	quad_list_add(&world->quads, &ceiling);
	quad_list_add(&world->quads, &back_wall);

	t_material metal = make_metal((t_vec3){0.8, 0.8, 0.8}, 0.0);
	t_material metal_fuzz = make_metal((t_vec3){0.12, 0.45, 0.15}, 0.8);
	sphere_list_add(&world->spheres, (t_vec3){1.77, 1.0, 4.44}, 1.0, metal);
	t_cylinder c = {
		.height = 1,
		.radius = 0.5,
		.mat = metal_fuzz,
		.center = {4, 1, 0}
	};
	cylinder_list_add(&world->cylinders, &c);
	create_box(world, (t_vec3){1.30, 0, 0.65}, (t_vec3){2.95, 1.65, 2.30}, white);
	create_box(world, (t_vec3){2.65, 0, 2.95}, (t_vec3){4.30, 3.30, 4.60}, white);
}
*/
