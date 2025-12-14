NAME		= fractol

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -I../minilibx-linux

MLX_DIR		= ../minilibx-linux
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR		= src
SRCS		= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/hooks.c \
	$(SRC_DIR)/julia.c \
	$(SRC_DIR)/mandelbrot.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/input.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
