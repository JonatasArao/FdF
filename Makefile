NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux

LIB_DIR = lib
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

HEADER_DIR = inc
HEADER = $(HEADER_DIR)/fdf.h
INCLUDES = -I$(HEADER_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRCS_DIR = src
SRCS_FILES = main.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME)

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

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
