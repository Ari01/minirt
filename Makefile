NAME		= minirt
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a

SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -L libft -lft -lm -L minilibx -lmlx -lXext -lX11 -lpthread
INCLUDES	= -I libft -I minilibx

RM			= rm -Rf

all :		$(MLX) $(LIBFT) $(NAME)

$(NAME) :	$(MLX) $(LIBFT) $(OBJS)
			$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCLUDES) $(LFLAGS)

$(LIBFT) :
			make -C libft

$(MLX) :
			cd minilibx && ./configure

.c.o :
			$(CC) -c $< -o $(<:.c=.o) $(CFLAGS) $(INCLUDES)

clean :
			$(RM) $(OBJS)

fclean :	clean
			make fclean -C libft
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re libft
