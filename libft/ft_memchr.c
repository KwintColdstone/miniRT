/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:22:52 by kjongeri          #+#    #+#             */
/*   Updated: 2024/10/24 17:34:12 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*chstr;
	unsigned char	cc;
	size_t			i;

	chstr = (unsigned char *) str;
	cc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (chstr[i] == cc)
			return ((void *) &chstr[i]);
		i++;
	}
	return (NULL);
}

/*
int main(void)
{
	const char str[] = "test";
	const char c = 's';

	puts(ft_memchr(str,c,4));
	return (0);
}
*/
