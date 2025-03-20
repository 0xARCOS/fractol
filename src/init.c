/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:18 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 15:17:21 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	init(t_data *data)
{
	data->lorenz_speed = 0.01;
	data->sigma = 10.0;
	data->rho = 28.0;
	data->beta = 8.0 / 3.0;
	data->zoom = 1;
	data->x_offset = 0;
	data->y_offset = 0;
	data->color_shift = 255;         // Mejora visual
	data->fractal_type = MANDELBROT; // Iniciar con Mandelbrot
	data->mlx_ptr = mlx_init();      // Conexión con MiniLibX
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "mi ventana");
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->img_ptr == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (data->img_data == NULL)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	return (0);
}
