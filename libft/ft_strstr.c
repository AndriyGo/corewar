/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:05:25 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	len;
	size_t	big_len;

	len = ft_strlen(little);
	if (len == 0)
		return ((char *)big);
	big_len = ft_strlen(big);
	while (big_len-- >= len)
	{
		if (ft_strncmp(big, little, len) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
