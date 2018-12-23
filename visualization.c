#include "corewarVM.h"
# define Y_1 196
# define Y_2 57
# define X_1 67

static void	ft_colors(void)
{
	start_color();
	// init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	// init_pair(5, COLOR_BLACK, COLOR_RED);
	// init_pair(6, COLOR_BLACK, COLOR_CYAN);
	// init_pair(7, COLOR_WHITE, COLOR_GREEN);
	// init_pair(8, COLOR_WHITE, COLOR_BLUE);
	// init_pair(9, COLOR_WHITE, COLOR_RED);
	// init_pair(10, COLOR_WHITE, COLOR_CYAN);
	init_pair(11, COLOR_WHITE, COLOR_WHITE);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_color(COLOR_WHITE, 400, 400, 400);
}

void	initiate_visualization(t_vm *vm)
{
	(void)vm;
	initscr();
	curs_set(0);
	ft_colors();

}

static void draw_map(t_vm *vm)
{
	int i;
	int n;
	int j;

	j = 0;
	n = 2;
	while (n < 66)
	{
		i = 3;
		while (i <= 192)
		{
			if (vm->mem[j]->player != NULL)
				attron(COLOR_PAIR(vm->mem[j]->player->n));
			if (vm->mem[j]->last_update > 0)
			{
				vm->mem[j]->last_update--;
				attron(A_BOLD);
			}
			mvprintw(n, i, "%02x", vm->mem[j]->value);
			if (vm->mem[j]->player != NULL)
				attroff(COLOR_PAIR(vm->mem[j]->player->n) | A_BOLD);
			i += 3;
			j++;
		}
		n++;
	}
}

static void	draw_carrys(t_vm *vm)
{
	t_process *tmp;

	tmp = vm->process;
	while (tmp)
	{
		if (vm->mem[tmp->pc]->player == NULL)
			attron(COLOR_PAIR(5) | A_BOLD);
		else
			attron(COLOR_PAIR(vm->mem[tmp->pc]->player->n + 5));
		int x = tmp->pc / 64 + 2;
		int y = tmp->pc % 64 * 3 + 3;
		// fprintf(stderr, "%d\n", tmp->pc);
		mvprintw(x, y, "%02x", vm->mem[tmp->pc]->value);
		if (vm->mem[tmp->pc]->player == NULL)
			attroff(COLOR_PAIR(5));
		else
			attroff(COLOR_PAIR(vm->mem[tmp->pc]->player->n + 5));
		tmp = tmp->next;
	}
}

void	visualization(t_vm *vm)
{
	int i;
	int		j;
	int		num;

	i = 0;
	// initscr();
	// start_color();
	// ft_colors();
	attron(COLOR_PAIR(11));
	i = 67;
	while (i >= 0)
	{	
		mvprintw(i, 0, "*");
		mvprintw(i, Y_1 + Y_2, "*");
		mvprintw(i, Y_1, "*");
		i--;
	}
	i = 253;
	while (i >= 0)
	{
		mvprintw(0, i, "*");
		mvprintw(X_1, i, "*");
		i--;
	}
	attroff(COLOR_PAIR(11));
	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw(2, Y_1 + 3, "** PAUSED **");
	mvprintw(4, Y_1 + 3, "Cycles/second limit : %d", 50);
	mvprintw(7, Y_1 + 3, "Cycle : %d", (vm)->cycle);
	// mvprintw(9, Y_1 + 3, "Processes : %d", (vm)->proc);
	j = 11;
	num = 3;
	while (j < 23)
	{
		// mvprintw(j, Y_1 + 3, "Player -%d : ", (vm)->player[num].idx);
		color_set(num + 1, NULL);
		// printw("%s", (vm)->player[num].name);
		color_set(12, NULL);
		// mvprintw(++j, Y_1 + 5, "Last live : %23d", (vm)->player[num].last_live);
		// mvprintw(++j, Y_1 + 5, "Lives in current period : %9d", (vm)->player[num].lives);
		j += 2;
	}
	num = 0;
	mvprintw(j, Y_1 + 3, "Live breakdown for current period :");
	mvprintw(j + 3, Y_1 + 3, "Live breakdown for last period :");
	attroff(A_BOLD);
	num = 0;
	while (++num <= 50)
	{
		mvprintw(j + 1, Y_1 + 3 + num, "-");
		mvprintw(j + 4, Y_1 + 3 + num, "-");
	}
	attron(COLOR_PAIR(13) | A_BOLD);
	mvprintw(j + 1, Y_1 + 3, "[");
	mvprintw(j + 4, Y_1 + 3, "[");
	mvprintw(j + 1, Y_1 + 3 + num, "]");
	mvprintw(j + 4, Y_1 + 3 + num, "]");
	color_set(12, NULL);
	mvprintw(j + 6, Y_1 + 3, "CYCLE_TO_DIE : %d", (vm)->cycle_to_die);
	// mvprintw(j + 8, Y_1 + 3, "CYCLE_DELTA : %d", (vm)->cycle_delta);
	// mvprintw(j + 10, Y_1 + 3, "NBR_LIVE : %d", (vm)->nbr_live);
	// mvprintw(j + 12, Y_1 + 3, "MAX_CHECKS : %d", (vm)->max_checks);
	attroff(A_BOLD);

	draw_map(vm);
	draw_carrys(vm);
	refresh();

	char c = getch();
	if (c == 27)
	{
		endwin();
		exit(0);
	}
}
