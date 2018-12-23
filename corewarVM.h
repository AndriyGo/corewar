#ifndef COREWAR_VM_H
# define COREWAR_VM_H
# include "op.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h> //////////////////////////// added by Julia
# include <ncurses.h> ///////////

struct					s_vm;

typedef struct			s_player
{
	int					last_live;
	int					lives;
	int					idx;
	int					n;
	char				*name;
	char				*comment;
	char				*instructions;
	struct s_player		*next;
	struct s_vm			*vm;
}						t_player;

typedef	struct 			s_process
{
	char				carry;
	int					*reg;
	int					pc;
	int					delay;
	int					live;
	int					l_size;
	unsigned char		inst;
	struct s_process	*next;
	struct s_vm			*vm;
	struct s_player		*player;
}						t_process;

typedef struct			s_codage
{
	int					*type;
	int					*value;
	int					*raw_value;
	int					valid;
	int					to_skip;
}						t_codage;

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
	int				 	checks;
	int					game_on;
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
void					add_process(t_vm *vm, int pc, t_player *player);
int						next_pc(int pc, int offset);
void					tik_process(t_process *pr);
unsigned int			read_bytes(t_vm *vm, int pc, unsigned int n_bytes);
void					copy_process(t_vm *vm, t_process *ref);
t_codage				*read_codage(t_vm *vm, t_process *process, int nf);
void					dump_to_mem(t_process *pr, int len, int val, int idx);
void					ex_live(t_process *pr);
void					ex_lfork(t_process *pr);
void					ex_zjmp(t_process *pr);
void					ex_fork(t_process *pr);
void					ex_load(t_process *pr);
void					ex_st(t_process *pr);
void					ex_add(t_process *pr);
void					ex_sub(t_process *pr);
void					ex_and(t_process *pr);
void					ex_or(t_process *pr);
void					ex_xor(t_process *pr);
void					ex_ldi(t_process *pr);
void					ex_sti(t_process *pr);
void					ex_lld(t_process *pr);
void					ex_lldi(t_process *pr);
void					ex_aff(t_process *pr);
void					ex_lfork(t_process *pr);

void					initiate_visualization(t_vm *vm); //////////////////////////// added by Julia
void					visualization(t_vm *vm);

#endif