NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c \
		ft_printvalue.c \
		ft_helper.c \
		ft_helper_helper.c
OBJS = $(SRCS:.c=.o)

$(NAME):		$(OBJS)
				@ar rc $(NAME) $(OBJS)

all:			$(NAME)

%.o:%.c
				@cc -c $^ -o $@ $(CFLAGS)

clean:
				@rm -f $(OBJS)

fclean:			clean
				@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re