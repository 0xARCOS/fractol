/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcos <aarcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:05:41 by aarcos            #+#    #+#             */
/*   Updated: 2025/03/28 11:43:50 by aarcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "fractal_soul.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 800
# define MLX_ERROR 1

# define ESC 65307
# define PLUS 61
# define MINUS 45
# define W 119
# define S 115
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESQ_KEY 65307
# define ZOOM_IN 65451
# define ZOOM_OUT 65453
# define RESET 114
# define COLOR 99
# define MANDELBROT 0
# define JULIA 1
# define LORENZ 2

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		fractal_type;
	double	zoom;
	double	x_offset;
	double	y_offset;
	int		color_shift;
	int		bpp;
	int		size_line;
	int		endian;
	int		max_iter;
	double	c_real;
	double	c_imag;
	double	rho;
	double	sigma;
	double	beta;
	double	lorenz_speed;
}			t_data;

int			init(t_data *data);
void		handle_movement(int keycode, t_data *data);
void		handle_zoom(int keycode, t_data *data);
void		apply_color_change(int keycode, t_data *data);
void		handle_lorenz_keys(int keycode, t_data *data);
int			handle_key(int keycode, t_data *data);

void		put_pixel_to_image(t_data *data, int x, int y, int color);
void		render_fractal(t_data *data);
double		map_x(int x, t_data *data);
double		map_y(int y, t_data *data);
int			get_fractal_color(int iter, int max_iter, int color_shift);

void		draw_mandelbrot_pixel(t_data *data, int x, int y);
void		draw_mandelbrot(t_data *data);

int			julia(double x, double y, t_data *data);
void		draw_julia_pixel(t_data *data, int x, int y);
void		draw_julia(t_data *data);

int			get_lorenz_color(double z);
void		update_lorenz(double *x, double *y, double *z, t_data *data);
void		draw_lorenz(t_data *data);

int			ft_strcmp_insensitive(const char *s1, const char *s2);
double		ft_atof(const char *str);
void		set_julia_params(t_data *data, int argc, char **argv);
void		parse_arguments(t_data *data, int argc, char **argv);

#endif