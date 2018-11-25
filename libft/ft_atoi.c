/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 16:40:59 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char	*prcs;
	long	ret;
	int		is_neg;
	int		step;

	prcs = (char *)str;
	while (*prcs && ft_iswhitespace(*prcs))
		prcs++;
	is_neg = (*prcs == '-');
	if (is_neg || (*prcs == '+'))
		prcs++;
	ret = 0;
	while (*prcs && ft_isdigit(*prcs))
	{
		step = (is_neg) ? ('0' - *prcs) : (*prcs - '0');
		if (is_neg && (ret < (-LONG_MAX_LIB - 1 - step) / 10))
			return (0);
		else if (!is_neg && (ret > (LONG_MAX_LIB - step) / 10))
			return (-1);
		else
			ret = ret * 10 + step;
		prcs++;
	}
	return ((int)ret);
}
