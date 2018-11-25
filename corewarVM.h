#ifndef COREWAR_VM_H
# define COREWAR_VM_H

typedef	struct 	s_process
{
	char				carry;
	int					*regs;
	int					pc;
	struct s_process	*next;
	t_vm				*vm;
}				t_process;

typedef struct	s_player
{
	int					last_live;
	int					lives;
	int					idx;
	char				*name;
	struct s_player		*next;
	t_vm				*vm;
}				t_player;

typedef	struct	s_vm
{
	int					cycle;
	int					cycle_to_die;
	char				*mem;
	t_process			*process;
	t_player			*player;
}				t_vm;

#endif