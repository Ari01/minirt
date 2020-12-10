NAME			= minirt

SRCS			= main.c
OBJS			= $(SRCS:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L minilibx -lmlx -lXext -lX11

RM				= rm -Rf

MLXDIR			= minilibx
MLXLIB			= $(MLXDIR)/libmlx.a

all :			$(MLXLIB) $(NAME)

$(NAME) :		$(OBJS)
				$(CC) -o $@ $^ $(CLFAGS) $(LFLAGS)

run :			$(NAME)
				./minirt

$(MLXLIB) :
				cd $(MLXDIR) && ./configure
		
.c.o :
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :			
				$(RM) $(OBJS)

fclean :		clean
				$(RM) $(NAME)

re :			fclean all

.PHONY :		all clean fclean re
