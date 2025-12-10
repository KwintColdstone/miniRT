#pragma  once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 add_by_vec3(t_vec3 a, double b);
t_vec3 minus_vec3(t_vec3 a, t_vec3 b);
t_vec3 minus_by_vec3(t_vec3 a, double b);
t_vec3 multiply_vec3(t_vec3 a, t_vec3 b);
t_vec3 multiply_by_vec3(t_vec3 a, double b);
t_vec3 divide_vec3(t_vec3 a, t_vec3 b);
t_vec3 divide_by_vec3(t_vec3 a, double b);
