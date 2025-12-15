/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:34 by kjongeri          #+#    #+#             */
/*   Updated: 2024/10/24 17:24:08 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	count_nbr(int num);

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nbr;

	nbr = n;
	i = count_nbr(nbr);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		str[i--] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	return (str);
}

static int	count_nbr(int num)
{
	int		counter;
	long	nbr;

	counter = 0;
	nbr = num;
	if (nbr <= 0)
		counter++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		counter++;
	}
	return (counter);
}

/*
int main(void)
{
	puts(ft_itoa(-148));
	return(0);
}
*/
