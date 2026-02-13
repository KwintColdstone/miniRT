/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 14:45:40 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 16:11:14 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/*
int main()
{
	const char *s ="test";
	printf("%zu\n", ft_strlen(s + 2));	
	printf("%zu\n", strlen(s));	
	return (0);
}
*/
