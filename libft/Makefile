NAME	= libft.a

SRCS	= ft_atoi.c			ft_bzero.c				ft_calloc.c			\
		ft_flags_bonus.c	ft_get_next_line.c		ft_isalnum.c		\
		ft_isalpha.c		ft_isascii.c			ft_isdigit.c		\
		ft_isprint.c		ft_itoa.c				ft_lstadd_back.c	\
		ft_lstadd_front.c	ft_lstclear.c			ft_lstdelone.c		\
		ft_lstiter.c		ft_lstlast.c			ft_lstmap.c			\
		ft_lstnew.c			ft_lstsize.c			ft_memchr.c			\
		ft_memcmp.c			ft_memcpy.c				ft_memmove.c		\
		ft_memset.c			ft_precision_bonus.c	ft_print_addr.c		\
		ft_print_base.c		ft_print_char.c			ft_printf.c			\
		ft_print_nbr.c		ft_print_str.c			ft_print_uns_nbr.c	\
		ft_putchar_fd.c		ft_putendl_fd.c			ft_putnbr_fd.c		\
		ft_putstr_fd.c		ft_size.c				ft_split.c			\
		ft_strchr.c			ft_strdup.c				ft_striteri.c		\
		ft_strjoin.c		ft_strlcat.c			ft_strlcpy.c		\
		ft_strlen.c			ft_strmapi.c			ft_strncmp.c		\
		ft_strnstr.c		ft_strrchr.c			ft_strtrim.c		\
		ft_substr.c			ft_tolower.c			ft_toupper.c		\
		ft_width_bonus.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -I.

$(NAME) : $(OBJS)
	@ar -crs $@ $^
	@echo LibFT compiled.

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo LibFT binaries deleted.

fclean: clean
	@rm -f $(NAME)
	@echo LibFT completely deleted.

re: fclean all