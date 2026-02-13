/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isalnum.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 14:04:42 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/21 15:49:07 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}

/*int	main()
{
	char c;
	c = '8';
	printf("%d\n",ft_isalnum(c));
	printf("%d\n",isalnum(c));
	char d;
	c = '#';
	printf("%d\n",ft_isalnum(c));
	printf("%d\n",isalnum(c));
	return 0;
}
*/
