AS_NAME =	asm

VM_NAME	=	corewar

VM_SRS	= 	main.c \
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
VM_DIR  =	vm_sources/
VM_SRCS =	$(addprefix $(VM_DIR), $(VM_SRS))

VM_INC	=	vm_sources/corewarvm.h \
			op.h

VM_OBJS	=	$(VM_SRCS:.c=.o)

all: 
	make $(VM_NAME)

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

$(VM_NAME): libft
	gcc -lncurses -o $(VM_NAME) $(VM_OBJS) libft/libft.a

$(VM_DIR):
	@mkdir -p $(VM_DIR)

.PHONY: libft
libft:
	@make -C libft

clean:
	rm -f *.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
