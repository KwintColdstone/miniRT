#include "miniRT.h"

double degrees_to_radians(double degrees)
{
    return (degrees * M_PI / 180.0);
}

double random_double(void)
{
    // Returns a random real in [0,1).
    return (rand() / (RAND_MAX + 1.0));
}

double random_double_mm(double min, double max)
{
    // Returns a random real in [min,max).
    return (min + (max-min)*random_double());
}

double	clamp_interval(double x, t_interval i)
{
	if (x < i.min)
	{
		return (i.min);
	}
	if (x > i.max)
	{
		return (i.max);
	}
	return (x);
}

bool	interval_contains(t_interval i, double x)
{
	return (i.min <= x && x <= i.max);
}
