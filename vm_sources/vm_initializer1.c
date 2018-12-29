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

void	set_vm_initial_values(t_vm *vm)
{
	vm->cycle = 0;
	vm->cycle_ = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->process = NULL;
	vm->player = NULL;
	vm->nbr_cycles = -1;
	vm->checks = MAX_CHECKS;
	vm->game_on = 1;
	vm->log = 0;
	vm->lives = 0;
	vm->codage = init_codage();
	vm->c_per_sec = 10;
	vm->paused = 1;
	vm->winner = NULL;
	vm->fps = 50;
	vm->p_n = 1;
}

void	create_vm(t_vm **vm)
{
	int	i;

	if ((*vm = ft_memalloc(sizeof(t_vm))) == NULL)
		die("Error: Out of memory!");
	set_vm_initial_values(*vm);
	if (((*vm)->mem = ft_memalloc(sizeof(t_map_cell *) * MEM_SIZE)) == NULL)
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
