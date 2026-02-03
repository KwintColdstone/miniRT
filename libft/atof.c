#include "libft.h"
#include <limits.h>

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		i;
	int		sign;
	int		fract_count;

	result = 0.0;
	fraction = 0.0;
	divisor = 10.0;
	bool is_fraction = false;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == '.'))
	{
		if (fract_count >= 3)
			return (sign * (result + fraction));
		if (str[i] == '.')
		{
			is_fraction = true;
			i++;
		}
		int digit = str[i] - '0';
		if (is_fraction == true)
		{
			fraction += digit / divisor;
			divisor *= 10.0;
			fract_count++;
		}
		else
		{
			result = result * 10 + digit;
		}
		if (result >= INT_MAX)
			return (result);
		i++;
	}
	return (sign * (result + fraction));
}
