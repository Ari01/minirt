NAME		= minirt
LIBFT		= libft/libft.a

SRCS		= camera.c \
error.c \
matrix1.c \
parser_utils.c \
save.c \
sphere.c \
triangle.c \
color.c \
grab_focus.c \
matrix2.c \
plane.c \
scene.c \
square.c \
vector2.c \
color_mix.c \
hook.c \
matrix_rotate.c \
ray.c \
set_objects.c \
trace_ray.c \
vector.c \
cylinder.c \
light.c \
object2.c \
render.c \
set_rt.c \
transform.c \
cylinder_caps.c \
main.c \
object.c \
rt.c \
set_scene.c \
transform_hook.c

SRCDIR		= src
INCLUDDIR	= includes
MLXDIR		= minilibx
LIBFTDIR	= libft

OBJS		= $(addprefix $(SRCDIR)/, $(SRCS:.c=.o))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
LIBFTFLAGS	= -L $(LIBFTDIR) -lft
MLXFLAGS	= -L $(MLXDIR) -lmlx -lXext -lX11
LFLAGS		= $(LIBFTFLAGS) $(MLXFLAGS) -lm
INCLUDES	= -I $(LIBFTDIR) -I $(MLXDIR) -I $(INCLUDDIR)

RM			= rm -Rf

all :		$(MLX) $(LIBFT) $(NAME)

$(NAME) :	$(OBJS)
			$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LFLAGS)

$(LIBFT) :
			make -C $(LIBFTDIR)

$(MLX) :
			make -C $(MLXDIR)

.c.o :
			$(CC) -c $< -o $(<:.c=.o) $(CFLAGS) $(INCLUDES)

clean :
			$(RM) $(OBJS)

fclean :	clean
			make fclean -C libft
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re libft
