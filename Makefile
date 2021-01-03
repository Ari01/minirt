NAME		= minirt
LIBFT		= libft/libft.a

SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -L libft -lft -lm -lmlx -lXext -lX11
INCLUDES	= -I libft

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
