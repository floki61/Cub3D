NAME = cub3d
# BNAME = so_long_bonus
FLAGS =  -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit 
 
SRCS =	main.c 					\
		tools/checker.c			\
		draw.c					\
		moves.c 				\
		tools/ft_split.c 		\
		tools/get_next_line.c	\
		tools/ft_itoi.c 		\
		tools/tools.c 			\

all: $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS)  -D BUFFER_SIZE=1000000 -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean:
	@rm -rf $(NAME) 

re: fclean all