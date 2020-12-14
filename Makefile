NAME			= minirt

SRC				= camera.c \
color.c \
hook.c \
light.c \
main.c \
object_intersection.c \
print.c \
ray.c \
sphere.c \
vector.c

SRCS			= $(addprefix $(SRCDIR), $(SRC))

OBJS			= $(SRCS:.c=.o)

SRCDIR			= src/
INCLUDEDIR		= includes

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L minilibx -lmlx -lXext -lX11 -lm
INCLUDES		= -I $(INCLUDEDIR)

RM				= rm -Rf

MLXDIR			= minilibx
MLXLIB			= $(MLXDIR)/libmlx.a

all :			$(MLXLIB) $(NAME)

$(NAME) :		$(OBJS)
				$(CC) -o $@ $^ $(CLFAGS) $(LFLAGS) $(INCLUDES)

run :			$(NAME)
				./minirt

$(MLXLIB) :
				cd $(MLXDIR) && ./configure
		
.c.o :
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCLUDES)

clean :			
				$(RM) $(OBJS)

fclean :		clean
				$(RM) $(NAME)

re :			fclean all

.PHONY :		all clean fclean re
