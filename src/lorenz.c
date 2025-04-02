/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lorenz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:19:09 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/24 07:02:23 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include <math.h>

int	get_lorenz_color(double z)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(128 + 127 * sin(0.1 * z));
	green = (int)(128 + 127 * sin(0.2 * z));
	blue = (int)(128 + 127 * sin(0.3 * z));
	return ((red << 16) | (green << 8) | blue);
}

void	update_lorenz(double *x, double *y, double *z, t_data *data)
{
	double	dx;
	double	dy;
	double	dz;

	dx = data->sigma * (*y - *x) * data->lorenz_speed;
	dy = (*x * (data->rho - *z) - *y) * data->lorenz_speed;
	dz = (*x * *y - data->beta * *z) * data->lorenz_speed;
	*x += dx;
	*y += dy;
	*z += dz;
}

void	draw_lorenz_point(t_data *data, double x, double y, double z)
{
	int	px;
	int	py;
	int	color;

	px = (int)((x * 10) + WIDTH / 2);
	py = (int)((y * 10) + HEIGHT / 2);
	if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
	{
		color = get_lorenz_color(z);
		put_pixel_to_image(data, px, py, color);
	}
}

void	draw_lorenz(t_data *data)
{
	double	x;
	double	y;
	double	z;
	int		i;

	x = 0.1;
	y = 0.0;
	z = 0.0;
	i = 0;
	while (i++ < 50000)
	{
		update_lorenz(&x, &y, &z, data);
		draw_lorenz_point(data, x, y, z);
	}
}
