/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initializer3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	create_player2(t_vm *vm, char *filename, int idx)
{
	int				fd;
	char			*tmp;
	char			*hex;
	unsigned char	c[1];
	char			*file;

	if (((tmp = ft_strstr(filename, ".cor")) == NULL) || (*(tmp + 4) != 0))
		die("Error: Champion file must have .cor extension!");
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

void	insert_player(t_vm *vm, t_player *p, int idx)
{
	t_player	*tmp;

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

void	add_player(t_vm *vm, char *file, int idx)
{
	t_player	*p;

	if ((p = ft_memalloc(sizeof(t_player))) == NULL)
		die("Error: Out of memory!");
	p->size = (int)bot_length(file + \
		(size_t)((PROG_NAME_LENGTH + 4 + hex_len(COREWAR_EXEC_MAGIC)) * 2));
	p->vm = vm;
	p->n = -idx;
	p->name = string_from_binary(file, hex_len(COREWAR_EXEC_MAGIC) * 2,
		PROG_NAME_LENGTH);
	p->comment = string_from_binary(file,
		(hex_len(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + 8) * 2,
		COMMENT_LENGTH);
	file += (size_t)((PROG_NAME_LENGTH + COMMENT_LENGTH + 12 + \
		hex_len(COREWAR_EXEC_MAGIC)) * 2);
	if ((p->instructions = ft_strdup(file)) == NULL)
		die("Error: Out of memory!");
	p->idx = idx;
	p->lives = 0;
	p->last_live = 0;
	p->next = NULL;
	insert_player(vm, p, idx);
}

void	create_player(t_vm *vm, char *filename, int *idx)
{
	int				fd;
	char			*tmp;
	char			*hex;
	unsigned char	c[1];
	char			*file;

	if (((tmp = ft_strstr(filename, ".cor")) == NULL) || (*(tmp + 4) != 0))
		die("Error: Champion file must have .cor extension!");
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
	add_player(vm, file, *idx);
	free(file);
	*idx = -1;
}
