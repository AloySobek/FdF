/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:49:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/27 16:19:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_in_str(char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

t_mylist			*ft_create_lst(const int fd)
{
	t_mylist		*new_elem;

	if (!(new_elem = (t_mylist *)malloc(sizeof(t_mylist))))
		return (NULL);
	(*new_elem).inter_str = ft_strnew(0);
	(*new_elem).fd = fd;
	(*new_elem).next = NULL;
	return (new_elem);
}

char				**ft_find_and_or_add(t_mylist **lst, const int fd)
{
	t_mylist		*check;

	check = *lst;
	if (!check)
	{
		if (!(*lst = ft_create_lst(fd)))
			return (NULL);
		return (&(**lst).inter_str);
	}
	while ((*check).fd != fd && (*check).next)
		check = (*check).next;
	if ((*check).fd == fd)
		return (&(*check).inter_str);
	if (!((*check).next = ft_create_lst(fd)))
		return (NULL);
	check = (*check).next;
	return (&(*check).inter_str);
}

void				ft_swapjoin(char **tmp, char **inter_str, char **buf)
{
	*tmp = ft_strjoin(*inter_str, *buf);
	free(*inter_str);
	*inter_str = *tmp;
}

int					get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_mylist	*fd_list = NULL;
	char			**inter_str;
	int				status;
	char			*tmp;

	if ((buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) &&
		(inter_str = ft_find_and_or_add(&fd_list, fd)) && line)
		while ((status = read(fd, buf, BUFF_SIZE)) >= 0)
		{
			buf[status] = '\0';
			ft_swapjoin(&tmp, &(*inter_str), &buf);
			if (ft_in_str(*inter_str, '\n') == 0 && status != 0)
				continue;
			free(buf);
			*line = ft_strcut(*inter_str, '\n');
			if (status == 0 && !**inter_str && !**line)
				return (0);
			tmp = ft_strcrop(*inter_str, '\n');
			free(*inter_str);
			*inter_str = tmp;
			return (1);
		}
	free(buf);
	return (-1);
}
