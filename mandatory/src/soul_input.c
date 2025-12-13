/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soul_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by aarcos            #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"
#include "fractal_soul.h"
#include <stdio.h>

void	print_help_menu(void);

static int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

static int	is_valid_share_code(const char *code)
{
	int	i;

	if (!code)
		return (0);
	i = 0;
	while (code[i])
		i++;
	if (i != 8)
		return (0);
	i = 0;
	while (code[i])
	{
		if (!((code[i] >= 'A' && code[i] <= 'Z') ||
			(code[i] >= '2' && code[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void	parse_soul_command(t_data *data, int argc, char **argv)
{
	t_soul_params	soul;
	unsigned long	decoded;

	if (argc == 3 && is_valid_share_code(argv[2]))
	{
		decoded = decode_share_code(argv[2]);
		soul_to_fractal_params(decoded, data);
		printf("\n🔓 Share Code decodificado: %s\n", argv[2]);
		printf("✨ Fractal Soul cargado!\n\n");
		return ;
	}
	if (argc != 6)
	{
		printf("\n❌ Formato incorrecto.\n\n");
		printf("Usa uno de estos formatos:\n");
		printf("  ./fractol soul \"Tu Nombre\" DD MM YYYY\n");
		printf("  ./fractol soul [SHARECODE]\n\n");
		return ;
	}
	soul.name = argv[2];
	soul.day = ft_atoi(argv[3]);
	soul.month = ft_atoi(argv[4]);
	soul.year = ft_atoi(argv[5]);
	if (soul.day < 1 || soul.day > 31 || soul.month < 1 || soul.month > 12)
	{
		printf("\n❌ Fecha inválida.\n\n");
		return ;
	}
	print_soul_animation();
	soul.soul_code = generate_soul_hash(soul.name, soul.day, soul.month, soul.year);
	soul.zodiac_sign = (char *)get_zodiac_sign(soul.day, soul.month);
	soul.soul_message = (char *)get_fractal_message(soul.soul_code);
	soul_to_fractal_params(soul.soul_code, data);
	soul.c_real = data->c_real;
	soul.c_imag = data->c_imag;
	soul.color_seed = data->color_shift;
	print_soul_info(&soul);
	char share_code[9];
	generate_share_code(soul.soul_code, share_code);
	print_share_instructions(share_code);
}

void	parse_viral_arguments(t_data *data, int argc, char **argv)
{
	if (argc < 2)
	{
		print_help_menu();
		data->fractal_type = -1;
		return ;
	}
	if (ft_strcmp_insensitive(argv[1], "soul") == 0)
	{
		parse_soul_command(data, argc, argv);
		data->fractal_type = JULIA;
		return ;
	}
	if (ft_strcmp_insensitive(argv[1], "horoscope") == 0)
	{
		generate_daily_horoscope(data);
		data->fractal_type = JULIA;
		return ;
	}
	if (ft_strcmp_insensitive(argv[1], "celebs") == 0)
	{
		list_celebrities();
		data->fractal_type = -1;
		return ;
	}
	if (ft_strcmp_insensitive(argv[1], "celeb") == 0 && argc >= 3)
	{
		load_celebrity_fractal(data, argv[2]);
		data->fractal_type = JULIA;
		return ;
	}
}
