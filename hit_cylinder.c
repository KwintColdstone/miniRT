#include "miniRT.h"

static bool	check_cap(const t_cylinder *cl, const t_ray *r, double cap_height,
					  double *t_cap)
{
	if (fabs(r->direction.y) < 1e-8)
		return (false);
	
	*t_cap = (cap_height - r->origin.y) / r->direction.y;
	
	if (*t_cap <= 0)
		return (false);
	
	t_vec3 hit = ray_at(r, *t_cap);
	double dx = hit.x;
	double dz = hit.z;
	
	return (dx * dx + dz * dz <= cl->radius * cl->radius);
}

static bool	check_cylinder_side(const t_cylinder *cl, const t_ray *r, 
								t_interval ray_t, double *t_side)
{
	double a = r->direction.x * r->direction.x + r->direction.z * r->direction.z;
	double b = 2 * (r->direction.x * r->origin.x + 
				   r->direction.z * r->origin.z);
	double c = r->origin.x * r->origin.x + 
			   r->origin.z * r->origin.z - 
			   cl->radius * cl->radius;
	
	if (fabs(a) < 1e-8)
		return (false);
	
	double disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	
	double sqrt_disc = sqrt(disc);
	double root = (-b - sqrt_disc) / (2 * a);
	
	// Check if first root is within bounds
	if (root <= ray_t.min || root >= ray_t.max)
		root = (-b + sqrt_disc) / (2 * a);
	
	// Check if second root is within bounds
	if (root <= ray_t.min || root >= ray_t.max)
		return (false);
	
	// Check if intersection point is within cylinder height
	double y = r->origin.y + root * r->direction.y;
	if (y < 0 || y > cl->height)
		return (false);
	
	*t_side = root;
	return (true);
}

static t_vec3 get_cylinder_normal_local(const t_vec3 *hit_local, double hit_t,
										double t_side, double t_bottom, double t_top)
{
	// Determine which part of the cylinder was hit
	if (fabs(hit_t - t_side) < 1e-8)
	{
		// Side hit: normal points radially outward
		t_vec3 normal = (t_vec3){hit_local->x, 0, hit_local->z};
		return (unit_vector(normal));
	}
	else if (fabs(hit_t - t_bottom) < 1e-8)
	{
		// Bottom cap hit: normal points down
		return ((t_vec3){0, -1, 0});
	}
	else
	{
		// Top cap hit: normal points up
		return ((t_vec3){0, 1, 0});
	}
}

bool	cylinder_hit(const t_cylinder *cl, const t_ray *r, t_interval ray_t, 
					 t_hit_record *rec)
{
	t_vec3	u, v, w;
	t_ray	rotated_r;
	double	t_side = INFINITY;
	double	t_bottom = INFINITY;
	double	t_top = INFINITY;
	double	t_min = INFINITY;
	
	create_orthonormal_basis(&cl->axis, &u, &v, &w);
	
	// Transform ray to cylinder's local coordinate system
	// Note: w is the cylinder's axis direction
	rotated_r.origin = world_to_object_space(&r->origin, &cl->center, &u, &v, &w);
	rotated_r.direction = world_to_object_direction(&r->direction, &u, &v, &w);

	// Check for intersections in local space
	if (check_cylinder_side(cl, &rotated_r, ray_t, &t_side))
		t_min = t_side;
	
	// Check bottom cap (y = 0 in local space)
	if (check_cap(cl, &rotated_r, 0.0, &t_bottom) && 
		t_bottom > ray_t.min && t_bottom < t_min)
		t_min = t_bottom;
	
	// Check top cap (y = height in local space)
	if (check_cap(cl, &rotated_r, cl->height, &t_top) && 
		t_top > ray_t.min && t_top < t_min)
		t_min = t_top;
	
	// No intersection found
	if (t_min == INFINITY)
		return (false);
	
	// Calculate hit information
	t_vec3 hit_local = ray_at(&rotated_r, t_min);
	rec->t = t_min;
	
	// Transform hit position back to world space
	rec->position = object_to_world_space(&hit_local, &cl->center, &u, &v, &w);
	rec->mat = cl->mat;
	
	// Calculate normal in local space, then transform to world space
	t_vec3 normal_local = get_cylinder_normal_local(&hit_local, t_min, 
										t_side, t_bottom, t_top);
	t_vec3 normal_world = object_to_world_direction(&normal_local, &u, &v, &w);
	
	// Set face normal (determines if ray hits from inside or outside)
	set_face_normal(r, &normal_world, rec);
	
	return (true);
}
