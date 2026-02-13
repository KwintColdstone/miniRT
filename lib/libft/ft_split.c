/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                          :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:33:41 by kjongeri          #+#    #+#             */
/*   Updated: 2024/10/29 18:28:23 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	int		i;

	if (s == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

void	free_split(char **split, int i)
{
	int	k;

	k = 0;
	while (k < i - 1)
	{
		free(split[k]);
		k++;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_len;
	int		i;

	split = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (split == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			split[i++] = ft_substr(s, 0, word_len);
			if (split[i - 1] == NULL)
				return (free_split(split, i), NULL);
			s += word_len;
		}
	}
	return (split[i] = NULL, split);
}

/*
int main(void)
{
	int i = 0;
	char s[] = "please split this string";
	char **split = ft_split(s,' ');

	while(split[i])
	{
		puts(split[i]);
		i++;
	}
	printf("%s",&s[5]);
	return (0);
}
*/
