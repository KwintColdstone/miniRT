/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:06:40 by kjongeri          #+#    #+#             */
/*   Updated: 2025/03/14 18:30:42 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_hextol(char *str)
{
	long	res;
	char	c;
	int		i;

	res = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			res = res * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			res = res * 16 + (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			res = res * 16 + (c - 'A' + 10);
		else
			return (-1);
		if (res > LONG_MAX)
			return (LONG_MAX);
		i++;
	}
	return (res);
}
