NAME	= minishell

CFLAGS	= -g -Wall -Werror -Wextra

SRCS	= minishell.c built_cd_env_exit.c parse.c parse_utils.c parse_utils2.c parse_utils3.c parse_utils4.c pipes.c execution.c rdir.c \
			helper_functions.c helper_functions2.c expansions.c expansions_utils.c expansions_utils2.c expansions_utils3.c \
			utils.c utils2.c utils3.c utils4.c utils5.c utils6.c change.c signal.c signal_utils.c syntax_verify.c \
			built_echo_unset.c built_export.c built_pwd.c others2.c others.c built_helper.c helper_functions3.c

LIBFT_DIR	= ./libft/

OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_DIR)
	@cc $(CFLAGS) $(OBJS) -I./libft ./libft/libft.a -lreadline -o $(NAME)
	@echo Minishell compiled.

%.o : %.c
	@cc -c -g $(CFLAGS) $< -o $@

.PHONY: all clean fclean re 

all: $(NAME)

clean:                                                                                                               
	@rm -f $(OBJS)
	@rm -f $(LIBFT_DIR)*.o
	@echo Minishell Gone!

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)*.a
	@echo Minishell REALLY GONE!

re: fclean all
