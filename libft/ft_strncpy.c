/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:05:56 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *ret;

	ret = dst;
	while (*src && (len > 0))
	{
		*(dst++) = *(src++);
		--len;
	}
	while (len > 0)
	{
		*(dst++) = '\0';
		--len;
	}
	return (ret);
}
