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

double vec3_len_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double vec3_length(t_vec3 v)
{
	return (sqrt(vec3_len_squared(v)));
}

t_vec3 random_vec3(void)
{
	t_vec3 random;

	random = (t_vec3){random_double(), random_double(), random_double()};
	return (random);
}

t_vec3 random_vec3_mm(double min, double max)
{

	t_vec3 random;

	random = (t_vec3){random_double_mm(min, max), random_double_mm(min, max), random_double_mm(min, max)};
	return (random);
}

t_vec3	unit_vector(t_vec3 v)
{
    return (divide_by_scalar(v, vec3_length(v)));
}

t_vec3	random_unit_vector(void)
{
	while (true)
	{
		t_vec3 p = random_vec3_mm(-1,1);
		double lensq = vec3_len_squared(p);
		if (1e-160 < lensq && lensq <= 1)
		    return (divide_by_scalar(p, sqrt(lensq)));
	}
}

t_vec3 random_on_hemisphere(const t_vec3 *normal)
{
	t_vec3 on_unit_sphere = random_unit_vector();
	// In the same hemisphere as the normal
	if (dot_vec3(on_unit_sphere, *normal) > 0.0)
		return on_unit_sphere;
	else
		return multiply_by_scalar(on_unit_sphere, -1.0);
}
