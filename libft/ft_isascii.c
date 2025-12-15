/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isascii.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 14:31:00 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/14 14:41:18 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
int	main()
{
	char c;
	c = 44;
	printf("%d\n",ft_isascii(c));
	printf("%d\n",isascii(c));
	int d;
	d = 0x80;
	printf("%d\n",ft_isascii(d));
	printf("%d\n",isascii(d));
	return 0;
}
*/
