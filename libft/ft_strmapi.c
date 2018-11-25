/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:06:06 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	char			*tmp;
	unsigned int	idx;

	if (s == NULL)
		return (NULL);
	if ((ret = ft_strdup(s)) == NULL)
		return (NULL);
	tmp = ret;
	idx = 0;
	while (*tmp)
	{
		*tmp = f(idx++, *tmp);
		tmp++;
	}
	return (ret);
}
