/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:30:03 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 14:44:17 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	mandelbrot(double x, double y, t_data *data)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;
	int		max_iter;

	(void)data;
	zr = 0;
	zi = 0;
	i = 0;
	max_iter = 100;
	while (zr * zr + zi * zi < 4 && i < max_iter)
	{
		tmp = zr * zr - zi * zi + x;
		zi = 2 * zr * zi + y;
		zr = tmp;
		i++;
	}
	return (i);
}

void	draw_mandelbrot(t_data *data)
{
	int	color;

	int x, y, iter;
	double real, imag;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			real = map_x(x, data);
			imag = map_y(y, data);
			iter = mandelbrot(real, imag, data);
			// Generar escala de grises
			color = (iter * 255 / 100);
			color = (color << 16) | (color << 8) | color; // R = G = B
			put_pixel_to_image(data, x, y, color);
			x++;
		}
		y++;
	}
}
