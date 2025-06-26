/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:13:10 by pmenard           #+#    #+#             */
/*   Updated: 2025/06/26 16:13:12 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

//draw one (and only one) pixel
void	put_pixel(t_my_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

//draw a square of pixels
void	draw_square(t_my_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			put_pixel(img, (SIZE * x) + i, (SIZE * y) + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_my_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			put_pixel(img, (SIZE * y) + i - (SIZE / 2),
				(SIZE * x) + j - (SIZE / 2), color);
			j++;
		}
		i++;
	}
}
