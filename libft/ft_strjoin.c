/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <kjongeri@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 16:02:40 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 16:48:35 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*joined;
	size_t	strlen;

	i = 0;
	j = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *) malloc((strlen + 1) * sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	if (joined == NULL)
		return (NULL);
	while (s1[i])
	{
		joined[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		joined[j++] = s2[i++];
	}
	joined[j] = '\0';
	return (joined);
}

/*
int main(void)
{
	char s1[] = "hello";
	char s2[] = "again";
	puts(ft_strjoin(s1,s2));
	return(0);
}
*/
