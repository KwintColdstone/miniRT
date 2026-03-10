/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   bonus.h                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 19:41:34 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:34:56 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "miniRT.h"

// MAX_ARGC is 2 + amount of bonus options
# define MAX_ARGC 4
// --ppm enables writing output of the renderer to a .ppm file
# define OPTION_PPM "--ppm"
// --il enables rendering with indirect lighting
# define OPTION_INDIRECT_LIGHTING "--il"

// bonus_parsing.c
int	parse_bonus_options(int argc, char *argv[], t_world *world);

// Writing image to a .ppm file
// ppm_file.c
void	write_to_file(int ppm_file, t_vec3 *pixel_color);
int		create_ppm_file(t_world *world, t_camera *cam);

// material.c
bool lambertian_scatter(const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
bool metal_scatter(const t_ray *r_in, const t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);


#endif //BONUS_H
