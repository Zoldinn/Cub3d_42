/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:41:20 by lefoffan          #+#    #+#             */
/*   Updated: 2025/05/30 15:05:39 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (!s || !*s)
		return (0);
	while (s[size])
		size++;
	return (size);
}

////////////////////// TEST
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%zu\n", ft_strlen(av[1]));
		return (0);
	}
	printf("ERROR\n");
	return (1);
}*/
