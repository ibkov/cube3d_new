NAME = cube3D

SRC = cude.c \
		proc_keys.c \
		parcer_map.c \
		ray_casting.c \
		parse_texture_path.c \
		parse_main_arguments.c \
		parse_floor_ceil.c \
		parse_map.c \
		utils_cube.c \
		init_begin_position.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C minilibx
		mv minilibx/libmlx.a .
		make -C libft
		mv libft/libft.a .
		gcc -Wall -g -Werror -Wextra -c $(SRC)
		gcc -Wall -g -Werror -Wextra -L. -lmlx -lft -framework OpenGL -framework Appkit $(OBJ) -o $(NAME)

clean:
		make -C minilibx clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx clean
		rm -rf $(NAME)

re : fclean all