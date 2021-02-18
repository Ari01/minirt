NAME		= minirt
LIBFT		= libft/libft.a

SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -L libft -lft -lm -L minilibx -lmlx -lXext -lX11
INCLUDES	= -I libft -I minilibx

RM			= rm -Rf

all :		$(LIBFT) $(NAME)

$(NAME) :	$(OBJS)
			$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LFLAGS)

$(LIBFT) :
			make -C libft

.c.o :
			$(CC) -c $< -o $(<:.c=.o) $(CFLAGS) $(INCLUDES)

clean :
			$(RM) $(OBJS)

fclean :	clean
			make fclean -C libft
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re libft
