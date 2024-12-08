NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

LIB_DIR = lib
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

HEADER_DIR = inc
HEADER = $(HEADER_DIR)/fdf.h
INCLUDES = -I$(HEADER_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRCS_DIR = src
SRCS_FILES = parse.c vectorize.c map.c transform.c draw.c render.c main.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME) $(MLX_LIB) $(LIBFT_LIB)

re: fclean all

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
