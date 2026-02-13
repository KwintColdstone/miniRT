/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isdigit.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 12:53:27 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/14 12:56:50 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

/*int	main()
{
	char c;
	c = '2';
	printf("%d\n",ft_isdigit(c));
	printf("%d\n",isdigit(c));
	char d;
	c = '#';
	printf("%d\n",ft_isdigit(c));
	printf("%d\n",isdigit(c));
	return 0;
}*/
