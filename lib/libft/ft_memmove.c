/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/15 13:29:24 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 20:33:14 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	size_t			i;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (tmp_dst > tmp_src)
		while (n-- > 0)
			tmp_dst[n] = tmp_src[n];
	else
	{
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}

/*
int	main()
{
	char dst[20];
	char src[20] = "testing";

	ft_memmove(dst,src,4);
	puts(dst);

	return (0);
}
*/
