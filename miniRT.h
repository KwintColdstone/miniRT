#pragma once

#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_vec3 {
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_ray {
	t_vec3 origin;
	t_vec3 direction;
}	t_ray;

typedef struct s_sphere_list {
	t_vec3* centers;
	double* radii;
	int count;
	int capacity;
}	t_sphere_list;

typedef struct s_plane_list {
	t_vec3* points;
	t_vec3* normals;
	int count;
	int capacity;
}	t_plane_list;

typedef struct s_cylinder_list {
	t_vec3* centers;
	double* radii;
	double* heights;
	int count;
	int capacity;
}	t_cylinder_list;

typedef struct s_world {
	t_sphere_list spheres;
	t_plane_list planes;
	t_cylinder_list cylinders; }	t_world;

typedef struct s_hit_record {
	t_vec3 position;
	t_vec3 normal;
	double t; // Distance along ray
}	t_hit_record;

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

typedef struct s_camera
{
	t_vec3	camera_center;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_vec3	pixel00_loc;
	t_vec3	look_from;
	t_vec3	look_at;
	t_vec3	v_up;
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	double	aspect_ratio;
    int		image_width;
    int		image_height;
    int		samples_per_pixel;
    int		max_depth;
    int		hfov;
}	t_camera;

//vec3.c
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
t_vec3	add_by_scalar(t_vec3 a, double b);
t_vec3	subtract_vec3(t_vec3 a, t_vec3 b);
t_vec3	subtract_by_scalar(t_vec3 a, double b);
t_vec3	multiply_vec3(t_vec3 a, t_vec3 b);
t_vec3	multiply_by_scalar(t_vec3 a, double b);
t_vec3	divide_vec3(t_vec3 a, t_vec3 b);
t_vec3	divide_by_scalar(t_vec3 a, double b);
double	dot_vec3(t_vec3 a, t_vec3 b);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
double	vec3_len_squared(t_vec3 v);
double	vec3_length(t_vec3 v);
t_vec3	random_vec3(void);
t_vec3	random_vec3_mm(double min, double max);
t_vec3	unit_vector(t_vec3 v);
t_vec3	random_unit_vector(void);
t_vec3	random_on_hemisphere(const t_vec3 *normal);

// ray.c
t_vec3	ray_at(const t_ray *ray, double t);

// hit_objects.c
bool	sphere_hit(const t_vec3 *center, double radius, const t_ray *r, t_interval ray_t, t_hit_record *rec);

// world_hit.c
bool	world_hit(const t_world* world, const t_ray* r,
	t_interval ray_t, t_hit_record* rec);

// utils.c
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_mm(double min, double max);
double	clamp_interval(double x, t_interval i);

// create_objects.c
bool	sphere_list_init(t_sphere_list *list, int capacity);
bool	sphere_list_add(t_sphere_list *list, t_vec3 center, double radius);
void	sphere_list_destroy(t_sphere_list *list);
bool	world_init(t_world *world);
void	world_destroy(t_world *world);

// camera
bool	camera_init(t_camera *cam);

// render
bool render(t_camera *cam, t_world *world);
