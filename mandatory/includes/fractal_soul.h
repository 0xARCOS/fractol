/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_soul.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by aarcos            #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_SOUL_H
# define FRACTAL_SOUL_H

# include <time.h>

# define SOUL_MODE 3
# define HOROSCOPE_MODE 4

typedef struct s_data	t_data;

typedef struct s_soul_params
{
	char		*name;
	int			day;
	int			month;
	int			year;
	unsigned long	soul_code;
	double		c_real;
	double		c_imag;
	int			color_seed;
	int			fractal_variant;
	char		*zodiac_sign;
	char		*soul_message;
}				t_soul_params;

typedef struct s_celebrity
{
	char		*name;
	unsigned long	soul_code;
	char		*share_code;
	int			fractal_type;
}				t_celebrity;

// Soul generation functions
unsigned long	generate_soul_hash(const char *name, int day, int month, int year);
void			soul_to_fractal_params(unsigned long soul_code, t_data *data);
void			print_soul_info(t_soul_params *soul);
void			generate_share_code(unsigned long soul_code, char *output);
unsigned long	decode_share_code(const char *code);

// Horoscope functions
void			generate_daily_horoscope(t_data *data);
const char		*get_zodiac_sign(int day, int month);
const char		*get_fractal_message(unsigned long soul_code);

// Celebrity database
void			load_celebrity_fractal(t_data *data, const char *name);
void			list_celebrities(void);

// Export functions
void			export_screenshot_instagram(t_data *data, const char *filename);
void			start_zoom_recording(t_data *data);
void			stop_zoom_recording(t_data *data);

// Viral display functions
void			print_ascii_logo(void);
void			print_soul_animation(void);
void			print_share_instructions(const char *share_code);

#endif
