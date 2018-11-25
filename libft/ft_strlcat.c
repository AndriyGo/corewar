/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:06:17 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ret;

	ret = 0;
	while (*dst && (size > 0))
	{
		dst++;
		ret++;
		size--;
	}
	while (*src && (size > 1))
	{
		*(dst++) = *(src++);
		ret++;
		size--;
	}
	while (*(src++))
		ret++;
	if (size > 0)
		*dst = '\0';
	return (ret);
}
