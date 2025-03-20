/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:19:00 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 14:50:34 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"

int	julia(double x, double y, t_data *data)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;
	int		max_iter;
	double	c_imag;
	double	c_real;

	(void)data;
	zr = x;
	zi = y;
	i = 0;
	max_iter = 100;
	// La constante C define la forma del fractal de Julia
	c_real = -0.7;
	// Puedes cambiar estos valores para ver diferentes formas
	c_imag = 0.27015;
	while (zr * zr + zi * zi < 4 && i < max_iter)
	{
		tmp = zr * zr - zi * zi + c_real;
		zi = 2 * zr * zi + c_imag;
		zr = tmp;
		i++;
	}
	return (i);
}

void	draw_julia(t_data *data)
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
			iter = julia(real, imag, data);
			// Escala de grises
			color = (iter * 255 / 100);
			color = (color << 16) | (color << 8) | color;
			put_pixel_to_image(data, x, y, color);
			x++;
		}
		y++;
	}
}
