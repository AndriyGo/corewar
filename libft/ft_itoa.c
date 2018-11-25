/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 16:51:40 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		size;
	int		copy;
	int		is_neg;
	char	*ret;

	copy = n;
	is_neg = (n < 0);
	size = is_neg + (n == 0);
	while (copy != 0)
	{
		copy /= 10;
		size++;
	}
	if ((ret = (char *)ft_memalloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	ret[size] = '\0';
	while (size > is_neg)
	{
		ret[--size] = ((is_neg) ? (-1 * (n % 10)) : (n % 10)) + '0';
		n /= 10;
	}
	if (size == 1)
		ret[0] = '-';
	return (ret);
}
