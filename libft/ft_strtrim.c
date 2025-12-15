/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <kjongeri@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 16:22:18 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 21:02:38 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	check_set(const char *set, char c);

char	*ft_strtrim(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1)
		return (NULL);
	while (check_set(set, s1[i]) == 1)
		i++;
	while (check_set(set, s1[j]) == 1)
		j--;
	return (ft_substr(s1, i, j - (i - 1)));
}

static int	check_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

/*
int main(void)
{
	char s1[] = "afafafafHello please testaffafafa";
	char set[] = "af";
	puts(ft_strtrim(s1,set));
	return(0);
}
*/
