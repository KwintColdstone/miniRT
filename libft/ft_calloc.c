/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:36:52 by kjongeri          #+#    #+#             */
/*   Updated: 2024/10/29 15:39:32 by kjongeri       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = malloc(count * size);
	if (count != 0 && size > (size_t)-1 / count)
		return (NULL);
	if (tmp == NULL)
		return (NULL);
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

/*
int main(void)
{
	 int n = 5;
   int *array;
   
   // use calloc function to allocate the memory
   array = (int*)ft_calloc(n, sizeof(int));
   
   if (array == NULL) {
      fprintf(stderr, "Memory allocation failed!\n");
      return 1;
   }
   
   //Display the array value
   printf("Array elements after calloc: ");
   for (int i = 0; i < n; i++) {
      printf("%d ", array[i]);
   }
   printf("\n");
   
   //free the allocated memory
   free(array);
   return 0;
}
*/
