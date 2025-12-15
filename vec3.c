#include "miniRT.h"

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vec3 add_by_scalar(t_vec3 a, double b)
{
	t_vec3 sum;

	sum.x = a.x + b;
	sum.y = a.y + b;
	sum.z = a.z + b;
	return (sum);
}

t_vec3 subtract_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 sum;

	sum.x = a.x - b.x;
	sum.y = a.y - b.y;
	sum.z = a.z - b.z;
	return (sum);
}

t_vec3 subtract_by_scalar(t_vec3 a, double b)
{
	t_vec3 sum;

	sum.x = a.x - b;
	sum.y = a.y - b;
	sum.z = a.z - b;
	return (sum);
}

t_vec3 multiply_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 sum;

	sum.x = a.x * b.x;
	sum.y = a.y * b.y;
	sum.z = a.z * b.z;
	return (sum);
}

t_vec3 multiply_by_scalar(t_vec3 a, double b)
{
	t_vec3 sum;

	sum.x = a.x * b;
	sum.y = a.y * b;
	sum.z = a.z * b;
	return (sum);
}

t_vec3 divide_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 sum;

	sum.x = a.x / b.x;
	sum.y = a.y / b.y;
	sum.z = a.z / b.z;
	return (sum);
}

t_vec3 divide_by_scalar(t_vec3 a, double b)
{
	t_vec3 sum;

	sum.x = a.x / b;
	sum.y = a.y / b;
	sum.z = a.z / b;
	return (sum);
}

double dot_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static double length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double vec3_length(t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

t_vec3 unit_vector(t_vec3 v)
{
    return (divide_by_scalar(v, vec3_length(v)));
}
