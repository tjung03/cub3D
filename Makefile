NAME = cub3D

CC= gcc

CFLAGS = -03 -Wall -Wextra -Werror

MLX = mlx

LXFLAGS = -lmlx -framework OpenGL -framework Appkit

SRCS = \

B_SRCS = \

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJS)

clean: clean
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

bonus: fclean $(B_OBJS)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_OBJS)