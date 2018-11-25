/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:27:06 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:28:19 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int *ret;
	int *point;

	if (max <= min)
		return (0);
	if ((ret = (int *)ft_memalloc((max - min) * sizeof(int))) == 0)
		return (0);
	point = ret;
	while (min < max)
		*(ret++) = min++;
	return (point);
}
