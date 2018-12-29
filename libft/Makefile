# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 23:11:16 by agordiyc          #+#    #+#              #
#    Updated: 2018/10/29 14:07:34 by agordiyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	= 	ft_atoi.c \
			ft_bzero.c \
			ft_count_and_delim_words.c \
			ft_fill_arr_with_null_term_words.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespace.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstappend.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstdup.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_max.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_range.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strniter.c \
			ft_strniteri.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			format_flags_reader.c \
			ft_printf.c \
			flags_optimizer.c \
			string_printer1.c \
			string_printer2.c \
			postprocessor1.c \
			number_helper.c \
			number_printer.c \
			unicode.c

OBJS	=	$(SRCS:.c=.o)

INC		=	libft.h

all: $(NAME)

%.o : %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
