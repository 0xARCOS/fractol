/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viral_display.c                                    :+:      :+:    :+:   */
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
#include <unistd.h>

void	print_ascii_logo(void)
{
	printf("\033[1;35m");
	printf("\n");
	printf("  ███████╗██████╗  █████╗  ██████╗████████╗ █████╗ ██╗     \n");
	printf("  ██╔════╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██║     \n");
	printf("  █████╗  ██████╔╝███████║██║        ██║   ███████║██║     \n");
	printf("  ██╔══╝  ██╔══██╗██╔══██║██║        ██║   ██╔══██║██║     \n");
	printf("  ██║     ██║  ██║██║  ██║╚██████╗   ██║   ██║  ██║███████╗\n");
	printf("  ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝\n");
	printf("  ███████╗ ██████╗ ██╗   ██╗██╗                             \n");
	printf("  ██╔════╝██╔═══██╗██║   ██║██║                             \n");
	printf("  ███████╗██║   ██║██║   ██║██║                             \n");
	printf("  ╚════██║██║   ██║██║   ██║██║                             \n");
	printf("  ███████║╚██████╔╝╚██████╔╝███████╗                        \n");
	printf("  ╚══════╝ ╚═════╝  ╚═════╝ ╚══════╝                        \n");
	printf("\033[0m");
	printf("\033[1;36m");
	printf("\n      ✨ Descubre el Fractal Único de Tu Alma ✨\n");
	printf("         🌟 Comparte Tu Energía Cósmica 🌟\n");
	printf("\033[0m\n");
}

void	print_soul_animation(void)
{
	int	i;
	const char *frames[] = {
		"    ✨        ",
		"   ✨ ✨      ",
		"  ✨ 🔮 ✨    ",
		" ✨ 🔮 🔮 ✨  ",
		"✨ 🔮 💫 🔮 ✨",
	};

	printf("\n  Generando tu Fractal Soul");
	i = 0;
	while (i < 3)
	{
		printf(".");
		fflush(stdout);
		usleep(300000);
		i++;
	}
	printf("\n\n");
	i = 0;
	while (i < 5)
	{
		printf("\r  %s", frames[i]);
		fflush(stdout);
		usleep(200000);
		i++;
	}
	printf("\n\n");
}

void	print_share_instructions(const char *share_code)
{
	printf("\n");
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║              📱 COMPARTE TU FRACTAL SOUL 📱              ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n\n");
	printf("  🎯 PASO 1: Toma un screenshot (tecla 'P')\n");
	printf("  🎨 PASO 2: Sube a Instagram/TikTok\n");
	printf("  🔥 PASO 3: Usa estos hashtags:\n\n");
	printf("     #FractalSoul #%s #MyFractalSoul\n", share_code);
	printf("     #MathematicalArt #UniqueArt #DigitalArt\n\n");
	printf("  💬 CAPTION SUGERIDO:\n");
	printf("     \"✨ Este es mi Fractal Soul único en el universo!\n");
	printf("     Descubre el tuyo en [tu_link] 🔮\n");
	printf("     Share Code: %s 💫\"\n\n", share_code);
	printf("  🎬 BONUS: Graba un video del zoom infinito (tecla 'V')\n");
	printf("     ¡Perfecto para Reels/TikTok!\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("  🌟 Desafía a tus amigos a encontrar su Fractal Soul!\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

void	print_help_menu(void)
{
	print_ascii_logo();
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                    🎮 COMANDOS 🎮                        ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n\n");
	printf("  🌟 CREA TU FRACTAL SOUL:\n");
	printf("     ./fractol soul \"Tu Nombre\" DD MM YYYY\n");
	printf("     Ejemplo: ./fractol soul \"Maria Garcia\" 15 06 1995\n\n");
	printf("  🔮 HORÓSCOPO FRACTAL DIARIO:\n");
	printf("     ./fractol horoscope\n\n");
	printf("  🔑 USA UN SHARE CODE:\n");
	printf("     ./fractol soul [CODE]\n");
	printf("     Ejemplo: ./fractol soul ABC12XYZ\n\n");
	printf("  👑 FRACTALES DE CELEBRIDADES:\n");
	printf("     ./fractol celebs          (ver lista)\n");
	printf("     ./fractol celeb [nombre]  (cargar uno)\n\n");
	printf("  🎨 FRACTALES CLÁSICOS:\n");
	printf("     ./fractol mandelbrot\n");
	printf("     ./fractol julia [real] [imag]\n");
	printf("     ./fractol lorenz\n\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("  ⌨️  CONTROLES EN VENTANA:\n");
	printf("     Mouse Scroll  - Zoom in/out\n");
	printf("     Flechas       - Mover vista\n");
	printf("     C             - Cambiar colores\n");
	printf("     R             - Reset\n");
	printf("     P             - Screenshot para Instagram\n");
	printf("     ESC           - Salir\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
	printf("  💡 TIP: Experimenta con zoom y colores para\n");
	printf("      crear el screenshot perfecto para redes! 📸\n\n");
}
