#include "corewarVM.h"

void	die(char *s)
{
	ft_printf("%s\n", s);
	exit(-1);
}

int		hex_to_int(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (c - '0');
	if ((c >= 'A') && (c <= 'F'))
		return (c - 'A' + 10);
	if ((c >= 'a') && (c <= 'f'))
		return (c - 'a' + 10);
	return (-1);
}

int		hex_len(unsigned int hex)
{
	int	i;

	i = 0;
	while (hex > 0)
	{
		hex /= 255;
		i++;
	}
	if (i % 2 == 1)
		i++;
	return (i);
}

int		int_from_hex(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (c - '0');
	if ((c >= 'a') && (c <= 'f'))
		return (10 + c - 'a');
	if ((c >= 'A') && (c <= 'F'))
		return (10 + c - 'A');
	die("Error: champion binary contains invalid hex!");
	return (-1);
}

int		next_pc(int pc, int offset)
{
	return ((pc + offset) % MEM_SIZE);
}