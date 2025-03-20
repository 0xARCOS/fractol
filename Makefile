# Nombre del ejecutable
NAME = fractol

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux -Isrc -g3 -Ofast -march=native -funroll-loops -flto

# Archivos fuente dentro de src/
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Directorio de MiniLibX
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Regla principal
all: $(NAME)

# Compilar fractol
$(NAME): $(OBJS)
	@make -C $(MLX_DIR) # Compilar MiniLibX si es necesario
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

# Regla para compilar archivos .c en .o dentro de src/
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	rm -f $(OBJS)

# Limpiar todo (ejecutable + objetos)
fclean: clean
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all
