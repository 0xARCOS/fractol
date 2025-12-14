/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 06:48:26 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/24 06:48:35 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	set_julia_params(t_data *data, int argc, char **argv)
{
	if (argc == 4)
	{
		data->c_real = ft_atof(argv[2]);
		data->c_imag = ft_atof(argv[3]);
		if (data->c_real < -2.0 || data->c_real > 2.0)
			data->c_real = -0.7;
		if (data->c_imag < -2.0 || data->c_imag > 2.0)
			data->c_imag = 0.27015;
	}
	else
	{
		data->c_real = -0.7;
		data->c_imag = 0.27015;
	}
}

void	parse_arguments(t_data *data, int argc, char **argv)
{
	if (argc >= 2)
	{
		if (ft_strcmp_insensitive(argv[1], "julia") == 0)
		{
			data->fractal_type = JULIA;
			set_julia_params(data, argc, argv);
		}
		else if (ft_strcmp_insensitive(argv[1], "mandelbrot") == 0)
			data->fractal_type = MANDELBROT;
	}
}
