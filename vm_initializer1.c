/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initilizer1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	create_vm(t_vm **vm)
{
	int	i;

	if ((*vm = ft_memalloc(sizeof(t_vm))) == NULL)
		die("Error: Out of memory!");
	(*vm)->cycle = 0;
	(*vm)->cycle_ = 0;
	(*vm)->cycle_to_die = CYCLE_TO_DIE;
	(*vm)->process = NULL;
	(*vm)->player = NULL;
	(*vm)->nbr_cycles = -1;
	(*vm)->checks = MAX_CHECKS;
	(*vm)->game_on = 1;
	(*vm)->log = 0;
	(*vm)->lives = 0;
	(*vm)->codage = init_codage();
	(*vm)->c_per_sec = 10;
	(*vm)->paused = 1;
	(*vm)->winner = NULL;
	(*vm)->fps = 50;
	(*vm)->p_n = 1;
	if (((*vm)->mem = ft_memalloc(MEM_SIZE * sizeof(t_map_cell *))) == NULL)
		die("Error: Out of memory!");
	i = 0;
	while (i < MEM_SIZE)
	{
		if (((*vm)->mem[i] = ft_memalloc(sizeof(t_map_cell))) == NULL)
			die("Error: Out of memory!");
		(*vm)->mem[i]->value = 0;
		(*vm)->mem[i]->last_update = 0;
		(*vm)->mem[i++]->player = NULL;
	}
}

char	*hex_string(unsigned char c)
{
	char			*ret;
	unsigned char	a;
	unsigned char	b;

	if ((ret = ft_memalloc(3 * sizeof(char))) == NULL)
		die("Error: Out of memory!");
	a = c % 16;
	b = (c / 16) % 16;
	if (b > 9)
		ret[0] = b - 10 + 'a';
	else
		ret[0] = b + '0';
	if (a > 9)
		ret[1] = a - 10 + 'a';
	else
		ret[1] = a + '0';
	ret[2] = 0;
	return (ret);
}

char	*string_from_binary(char *binary, int start, int length)
{
	char	*ret;
	int		i;
	char	c;
	int		j;

	if ((ret = ft_memalloc((length + 1) * sizeof(char))) == NULL)
		die("Error: Out of memory!");
	i = 0;
	j = 0;
	while (i < length)
	{
		c = int_from_hex(binary[start + j++]);
		c = c * 16 + int_from_hex(binary[start + j++]);
		ret[i++] = c;
	}
	ret[i] = 0;
	return (ret);
}

void	add_player(t_vm *vm, char *file, int idx)
{
	t_player	*p;
	t_player	*tmp;

	if ((p = ft_memalloc(sizeof(t_player))) == NULL)
		die("Error: Out of memory!");
	p->size = (int)bot_length(file + (size_t)((PROG_NAME_LENGTH + 4 + hex_len(COREWAR_EXEC_MAGIC)) * 2));
	p->vm = vm;
	p->n = -idx;
	p->name = string_from_binary(file, hex_len(COREWAR_EXEC_MAGIC) * 2, PROG_NAME_LENGTH);
	p->comment = string_from_binary(file, (hex_len(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 8) * 2 , COMMENT_LENGTH);
	file += (size_t)((PROG_NAME_LENGTH + COMMENT_LENGTH + 12 + hex_len(COREWAR_EXEC_MAGIC)) * 2);
	if ((p->instructions = ft_strdup(file)) == NULL)
		die("Error: Out of memory!");
	p->idx = idx;
	p->lives = 0;
	p->last_live = 0;
	p->next = NULL;
	if (vm->player == NULL)
		vm->player = p;
	else
	{
		tmp = vm->player;
		while (tmp->next != NULL)
		{
			if ((idx > 0) && (tmp->idx == idx))
				die("Error: Two players cannot have the same index!");
			tmp = tmp->next;
		}
		tmp->next = p;
	}
}

void	create_player(t_vm *vm, char *filename, int idx)
{
	int				fd;
	char			*tmp;
	char			*hex;
	unsigned char	c[1];
	char			*file;

	if ((fd = open(filename, O_RDONLY, 0)) == -1)
		die("Error: Cannot open champion file!");
	if ((file = ft_memalloc(sizeof(char))) == NULL)
		die("Error: Out of memory!");
	while (read(fd, c, 1) > 0)
	{
		tmp = file;
		hex = hex_string(c[0]);
		file = ft_strjoin(file, hex);
		free(hex);
		free(tmp);
	}
	validate_file(file);
	add_player(vm, file, idx);
	free(file);
}