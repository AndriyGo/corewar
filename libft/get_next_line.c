/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:17:25 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/29 17:00:37 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	delete_list_el(t_list **head, size_t fd)
{
	t_list **to_del;
	t_list *prev;

	if (head == NULL)
		return ;
	to_del = head;
	prev = NULL;
	while (*to_del != NULL)
	{
		if ((*to_del)->content_size == fd)
		{
			free((*to_del)->content);
			if (prev != NULL)
				prev->next = (*to_del)->next;
			free(*to_del);
			*to_del = NULL;
			return ;
		}
		prev = *to_del;
		to_del = &((*to_del)->next);
	}
}

t_list	*reader_for_fd(int fd, t_list **fd_list)
{
	t_list		*el;

	el = *fd_list;
	while (el)
	{
		if ((int)(el->content_size) == fd)
			return (el);
		el = el->next;
	}
	if ((el = ft_lstnew(NULL, 1)) == NULL)
		return (NULL);
	el->content = ft_strnew(1);
	el->content_size = fd;
	if (*fd_list == NULL)
		*fd_list = el;
	else
		ft_lstappend(*fd_list, el);
	return (el);
}

int		set_line_and_return(t_list **head, t_list *cur_read, char **line)
{
	char	*temp;

	if ((temp = ft_strchr((char *)(cur_read->content), '\n')) == NULL)
	{
		*line = ft_strdup((char *)(cur_read->content));
		delete_list_el(head, cur_read->content_size);
		head = head + 1;
		return (1);
	}
	*line = ft_strnew(ft_strlen(cur_read->content) - ft_strlen(temp));
	ft_strncpy(*line, cur_read->content, ft_strlen(cur_read->content) - \
		ft_strlen(temp));
	temp = ft_strdup(temp + 1);
	free(cur_read->content);
	cur_read->content = temp;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static	t_list	*fd_list;
	t_list			*cur_read;
	char			buf[BUFF_SIZE + 1];
	char			*temp;
	int				len;

	if ((line == NULL) || (fd < 0))
		return (-1);
	if ((cur_read = reader_for_fd(fd, &fd_list)) == NULL)
		return (-1);
	if ((temp = ft_strchr((char *)(cur_read->content), '\n')) != NULL)
		return (set_line_and_return(&fd_list, cur_read, line));
	while ((len = read(fd, buf, BUFF_SIZE)))
	{
		buf[len] = '\0';
		temp = ft_strjoin((char *)(cur_read->content), buf);
		free(cur_read->content);
		cur_read->content = temp;
		if ((temp = ft_strchr((char *)(cur_read->content), '\n')) != NULL)
			break ;
	}
	if (ft_strlen(cur_read->content) == 0)
		return (0);
	return (set_line_and_return(&fd_list, cur_read, line));
}
