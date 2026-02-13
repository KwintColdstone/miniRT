/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:15:17 by kjongeri          #+#    #+#             */
/*   Updated: 2024/10/24 17:22:08 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	cc;
	char	*save;

	i = 0;
	cc = (char) c;
	save = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
			save = ((char *) &str[i]);
		i++;
	}
	if (str[i] == cc)
		save = ((char *) &str[i]);
	return (save);
}

/*
int main()
{
	const char str[] = "test";
	const char t = 't';

	puts(ft_strrchr(str,t));
	return (0);
}
*/
