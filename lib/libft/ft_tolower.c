/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_tolower.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 15:12:27 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/14 15:17:43 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

/*
int	main()
{
	char c = 'a';
	char d = 'B';
	printf("%c\n", ft_tolower(c));	
	printf("%c\n", tolower(c));	
	printf("%c\n", ft_tolower(d));	
	printf("%c\n", tolower(d));	
}
*/
