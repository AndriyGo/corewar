#ifndef COREWAR_VM_H
# define COREWAR_VM_H
# include "op.h"
# include "libft.h"

typedef	struct 			s_process
{
	char				carry;
	int					*regs;
	int					pc;
	struct s_process	*next;
	t_vm				*vm;
}						t_process;

typedef struct			s_map_cell
{
	unsigned char		value;
	t_player			*player;
	int					last_update;
}						t_map_cell;

typedef struct			s_player
{
	int					last_live;
	int					lives;
	int					idx;
	char				*name;
	struct s_player		*next;
	t_vm				*vm;
}						t_player;

typedef	struct			s_vm
{
	int					cycle;
	int					cycle_to_die;
	t_map_cell			**map;
	t_process			*process;
	t_player			*player;
}						t_vm;

void					die(char *s);
void					create_vm(t_vm **vm);

#endif