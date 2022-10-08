NAME = cub3d
# BNAME = so_long_bonus
FLAGS =  -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit  -fsanitize=address
 
SRCS =	main.c 					\
		tools/checker.c			\
		draw.c					\
		moves.c 				\
		tools/ft_split.c 		\
		tools/get_next_line.c	\
		tools/ft_itoi.c 		\
		tools/tools.c 			\
		utilites.c				\
<<<<<<< HEAD
		utilites_2.c			\
		raycasting.c 			\
		raycasting_tools.c 		\
		map.c 					\
=======
		utilites_2.c
>>>>>>> 2693f92367358d5c20048a3d86296e22bd8117b8

all: $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS)  -D BUFFER_SIZE=1000000 -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean:
	@rm -rf $(NAME) 

re: fclean all