/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 06:42:18 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/28 08:47:04 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

static void	init_defaults(t_data *data)
{
	data->x_offset = 0;
	data->y_offset = 0;
	data->color_shift = 0;
	data->fractal_type = MANDELBROT;
	data->max_iter = 100;
	data->zoom = 1.0;
	data->lorenz_speed = 0.01;
	data->sigma = 10.0;
	data->rho = 28.0;
	data->beta = 8.0 / 3.0;
}

static int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "fract-ol");
	if (!data->win_ptr)
		return (MLX_ERROR);
	return (0);
}

static int	init_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (!data->img_data)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	return (0);
}

int	init(t_data *data)
{
	init_defaults(data);
	if (init_mlx(data) == MLX_ERROR)
		return (MLX_ERROR);
	if (init_image(data) == MLX_ERROR)
		return (MLX_ERROR);
	return (0);
}
