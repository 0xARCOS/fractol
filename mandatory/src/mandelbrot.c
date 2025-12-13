/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:30:03 by aarcos            #+#    #+#             */
/*   Updated: 2025/04/01 02:03:41 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"

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
	max_iter = data->max_iter;
	while (zr * zr + zi * zi < 4 && i < max_iter)
	{
		tmp = zr * zr - zi * zi + x;
		zi = 2 * zr * zi + y;
		zr = tmp;
		i++;
	}
	return (i);
}

void	draw_mandelbrot_pixel(t_data *data, int x, int y)
{
	double	real;
	double	imag;
	int		iter;
	int		color;

	real = map_x(x, data);
	imag = map_y(y, data);
	iter = mandelbrot(real, imag, data);
	color = get_fractal_color(iter, data->max_iter, data->color_shift);
	put_pixel_to_image(data, x, y, color);
}

void	draw_mandelbrot(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw_mandelbrot_pixel(data, x, y);
			x++;
		}
		y++;
	}
}
