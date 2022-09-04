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

# SRCSB =	so_long_bonus.c			\
# 		put_string_bonus.c 			\
# 		checker_bonus.c			\
# 		draw_bonus.c			\
# 		moves_bonus.c 			\
# 		tools/ft_split.c 		\
# 		tools/get_next_line.c	\
# 		tools/ft_itoi.c 		\
# 		tools/tools.c 			\

		

all: $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS)  -D BUFFER_SIZE=1000000 -o $(NAME)

# bonus: fclean $(BNAME)

# $(BNAME) : $(SRCSB)
# 	@gcc $(FLAGS) $(SRCSB) -D BUFFER_SIZE=1000000 -o $(BNAME)

clean :
	@rm -rf $(NAME)
fclean:
	@rm -rf $(NAME) 

re: fclean all