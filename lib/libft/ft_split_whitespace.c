/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:23:52 by kjongeri          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:59 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s)
{
	size_t	count;
	int		i;

	if (s == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == 1)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && ft_isspace(s[i]) == 0)
			i++;
	}
	return (count);
}

static void	free_split(char **split, int i)
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

char	**ft_split_whitespace(char const *s)
{
	char	**split;
	size_t	word_len;
	int		i;

	split = malloc((ft_countword(s) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_isspace(*s) == 1)
			s++;
		if (*s)
		{
			word_len = 0;
			while (s[word_len] && ft_isspace(s[word_len]) == 0)
				word_len++;
			split[i++] = ft_substr(s, 0, word_len);
			if (split[i - 1] == NULL)
				return (free_split(split, i), NULL);
			s += word_len;
		}
	}
	return (split[i] = NULL, split);
}
