#pragma  once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"

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
t_vec3 add_by_scalar(t_vec3 a, double b);
t_vec3 subtract_vec3(t_vec3 a, t_vec3 b);
t_vec3 subtract_by_scalar(t_vec3 a, double b);
t_vec3 multiply_vec3(t_vec3 a, t_vec3 b);
t_vec3 multiply_by_scalar(t_vec3 a, double b);
t_vec3 divide_vec3(t_vec3 a, t_vec3 b);
t_vec3 divide_by_scalar(t_vec3 a, double b);
double dot_vec3(t_vec3 a, t_vec3 b);
double vec3_length(t_vec3 v);
t_vec3 unit_vector(t_vec3 v);
