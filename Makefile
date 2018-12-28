NAME	=	corewar

SRCS	= 	main.c \
			vm_initializer1.c \
			vm_initializer2.c \
			vm_initializer3.c \
			helper1.c \
			helper2.c \
			helper3.c \
			helper4.c \
			validator1.c \
			data_reader.c \
			outputter1.c \
			game1.c \
			game2.c \
			game3.c \
			game4.c \
			visualization1.c \
			visualization2.c\

INC		=	corewarvm.h \
			op.h

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

%.o : %.c $(INC)
	@gcc -Wall -Wextra -c $< -o $@

$(NAME): libft $(OBJS) $(INC)
	@gcc -lncurses -o $(NAME) $(OBJS) libft/libft.a

.PHONY: libft
libft:
	make -C libft

clean:
	rm -f *.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
