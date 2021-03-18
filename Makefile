NAME = cub3D

B_NAME = cub3D_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = ./mlx

LXFLAGS = -lmlx -framework OpenGL -framework Appkit

SRCS =		main.c cub3d.c \
			parse.c parse_tools.c parse_tools_details.c \
			parse_check.c \
			engine.c raycasting.c sprite.c sprite_details.c \
			draw.c key.c tools.c \
			bitmap.c \
			utils/atoi.c utils/strchr.c utils/skipspace.c \
			utils/strdup.c utils/strjoin.c utils/strlen.c \
			utils/strlcpy.c utils/strlcat.c utils/substr.c \
			gnl/get_next_line.c

B_SRCS =	bonus/main_bonus.c bonus/cub3d_bonus.c \
			bonus/parse_bonus.c bonus/parse_tools_bonus.c \
			bonus/parse_tools_details_bonus.c bonus/parse_check_bonus.c \
			bonus/engine_bonus.c bonus/raycasting_bonus.c \
			bonus/sprite_bonus.c bonus/sprite_details_bonus.c \
			bonus/draw_bonus.c bonus/key_bonus.c \
			bonus/tools_bonus.c bonus/bitmap_bonus.c \
			bonus/time_bar_bonus.c bonus/bgm_bonus.c \
			bonus/utils_bonus/atoi_bonus.c bonus/utils_bonus/strchr_bonus.c \
			bonus/utils_bonus/skipspace_bonus.c bonus/utils_bonus/strdup_bonus.c \
			bonus/utils_bonus/strjoin_bonus.c bonus/utils_bonus/strlen_bonus.c \
			bonus/utils_bonus/strlcpy_bonus.c bonus/utils_bonus/strlcat_bonus.c \
			bonus/utils_bonus/substr_bonus.c \
			bonus/gnl_bonus/get_next_line_bonus.c

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

.PHONY: all clean fclean re basic sample bmp1 bmp2 norm b_all b_clean b_fclean b_re bonus b_bmp b_norm

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L$(MLX) $(LXFLAGS) $(OBJS)
	@echo "\033[0m"

clean:
	@echo "\n\033[0;31mCleaning..."
	rm -rf $(OBJS)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

basic: re
	./$(NAME) maps/example.cub

sample: re
	./$(NAME) maps/cub3d.cub

bmp1: re
	./$(NAME) maps/example.cub --save

bmp2: re
	./$(NAME) maps/cub3d.cub --save

norm:
	norminette ./*.c ./*.h utils/*.c utils/*.h gnl/*.c gnl/*.h

b_all: $(B_NAME)

$(B_NAME): $(B_OBJS)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(B_NAME) -L$(MLX) $(LXFLAGS) $(B_OBJS)
	@echo "\033[0m"

b_clean:
	@echo "\n\033[0;31mCleaning..."
	rm -rf $(B_OBJS)
	rm -f bitmap_bonus.bmp
	@echo "\033[0m"

b_fclean: b_clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(B_NAME)
	@echo "\033[0m"

b_re: b_fclean b_all

bonus: b_re
	./$(B_NAME) bonus/maps_bonus/cub3d_bonus.cub

b_bmp: b_re
	./$(B_NAME) bonus/maps_bonus/cub3d_bonus.cub --save

b_norm:
	norminette ./bonus/*.c ./bonus/*.h ./bonus/utils_bonus/*.c ./bonus/utils_bonus/*.h ./bonus/gnl_bonus/*.c ./bonusgnl_bonus/*.h

aclean: fclean b_fclean
