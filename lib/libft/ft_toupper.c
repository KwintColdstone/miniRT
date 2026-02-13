/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_toupper.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 15:01:38 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/14 15:12:09 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*
int	main()
{
	char c = 'a';
	char d = 'B';
	printf("%c\n", ft_toupper(c));	
	printf("%c\n", toupper(c));	
	printf("%c\n", ft_toupper(d));	
	printf("%c\n", toupper(d));	
}
*/
