/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <kjongeri@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 15:08:12 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 16:58:57 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	return (str);
}

/*
int main(void)
{
	char str[] = "hello please test me";
	puts(ft_substr(str,5,8));
	return(0);
}
*/
