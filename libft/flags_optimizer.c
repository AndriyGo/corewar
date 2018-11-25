/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_optimizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/25 17:50:12 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	optimise_flags(t_format *flags)
{
	if ((flags->type == 'S') || (flags->type == 'C') || (flags->type == 'D') \
		|| (flags->type == 'O') || (flags->type == 'U'))
	{
		flags->size = L;
		flags->type = ft_tolower(flags->type);
	}
	if (flags->neg_width == 1)
		flags->zero_pad = 0;
	if (flags->min_width < 0)
	{
		flags->min_width *= -1;
		flags->neg_width = 1;
	}
}

int		read_format2(const char **c, t_format *ret)
{
	if (**c == '#')
		ret->alternate = 1;
	else if (**c == '0')
		ret->zero_pad = 1;
	else if (**c == '-')
		ret->neg_width = 1;
	else if (**c == ' ')
		ret->space = 1;
	else if (**c == '+')
		ret->sign_always = 1;
	else if (((**c == 'h') || (**c == 'l') || (**c == 'j') || (**c == 'z')))
		read_size(c, ret);
	else if ((**c >= '0') && (**c <= '9'))
		ret->min_width = read_number(c);
	else
		return (0);
	return (1);
}
