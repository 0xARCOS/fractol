/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:23 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/20 01:19:20 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"

void	move_fractal(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->x_offset -= 0.1 / data->zoom;
	else if (keycode == RIGHT)
		data->x_offset += 0.1 / data->zoom;
	else if (keycode == UP)
		data->y_offset -= 0.1 / data->zoom;
	else if (keycode == DOWN)
		data->y_offset += 0.1 / data->zoom;
	render_fractal(data);
}

void	zoom_fractal(int keycode, t_data *data)
{
	if (keycode == ZOOM_IN)
		data->zoom *= 1.1;
	if (keycode == ZOOM_OUT)
		data->zoom /= 1.1;
}

void	reset_or_change_color(int keycode, t_data *data)
{
	if (keycode == RESET)
	{
		data->zoom = 1.0;
		data->x_offset = 0.0;
		data->y_offset = 0.0;
		data->color_shift = 255;
	}
	else if (keycode == COLOR)
	{
		data->color_shift += 100;
	}
}

// int	handle_key(int keycode, t_data *data) // CLOSE
// {
// 	if (keycode == ESQ_KEY)
// 	{
// 		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
// 		mlx_destroy_window(data->mlx_ptr, data->img_ptr);
// 		mlx_destroy_display(data->mlx_ptr);
// 		free(data->mlx_ptr);
// 		exit(0);
// 	}
// 	move_fractal(keycode, data);
// 	zoom_fractal(keycode, data);
// 	reset_or_change_color(keycode, data);
// 	render_fractal(data);

// 	return (0);
// }

int	handle_key(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	else if (keycode == UP) // Aumentar rho
		data->rho += 1.0;
	else if (keycode == DOWN) // Disminuir rho
		data->rho -= 1.0;
	else if (keycode == LEFT) // Disminuir sigma
		data->sigma -= 0.5;
	else if (keycode == RIGHT) // Aumentar sigma
		data->sigma += 0.5;
	else if (keycode == PLUS) // Aumentar beta
		data->beta += 0.1;
	else if (keycode == MINUS) // Disminuir beta
		data->beta -= 0.1;
	else if (keycode == W) // Aumentar velocidad
		data->lorenz_speed *= 1.1;
	else if (keycode == S) // Disminuir velocidad
		data->lorenz_speed /= 1.1;
	render_fractal(data);
	return (0);
}
