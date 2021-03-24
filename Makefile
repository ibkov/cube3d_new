NAME = cube3D

SRC = 	cube3d.c \
		check_file.c \
		parse_texture_path.c \
		parse_main_arguments.c \
		parse_floor_ceil.c \
		parse_map.c \
		utils_cube.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		ray_casting_norm.c \
		ray_casting_norme.c \
		errors_print.c \
		check_error_map.c



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