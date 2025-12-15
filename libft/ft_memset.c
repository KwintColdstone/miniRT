/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/15 11:10:30 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 17:33:34 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)str;
	while (i < n)
	{
		tmp[i] = (unsigned char) c;
		i++;
	}
	return (str);
}

/*
int	main()
{
	char str[50];

   	strcpy(str, "Hallo test");
   	puts(str);

   	ft_memset(str, '#', 5);
   	puts(str);

   	return(0);
}
*/
