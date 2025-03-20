/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:22:52 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 15:02:01 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fract-ol.h"

double map_x(int x, t_data *data)
{
	return ((x - WIDTH / 2) * (4.0 / WIDTH) * data->zoom + data->x_offset);
}

double map_y(int y, t_data *data)
{
	return ((y - HEIGHT / 2) * (4.0 / HEIGHT) * data->zoom + data->y_offset);
}

void put_pixel_to_image(t_data *data, int x, int y, int color)
{
    int pixel;

    pixel = (y * data->size_line) + (x * (data->bpp / 8));
    *(unsigned int *)(data->img_data + pixel) = color;
}


void render_fractal(t_data *data)
{
    if (data->fractal_type == MANDELBROT)
        draw_mandelbrot(data);
    else if (data->fractal_type == JULIA)
        draw_julia(data);
    else if (data->fractal_type == LORENZ)
        draw_lorenz(data);

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

