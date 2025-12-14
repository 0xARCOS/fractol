/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:22:52 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/28 11:50:54 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"

void	render_fractal(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (data->fractal_type == MANDELBROT)
		draw_mandelbrot(data);
	else if (data->fractal_type == JULIA)
		draw_julia(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

double	map_x(int x, t_data *data)
{
	return ((x - WIDTH / 2) * (4.0 / WIDTH) / data->zoom + data->x_offset);
}

double	map_y(int y, t_data *data)
{
	return ((y - HEIGHT / 2) * (4.0 / HEIGHT) / data->zoom + data->y_offset);
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (y * data->size_line) + (x * (data->bpp / 8));
	*(unsigned int *)(data->img_data + pixel) = color;
}

int	get_fractal_color(int iter, int max_iter, int color_shift)
{
	int	red;
	int	green;
	int	blue;

	if (iter >= max_iter)
		return (0x000000);
	red = (iter * (9 + color_shift)) % 256;
	green = (iter * (5 + color_shift)) % 256;
	blue = (iter * (11 + color_shift)) % 256;
	return ((red << 16) | (green << 8) | blue);
}
