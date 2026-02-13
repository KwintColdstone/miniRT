#include "miniRT.h"

//random scatter
//direction = random_on_hemisphere(&rec.normal);
bool lambertian_scatter(const t_ray *r_in, const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
	(void) r_in; 	//unused!!
	t_vec3 scatter_direction = add_vec3(rec->normal, random_unit_vector());
	// Catch degenerate scatter direction
	if (near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = (t_ray){rec->position, scatter_direction};
	*attenuation = rec->mat.albedo;
	return true;
}


bool metal_scatter(const t_ray *r_in, const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3 reflected = reflect(&r_in->direction, &rec->normal);
	reflected = add_vec3(unit_vector(reflected), multiply_by_scalar(random_unit_vector(), rec->mat.fuzz));
	*scattered = (t_ray){rec->position, reflected};
	*attenuation = rec->mat.albedo;
	return (dot_vec3(scattered->direction, rec->normal) > 0);
}
