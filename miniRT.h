#pragma once

#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

typedef struct s_vec3 {
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_ray {
	t_vec3 origin;
	t_vec3 direction;
}	t_ray;

typedef enum e_material_type {
	MAT_LAMBERTIAN,
	MAT_METAL,
	MAT_EMIT,
}	t_material_type;

typedef struct s_material
{
	t_material_type	type;
	t_vec3		albedo;
	t_vec3		emit_color;
	double		fuzz;
}	t_material;

typedef struct	s_quad
{
	t_vec3		corner;
	t_vec3		u;
	t_vec3		v;
	t_material	mat;
}	t_quad;

typedef struct	s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_material	mat;
}	t_plane;

typedef struct	s_sphere
{
	t_vec3	center;
	t_material mat;
	double	radius;
}	t_sphere;

typedef struct	s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	t_material mat;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_light
{
	t_vec3	center;
	t_material mat;
	double	radius;
	double	strength;
}	t_light;

typedef struct s_ambient
{
	t_vec3	color;
	double	strength;
}	t_ambient;

typedef struct s_sphere_list
{
	t_sphere	*spheres;
	int		count;
	int		capacity;
}	t_sphere_list;

typedef struct s_quad_list
{
	t_quad	*quads;
	int count;
	int capacity;
}	t_quad_list;

typedef struct s_plane_list
{
	t_plane	*planes;
	int count;
	int capacity;
}	t_plane_list;

typedef struct s_cylinder_list
{
	t_cylinder	*cylinders;
	int count;
	int capacity;
}	t_cylinder_list;


typedef struct s_light_list
{
	t_light	*lights;
	t_ambient	amb;
	int count;
	int capacity;
}	t_light_list;

typedef struct s_world {
	t_sphere_list sp_list;
	t_quad_list qu_list;
	t_plane_list pl_list;
	t_cylinder_list cy_list;
	t_light_list	l_list;
}	t_world;

typedef struct s_hit_record {
	t_vec3	position;
	t_vec3	normal;
	t_material mat;
	double	t;
	bool	front_face;
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
	t_vec3	orientation;
	t_vec3	v_up;
	t_vec3	background;
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

typedef struct s_object_counter
{
	int sphere_cap;
	int quad_cap;
	int plane_cap;
	int cylinder_cap;
	int light_cap;
}	t_object_counter;

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
t_vec3	reflect(const t_vec3 *v, const t_vec3 *n);
bool	near_zero(t_vec3 v);

// ray.c
t_vec3	ray_at(const t_ray *ray, double t);

// hit_objects.c
bool	sphere_hit(const t_sphere *s, const t_ray *r, t_interval ray_t, t_hit_record *rec);
bool	quad_hit(const t_quad *p, const t_ray *r, t_interval ray_t, t_hit_record *rec);
bool	plane_hit(const t_plane *p, const t_ray *r, t_interval ray_t, t_hit_record *rec);
bool	cylinder_hit(const t_cylinder *cl, const t_ray *r, t_interval ray_t, t_hit_record *rec);

// world_hit.c
bool	world_hit(const t_world* world, const t_ray* r,
	t_interval ray_t, t_hit_record* rec);

// utils.c
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_mm(double min, double max);
double	clamp_interval(double x, t_interval i);
bool	interval_contains(t_interval i, double x);

// create_objects.c

// init.c
bool	sphere_list_init(t_sphere_list *list, int capacity);
bool	sphere_list_add(t_sphere_list *list, t_vec3 center, double radius, t_material material);
void	sphere_list_destroy(t_sphere_list *list);
bool	quad_list_init(t_quad_list *list, int capacity);
bool	quad_list_add(t_quad_list *list, const t_quad *quad);
void	quad_list_destroy(t_quad_list *list);
bool	cylinder_list_init(t_cylinder_list *list, int capacity);
bool	cylinder_list_add(t_cylinder_list *list, const t_cylinder *cyl);
void	cylinder_list_destroy(t_cylinder_list *list);
bool	plane_list_init(t_plane_list *list, int capacity);
bool	plane_list_add(t_plane_list *list, const t_plane *plane);
void	plane_list_destroy(t_plane_list *list);
bool	light_list_init(t_light_list *list, int capacity);
bool	light_list_add(t_light_list *list, const t_light *light);
void	light_list_destroy(t_light_list *list);
bool	world_init(t_world *world, t_object_counter *c);
void	world_destroy(t_world *world);

// camera.c
bool	camera_init(t_camera *cam);

// render.c
bool render(t_camera *cam, t_world *world);

// material.c
bool lambertian_scatter(const t_ray *r_in, const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
bool metal_scatter(const t_ray *r_in, const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);

// parse.c
bool	parse(char *file, t_world *world, t_camera *cam);

// parse_utils.c
bool	is_float(char *s);
char	*subtract_element(char *s, int *i, char delim);
bool	assign_vec3(t_vec3 *v, char *s, double min, double max);
bool	assign_float(double *f, char *s, double min, double max);
bool	count_objects(int fd, t_object_counter *counts);
