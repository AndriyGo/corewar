#ifndef COREWAR_VM_H
# define COREWAR_VM_H
# include "op.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>

struct					s_vm;

typedef	struct 			s_process
{
	char				carry;
	int					*regs;
	int					pc;
	int					delay;
	int					live;
	unsigned char		inst;
	struct s_process	*next;
	struct s_vm			*vm;
}						t_process;

typedef struct			s_player
{
	int					last_live;
	int					lives;
	int					idx;
	char				*name;
	char				*comment;
	char				*instructions;
	struct s_player		*next;
	struct s_vm				*vm;
}						t_player;

typedef struct			s_map_cell
{
	unsigned char		value;
	t_player			*player;
	int					last_update;
}						t_map_cell;

typedef	struct			s_vm
{
	int					cycle;
	int					cycle_to_die;
	char				visual_mode;
	char				nbr_cycles;
	t_map_cell			**mem;
	t_process			*process;
	t_player			*player;
}						t_vm;

void					die(char *s);
void					create_vm(t_vm **vm);
int						hex_len(unsigned int hex);
void					validate_file(char *file);
int						hex_to_int(char c);
void					create_player(t_vm *vm, char *filename, int idx);
int						player_index(int i, int argc, char **argv);
void					read_dump(t_vm *vm, int i, int argc, char **argv);
void					print_usage();
int						int_from_hex(char c);
void					dump(t_vm *vm);
void					add_process(t_vm *vm, int pc);
int						next_pc(int pc, int offset);
void					tik_process(t_process *pr);

#endif