/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:49:55 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/30 16:22:15 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && n)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

//////////////////// TEST
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	int		res;
	size_t	size;

	if (ac == 4)
	{
		size = (size_t) ft_atoi(av[3]);
		res = ft_strncmp((const char *) av[1], (const char *) av[2], size);
		printf("%d\n", res);
		return (0);
	}
	printf("Error\n");
	return (1);
}*/
