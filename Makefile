NAME = cub3D

CC = gcc

#CFLAGS = -03 -Wall -Wextra -Werror

MLX = ./mlx

LXFLAGS = -lmlx -framework OpenGL -framework Appkit

SRCS =	main.c cub3d.c \
		parse.c parse_tools.c parse_tools_details.c \
		parse_check.c \
		engine.c raycasting.c \
		draw.c key.c tools.c \
		bitmap.c \
		utils/atoi.c utils/strchr.c utils/skipspace.c \
		utils/strdup.c utils/strjoin.c utils/strlen.c \
		utils/strlcpy.c utils/strlcat.c utils/substr.c \
		gnl/get_next_line.c

B_SRCS = \

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L$(MLX) $(LXFLAGS) $(OBJS)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJS)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

bonus: fclean $(B_OBJS)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_OBJS)
	./$(NAME) maps/cub3d_bonus.cub

basic: re
	./$(NAME) maps/cub3d.cub

bmp: re
	./$(NAME) maps/cub3d.cub --save

norm:
	norminette ./*.c ./*.h utils/*.c utils/*.h gnl/*.c gnl/*.h
