#include "miniRT.h"

void create_orthonormal_basis(const t_vec3 *axis, t_vec3 *u, t_vec3 *v, t_vec3 *w)
{
	*w = unit_vector(*axis);

	// Find an arbitrary vector perpendicular to w
	t_vec3 temp;
	if (fabs(w->x) > 0.9)
		temp = (t_vec3){0, 1, 0};
	else
		temp = (t_vec3){1, 0, 0};

	*u = subtract_vec3(temp, multiply_by_scalar(*w, dot_vec3(*w, temp)));
	*u = unit_vector(*u);
	*v = cross_vec3(*w, *u);
}

t_vec3 world_to_object_space(const t_vec3 *point, const t_vec3 *center,
                             const t_vec3 *u, const t_vec3 *v, const t_vec3 *w)
{
	t_vec3 translated = subtract_vec3(*point, *center);

	return (t_vec3){
		dot_vec3(translated, *u),
		dot_vec3(translated, *v),
		dot_vec3(translated, *w)
	};
}

t_vec3 object_to_world_space(const t_vec3 *point_obj, const t_vec3 *center,
                             const t_vec3 *u, const t_vec3 *v, const t_vec3 *w)
{
	t_vec3 world_point = add_vec3(
		multiply_by_scalar(*u, point_obj->x),
		multiply_by_scalar(*v, point_obj->y)
	);
	world_point = add_vec3(world_point, multiply_by_scalar(*w, point_obj->z));
	world_point = add_vec3(world_point, *center);

	return world_point;
}

t_vec3 world_to_object_direction(const t_vec3 *dir,
                                 const t_vec3 *u, const t_vec3 *v, const t_vec3 *w)
{
	return (t_vec3){
		dot_vec3(*dir, *u),
		dot_vec3(*dir, *v),
		dot_vec3(*dir, *w)
	};
}

t_vec3 object_to_world_direction(const t_vec3 *dir_obj,
                                 const t_vec3 *u, const t_vec3 *v, const t_vec3 *w)
{
	t_vec3 world_dir = add_vec3(
		multiply_by_scalar(*u, dir_obj->x),
		multiply_by_scalar(*v, dir_obj->y)
	);
	world_dir = add_vec3(world_dir, multiply_by_scalar(*w, dir_obj->z));

	return world_dir;
}
