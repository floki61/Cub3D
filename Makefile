NAME = cub3d
FLAGS =  -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit  #-g3 -fsanitize=address
 
SRCS =	main.c 					\
		tools/checker.c			\
		draw.c					\
		moves.c 				\
		tools/ft_split.c 		\
		tools/get_next_line.c	\
		tools/ft_itoi.c 		\
		tools/tools.c 			\
		utilites.c				\
		utilites_2.c			\
		raycasting.c 			\
		raycasting_tools.c 		\
		map.c 					\
		minimap.c 				\
		tools.c 				\
		project_wall.c 			\

all: $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS)  -D BUFFER_SIZE=1000000 -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean:
	@rm -rf $(NAME) 

re: fclean all