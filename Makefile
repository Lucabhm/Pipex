NAME = pipex
NAMEB = pipex_bonus
CFLAGS = -Wall -Werror -Wextra
SRCS = src/pipex.c \
		src/parsing.c \
		src/helper.c \
		src/free.c
SRCSB = src_bonus/pipex_bonus.c \
		src_bonus/helper_bonus.c \
		src/parsing.c \
		src/helper.c \
		src/free.c
OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)
PATHLIBFT = lib/libft
PATHGETNEXT = lib/get_next_line
INLIBFT = -L $(PATHLIBFT) -lft
INGETNEXT = -L $(PATHGETNEXT) -lftget_next_line
INPIPEX = -I include/pipex.h

RED = '\033[1;31m'
BLUE ="\033[1;34m"
DEF_COLOR = '\033[0;39m'

$(NAME):		$(OBJS)
				@echo $(BLUE)"Compiling libft..."$(DEF_COLOR)
				@cd $(PATHLIBFT) && $(MAKE)
				@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
				@cc $(OBJS) $(INLIBFT) -o $(NAME) $(INPIPEX) $(CFLAGS)

$(NAMEB):		$(OBJSB)
				
				@echo $(BLUE)"Compiling libft..."$(DEF_COLOR)
				@cd $(PATHLIBFT) && $(MAKE)
				@echo $(BLUE)"Compiling get_next_line..."$(DEF_COLOR)
				@cd $(PATHGETNEXT) && $(MAKE)
				@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
				@cc $(OBJSB) $(INLIBFT) $(INGETNEXT) -o $(NAMEB) $(INPIPEX) $(CFLAGS)

all:			$(NAME)

bonus:			$(NAMEB)

%.o:%.c
				@cc -c $< -o $@ $(CFLAGS)

clean:
				@echo $(RED)"Cleaning object files..."$(DEF_COLOR)
				@rm -f $(OBJS)
				@rm -f $(OBJSB)
				@cd $(PATHLIBFT) && $(MAKE) clean
				@cd $(PATHGETNEXT) && $(MAKE) clean

fclean:			clean
				@echo $(RED)"Cleaning executable files..."$(DEF_COLOR)
				@rm -f $(NAME)
				@rm -f $(NAMEB)
				@cd $(PATHLIBFT) && $(MAKE) fclean
				@cd $(PATHGETNEXT) && $(MAKE) fclean


re: fclean all

.PHONY: all clean fclean re bonus