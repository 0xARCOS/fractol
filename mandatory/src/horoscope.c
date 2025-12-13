/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horoscope.c                                        :+:      :+:    :+:   */
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

const char	*get_zodiac_sign(int day, int month)
{
	if ((month == 3 && day >= 21) || (month == 4 && day <= 19))
		return ("Aries ♈");
	if ((month == 4 && day >= 20) || (month == 5 && day <= 20))
		return ("Tauro ♉");
	if ((month == 5 && day >= 21) || (month == 6 && day <= 20))
		return ("Géminis ♊");
	if ((month == 6 && day >= 21) || (month == 7 && day <= 22))
		return ("Cáncer ♋");
	if ((month == 7 && day >= 23) || (month == 8 && day <= 22))
		return ("Leo ♌");
	if ((month == 8 && day >= 23) || (month == 9 && day <= 22))
		return ("Virgo ♍");
	if ((month == 9 && day >= 23) || (month == 10 && day <= 22))
		return ("Libra ♎");
	if ((month == 10 && day >= 23) || (month == 11 && day <= 21))
		return ("Escorpio ♏");
	if ((month == 11 && day >= 22) || (month == 12 && day <= 21))
		return ("Sagitario ♐");
	if ((month == 12 && day >= 22) || (month == 1 && day <= 19))
		return ("Capricornio ♑");
	if ((month == 1 && day >= 20) || (month == 2 && day <= 18))
		return ("Acuario ♒");
	return ("Piscis ♓");
}

const char	*get_fractal_message(unsigned long soul_code)
{
	const char	*messages[] = {
		"Tu alma vibra con patrones infinitos de creatividad y pasión",
		"Las matemáticas del universo te revelan caminos de autorrealización",
		"Tu energía fractal irradia belleza en cada iteración de tu ser",
		"El caos ordenado de tu alma crea armonía en el cosmos",
		"Tu espíritu se expande infinitamente como los brazos de Mandelbrot",
		"La complejidad de tu esencia es un misterio hermoso y único",
		"Tus decisiones crean patrones que resonarán en el universo",
		"La belleza de tu alma se multiplica con cada nueva experiencia",
		"Tu energía cósmica fluye en espirales de posibilidad infinita",
		"El universo te reconoce como una obra maestra fractal única",
		"Tu vibración atrae oportunidades que se multiplican exponencialmente",
		"La geometría sagrada de tu ser irradia luz y transformación",
	};
	return (messages[soul_code % 12]);
}

void	generate_daily_horoscope(t_data *data)
{
	time_t		rawtime;
	struct tm	*timeinfo;
	unsigned long	today_code;
	char		share_code[9];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	today_code = generate_soul_hash("COSMIC_ENERGY",
			timeinfo->tm_mday,
			timeinfo->tm_mon + 1,
			timeinfo->tm_year + 1900);
	soul_to_fractal_params(today_code, data);
	generate_share_code(today_code, share_code);
	printf("\n");
	printf("🌟════════════════════════════════════════════════════════🌟\n");
	printf("           ✨ HORÓSCOPO FRACTAL DEL DÍA ✨\n");
	printf("              %02d de ", timeinfo->tm_mday);
	const char *months[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo",
		"Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre",
		"Diciembre"};
	printf("%s de %d\n", months[timeinfo->tm_mon], timeinfo->tm_year + 1900);
	printf("🌟════════════════════════════════════════════════════════🌟\n\n");
	printf("  🔮 Energía Cósmica del Día:\n");
	printf("     %s\n\n", get_fractal_message(today_code));
	printf("  🎨 Tu color de poder hoy: Vibración %d°\n", data->color_shift);
	printf("  🔑 Share Code del Día: %s\n\n", share_code);
	printf("  💫 Comparte tu energía:\n");
	printf("     #FractalHoroscope #%s #DailyFractal\n\n", share_code);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("  🧘 Meditación Fractal: Observa cómo los patrones se repiten\n");
	printf("     en tu vida. Cada decisión crea infinitas posibilidades.\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}
