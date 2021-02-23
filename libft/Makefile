# VAR

NAME			= libft.a
LIB				= ar cr

TEST			= test
TESTDIR			= resources/
TESTS			= test_part1 test_additional_functions test_bonus

SRCS			= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c get_next_line.c ft_atod.c ft_dec_to_hex.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
LDFLAGS			= -I . -lbsd -L. -lft
RM				= rm -f

# RULES 

all :			$(NAME)

$(NAME) :		$(OBJS)
				$(LIB) $@ $^

$(TEST) :		$(TESTS)

$(TESTS) :		%: $(TESTDIR)%.c $(NAME)
				$(CC) $(CLFAGS) -o $@ $< $(LDFLAGS)

.c.o :
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
				$(RM) $(OBJS)

fclean :		clean
				$(RM) $(NAME) $(TESTS)

re :			fclean all

.PHONY :		all clean fclean re test
