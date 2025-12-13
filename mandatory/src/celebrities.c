/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celebrities.c                                      :+:      :+:    :+:   */
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

static t_celebrity	*get_celebrity_database(void)
{
	static t_celebrity	celebs[] = {
		{"Messi", 0, "MESSI10", JULIA},
		{"Cristiano", 0, "CR7SIUUU", JULIA},
		{"Bad Bunny", 0, "BENITO42", JULIA},
		{"Shakira", 0, "SHAKIRAA", JULIA},
		{"Rosalía", 0, "MOTOMAMI", JULIA},
		{"Dua Lipa", 0, "DUALIPA9", JULIA},
		{"The Weeknd", 0, "BLINDING", JULIA},
		{"Billie Eilish", 0, "BILLIE17", JULIA},
		{"Elon Musk", 0, "ELONMARS", MANDELBROT},
		{"Einstein", 0, "E2MC2MTH", JULIA},
		{"Frida Kahlo", 0, "FRIDART", JULIA},
		{"Van Gogh", 0, "STARRYNT", JULIA},
		{"Picasso", 0, "CUBISM42", JULIA},
		{"Da Vinci", 0, "MONALISA", JULIA},
		{"Tesla", 0, "NIKOLATL", MANDELBROT},
		{"Dalí", 0, "SURREAL9", JULIA},
		{"", 0, "", 0}
	};
	int	i;

	i = 0;
	while (celebs[i].name[0])
	{
		if (celebs[i].soul_code == 0)
			celebs[i].soul_code = generate_soul_hash(celebs[i].name, 1, 1, 2000);
		i++;
	}
	return (celebs);
}

void	load_celebrity_fractal(t_data *data, const char *name)
{
	t_celebrity	*celebs;
	int			i;
	char		lowercase_input[256];
	char		lowercase_celeb[256];
	int			j;

	celebs = get_celebrity_database();
	i = 0;
	j = 0;
	while (name[j] && j < 255)
	{
		if (name[j] >= 'A' && name[j] <= 'Z')
			lowercase_input[j] = name[j] + 32;
		else
			lowercase_input[j] = name[j];
		j++;
	}
	lowercase_input[j] = '\0';
	while (celebs[i].name[0])
	{
		j = 0;
		while (celebs[i].name[j] && j < 255)
		{
			if (celebs[i].name[j] >= 'A' && celebs[i].name[j] <= 'Z')
				lowercase_celeb[j] = celebs[i].name[j] + 32;
			else
				lowercase_celeb[j] = celebs[i].name[j];
			j++;
		}
		lowercase_celeb[j] = '\0';
		if (strstr(lowercase_celeb, lowercase_input) != NULL)
		{
			soul_to_fractal_params(celebs[i].soul_code, data);
			data->fractal_type = celebs[i].fractal_type;
			printf("\n");
			printf("⭐════════════════════════════════════════════════════════⭐\n");
			printf("        🌟 FRACTAL SOUL DE CELEBRIDAD CARGADO 🌟\n");
			printf("⭐════════════════════════════════════════════════════════⭐\n\n");
			printf("  👑 Celebridad: %s\n", celebs[i].name);
			printf("  🔑 Share Code: %s\n", celebs[i].share_code);
			printf("  🔮 Soul Code: %lu\n\n", celebs[i].soul_code);
			printf("  📱 Comparte en redes:\n");
			printf("     #FractalSoul #%s #%s\n\n", celebs[i].name, celebs[i].share_code);
			printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
			return ;
		}
		i++;
	}
	printf("❌ Celebridad no encontrada. Usa: ./fractol celebs\n");
}

void	list_celebrities(void)
{
	t_celebrity	*celebs;
	int			i;

	celebs = get_celebrity_database();
	printf("\n");
	printf("👑═══════════════════════════════════════════════════════👑\n");
	printf("          ✨ FRACTALES DE CELEBRIDADES ✨\n");
	printf("👑═══════════════════════════════════════════════════════👑\n\n");
	printf("  Descubre el Fractal Soul de las personas más famosas:\n\n");
	i = 0;
	while (celebs[i].name[0])
	{
		printf("  🌟 %-20s Code: %s\n", celebs[i].name, celebs[i].share_code);
		i++;
	}
	printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("  📖 Uso:\n");
	printf("     ./fractol celeb [nombre]\n");
	printf("     Ejemplo: ./fractol celeb messi\n\n");
	printf("  💡 También puedes usar share codes:\n");
	printf("     ./fractol soul MESSI10\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}
