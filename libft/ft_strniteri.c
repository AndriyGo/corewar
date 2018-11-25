/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strniteri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:05:42 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_strniteri(char *s, void (*f)(unsigned int, char *), size_t n)
{
	unsigned int	i;

	i = 0;
	if ((s == NULL) || (f == NULL))
		return ;
	while (*s && (n-- > 0))
		f(i++, s++);
}
