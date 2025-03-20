/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lorenz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:19:09 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 15:15:02 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include <math.h>

void	draw_lorenz(t_data *data)
{
	double	sigma = data->sigma, rho = data->rho, beta;
	double	dx;
	double	dy;
	double	dz;
	int		red;
	int		green;
	int		blue;

	double x = 0.1, y = 0.0, z = 0.0; // Condiciones iniciales
	double dt = data->lorenz_speed;   // Paso de tiempo ajustable
	sigma = data->sigma, rho = data->rho, beta = data->beta;
	int i, px, py, color;
	for (i = 0; i < 50000; i++) // Iteraciones para dibujar la trayectoria
	{
		dx = sigma * (y - x) * dt;
		dy = (x * (rho - z) - y) * dt;
		dz = (x * y - beta * z) * dt;
		x += dx;
		y += dy;
		z += dz;
		// Escalar valores a la pantalla
		px = (int)((x * 10) + WIDTH / 2);
		py = (int)((y * 10) + HEIGHT / 2);
		// Asegurar que los puntos están dentro de la ventana
		if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
		{
			// Color dinámico basado en `z`
			red = (int)(128 + 127 * sin(0.1 * z));
			green = (int)(128 + 127 * sin(0.2 * z));
			blue = (int)(128 + 127 * sin(0.3 * z));
			color = (red << 16) | (green << 8) | blue;
			put_pixel_to_image(data, px, py, color);
		}
	}
}
