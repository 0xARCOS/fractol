/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soul_generator.c                                   :+:      :+:    :+:   */
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
#include <string.h>

static unsigned long	djb2_hash(const unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

unsigned long	generate_soul_hash(const char *name, int day, int month, int year)
{
	unsigned long	hash;
	char			buffer[256];
	int				i;

	i = 0;
	while (name[i] && i < 200)
	{
		if (name[i] >= 'A' && name[i] <= 'Z')
			buffer[i] = name[i] + 32;
		else
			buffer[i] = name[i];
		i++;
	}
	buffer[i] = '\0';
	hash = djb2_hash((unsigned char *)buffer);
	hash ^= (unsigned long)(day * 31 + month * 97 + year * 13);
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);
	return (hash);
}

void	soul_to_fractal_params(unsigned long soul_code, t_data *data)
{
	double	normalized;

	normalized = (soul_code % 10000) / 10000.0;
	data->fractal_type = JULIA;
	data->c_real = -0.8 + (normalized * 1.0);
	data->c_imag = -0.4 + ((soul_code % 5000) / 5000.0 * 0.8);
	data->zoom = 1.0 + (soul_code % 100) / 50.0;
	data->x_offset = ((soul_code % 1000) / 1000.0 - 0.5) * 0.5;
	data->y_offset = ((soul_code % 2000) / 2000.0 - 0.5) * 0.5;
	data->color_shift = (int)(soul_code % 360);
	data->max_iter = 100 + (int)(soul_code % 50);
}

void	generate_share_code(unsigned long soul_code, char *output)
{
	const char	*charset = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
	int			i;

	for (i = 0; i < 8; i++)
	{
		output[i] = charset[soul_code % 32];
		soul_code /= 32;
	}
	output[8] = '\0';
}

unsigned long	decode_share_code(const char *code)
{
	const char		*charset = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
	unsigned long	result;
	int				i;
	int				j;
	int				value;

	result = 0;
	i = 7;
	while (i >= 0)
	{
		j = 0;
		value = -1;
		while (charset[j])
		{
			if (charset[j] == code[i])
			{
				value = j;
				break ;
			}
			j++;
		}
		if (value == -1)
			return (0);
		result = result * 32 + value;
		i--;
	}
	return (result);
}

void	print_soul_info(t_soul_params *soul)
{
	char	share_code[9];

	generate_share_code(soul->soul_code, share_code);
	printf("\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║          ✨ TU FRACTAL SOUL HA SIDO REVELADO ✨        ║\n");
	printf("╚════════════════════════════════════════════════════════╝\n\n");
	printf("  👤 Nombre: %s\n", soul->name);
	printf("  🎂 Nacimiento: %02d/%02d/%d\n", soul->day, soul->month, soul->year);
	if (soul->zodiac_sign)
		printf("  ♈ Signo: %s\n", soul->zodiac_sign);
	printf("  🔮 Soul Code: %lu\n", soul->soul_code);
	printf("  🔑 Share Code: %s\n\n", share_code);
	printf("╭────────────────────────────────────────────────────────╮\n");
	printf("│  💫 Parámetros Fractales de tu Alma:                  │\n");
	printf("│     • Parte Real: %.6f                              │\n", soul->c_real);
	printf("│     • Parte Imaginaria: %.6f                        │\n", soul->c_imag);
	printf("│     • Vibración de Color: %d°                        │\n", soul->color_seed);
	printf("╰────────────────────────────────────────────────────────╯\n\n");
	if (soul->soul_message)
	{
		printf("  📜 Mensaje Fractal:\n");
		printf("     \"%s\"\n\n", soul->soul_message);
	}
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("  📱 COMPARTE TU FRACTAL SOUL:\n");
	printf("     Instagram/TikTok: #FractalSoul #%s\n", share_code);
	printf("     Para ver este fractal: ./fractol soul %s\n", share_code);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}
