# Nombre del ejecutable
NAME = fractol

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux -Isrc -g3 -Ofast -march=native -funroll-loops -flto

# Directorios
SRC_DIR = src
EJERS_DIR = ejers
MLX_DIR = minilibx-linux

# Flags para MiniLibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Regla principal
all: $(NAME)

# Compilar ejecutable principal
$(NAME): $(OBJS)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

# Compilación de ejercicios (test)
EJERS_SRCS = $(wildcard $(EJERS_DIR)/*.c)
EJERS_BINS = $(patsubst $(EJERS_DIR)/%.c, $(EJERS_DIR)/%, $(EJERS_SRCS))

test: $(EJERS_BINS)

$(EJERS_DIR)/%: $(EJERS_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $< -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Limpiar objetos
clean:
	rm -f $(OBJS)

# Limpiar todo
fclean: clean
	rm -f $(NAME) $(EJERS_BINS)

# Recompilar desde cero
re: fclean all
