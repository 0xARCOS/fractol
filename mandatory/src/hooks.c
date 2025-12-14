/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:23 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/24 07:02:53 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"

int	handle_close(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == ESC)
		handle_close(data);
	handle_movement(keycode, data);
	handle_zoom(keycode, data);
	apply_color_change(keycode, data);
	handle_reset(keycode, data);
	handle_lorenz_keys(keycode, data);
	render_fractal(data);
	return (0);
}

void	handle_reset(int keycode, t_data *data)
{
	if (keycode == RESET)
	{
		data->zoom = 1.0;
		data->x_offset = 0.0;
		data->y_offset = 0.0;
		data->max_iter = 100;
		data->color_shift = 0;
		if (data->fractal_type == JULIA)
		{
			data->c_real = -0.7;
			data->c_imag = 0.27015;
		}
		else if (data->fractal_type == LORENZ)
		{
			data->sigma = 10.0;
			data->rho = 28.0;
			data->beta = 8.0 / 3.0;
			data->lorenz_speed = 0.01;
		}
	}
}

void	handle_lorenz_keys(int keycode, t_data *data)
{
	if (data->fractal_type != LORENZ)
		return ;
	if (keycode == UP)
		data->rho += 1.0;
	else if (keycode == DOWN)
		data->rho -= 1.0;
	else if (keycode == LEFT)
		data->sigma -= 0.5;
	else if (keycode == RIGHT)
		data->sigma += 0.5;
	else if (keycode == PLUS)
		data->beta += 0.1;
	else if (keycode == MINUS)
		data->beta -= 0.1;
	else if (keycode == W)
		data->lorenz_speed *= 1.1;
	else if (keycode == S)
		data->lorenz_speed /= 1.1;
}

void	handle_movement(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->x_offset -= 0.1 / data->zoom;
	else if (keycode == RIGHT)
		data->x_offset += 0.1 / data->zoom;
	else if (keycode == UP)
		data->y_offset -= 0.1 / data->zoom;
	else if (keycode == DOWN)
		data->y_offset += 0.1 / data->zoom;
}

void	handle_zoom(int keycode, t_data *data)
{
	if (keycode == ZOOM_IN)
	{
		data->zoom *= 1.1;
		data->max_iter += 10;
	}
	else if (keycode == ZOOM_OUT)
	{
		data->zoom /= 1.1;
		if (data->max_iter > 30)
			data->max_iter -= 10;
	}
	render_fractal(data);
}

void	apply_color_change(int keycode, t_data *data)
{
	if (keycode == COLOR)
		data->color_shift += 50;
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	double	mouse_x;
	double	mouse_y;

	(void)x;
	(void)y;
	mouse_x = map_x(x, data);
	mouse_y = map_y(y, data);
	if (button == 4 || button == 5)
	{
		if (button == 4)
		{
			data->zoom *= 1.2;
			data->x_offset = mouse_x + (data->x_offset - mouse_x) / 1.2;
			data->y_offset = mouse_y + (data->y_offset - mouse_y) / 1.2;
			if (data->max_iter < 500)
				data->max_iter += 10;
		}
		else
		{
			data->zoom /= 1.2;
			data->x_offset = mouse_x + (data->x_offset - mouse_x) * 1.2;
			data->y_offset = mouse_y + (data->y_offset - mouse_y) * 1.2;
			if (data->max_iter > 30)
				data->max_iter -= 10;
		}
		render_fractal(data);
	}
	return (0);
}
