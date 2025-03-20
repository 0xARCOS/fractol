#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h" // Incluye Minilibx
# include <math.h>                  // Para funciones matemáticas
# include <stdio.h>                 // Para pritf()
# include <stdlib.h>                // Para exit()
# include <unistd.h>                // Para write

# define WIDTH 800
# define HEIGHT 600
# define MLX_ERROR 1

// key
# define ESC 65307
# define PLUS 61
# define MINUS 45
# define W 119
# define S 115
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESQ_KEY 65307  // close
# define LEFT 65361     // Flecha izquierda
# define RIGHT 65363    // Flecha derecha
# define UP 65362       // Flecha arriba
# define DOWN 65364     // Flecha abajo
# define ZOOM_IN 65451  // Tecla "+"
# define ZOOM_OUT 65453 // Tecla "-"
# define RESET 114      // Tecla "r"
# define COLOR 99       // Tecla "c"
# define MANDELBROT 0
# define JULIA 1
# define LORENZ 2

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     fractal_type;
    double  zoom;
    double  x_offset;
    double  y_offset;
    int     color_shift;
    int     bpp;
    int     size_line;
    int     endian;

    // Parámetros para el atractor de Lorenz
    double  rho;
    double  sigma;
    double  beta;
    double  lorenz_speed;
} t_data;


// init.c
int		init(t_data *data);
// hook.c
void	move_fractal(int keycode, t_data *data);
void	zoom_fractal(int keycode, t_data *data);
void	reset_or_change_color(int keycode, t_data *data);
int		handle_key(int keycode, t_data *data);
// render
void	put_pixel_to_image(t_data *data, int x, int y, int color);
void	render_fractal(t_data *data);
double	map_x(int x, t_data *data);
double	map_y(int y, t_data *data);

// mandelbrot.c
void	draw_mandelbrot(t_data *data);
int		mandelbrot(double x, double y, t_data *data);
// Julia
void	draw_julia(t_data *data);
int		julia(double x, double y, t_data *data);
// Lorenz
void	draw_lorenz(t_data *data);
#endif
