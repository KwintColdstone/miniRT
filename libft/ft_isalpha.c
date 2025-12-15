/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isalpha.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 12:49:36 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/14 14:28:19 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	else
		return (0);
}

/*
int	main()
{
	char c;
	c = 'q';
	printf("%d\n",ft_isalpha(c));
	printf("%d\n",isalpha(c));
	char d;
	c = '#';
	printf("%d\n",ft_isalpha(c));
	printf("%d\n",isalpha(c));
	return 0;
}*/
