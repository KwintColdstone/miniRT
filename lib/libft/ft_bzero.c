/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_bzero.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/15 11:56:47 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/15 12:10:33 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)str;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}

/*
int	main()
{
	char str[50];

   	strcpy(str, "Hallo test");
   	puts(str);

   	ft_bzero(str, 2);
   	puts(str);

   	return(0);
}
*/
