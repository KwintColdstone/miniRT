#include "miniRT.h"

t_vec3 ray_at(const t_ray *ray, double t)
{
	t_vec3 dir;
	dir = multiply_by_scalar(ray->direction, t);
	return (add_vec3(ray->origin, dir));
}
