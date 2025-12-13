/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:19:00 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/27 01:34:31 by aarcos           ###   ########.fr       */
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

	zr = x;
	zi = y;
	i = 0;
	max_iter = 100;
	while (zr * zr + zi * zi < 4 && i < max_iter)
	{
		tmp = zr * zr - zi * zi + data->c_real;
		zi = 2 * zr * zi + data->c_imag;
		zr = tmp;
		i++;
	}
	return (i);
}

void	draw_julia_pixel(t_data *data, int x, int y)
{
	double	real;
	double	imag;
	int		iter;
	int		color;

	real = map_x(x, data);
	imag = map_y(y, data);
	iter = julia(real, imag, data);
	color = get_fractal_color(iter, data->max_iter, data->color_shift);
	put_pixel_to_image(data, x, y, color);
}

void	draw_julia(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw_julia_pixel(data, x, y);
			x++;
		}
		y++;
	}
}
