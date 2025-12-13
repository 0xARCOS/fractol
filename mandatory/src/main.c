/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:11 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/24 07:02:10 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "mlx.h"
#include <unistd.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_strcmp_insensitive(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		divisor;
	int		sign;

	result = 0;
	fraction = 0;
	divisor = 1;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction * 10 + (*str++ - '0');
		divisor *= 10;
	}
	return (sign * (result + fraction / divisor));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(&data) == MLX_ERROR)
		return (MLX_ERROR);
	data.fractal_type = -1;
	parse_arguments(&data, argc, argv);
	if (data.fractal_type == -1)
	{
		write(1,
			"Uso: ./fractol [mandelbrot | julia [c_real c_imag] | lorenz]\n",
			61);
		return (1);
	}
	render_fractal(&data);
	mlx_key_hook(data.win_ptr, handle_key, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
