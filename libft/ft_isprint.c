/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kjongeri <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 14:41:49 by kjongeri       #+#    #+#                */
/*   Updated: 2024/10/24 16:02:35 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*
int	main()
{
	char c;
	c = 44;
	printf("%d\n",ft_isprint(c));
	printf("%d\n",isprint(c));
	char d;
	d = 127;
	printf("%d\n",ft_isprint(d));
	printf("%d\n",isprint(d));
	return 0;
}
*/
