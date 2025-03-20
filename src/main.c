/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:11 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/19 15:02:57 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"
#include <string.h> // BORRAR esta línea

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(&data) == MLX_ERROR)
		return (MLX_ERROR);
	// Buscar el fractal en los argumentos
	data.fractal_type = MANDELBROT; // Valor por defecto
	for (int i = 1; i < argc; i++)
	{
		if (strcasecmp(argv[i], "julia") == 0)
			data.fractal_type = JULIA;
		else if (strcasecmp(argv[i], "lorenz") == 0)
			data.fractal_type = LORENZ;
	}
	render_fractal(&data);
	mlx_key_hook(data.win_ptr, handle_key, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
