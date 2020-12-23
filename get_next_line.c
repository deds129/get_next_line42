/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:26:02 by hanisha           #+#    #+#             */
/*   Updated: 2020/12/23 15:10:01 by hanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				ft_bzero(char *s)
{
	size_t				i;

	i = 0;
	if (s != NULL)
		while (s[i])
		{
			((char *)s)[i] = 0;
			i++;
		}
}

void				n_line(char **p_n, char **rem, char **buff, char ***line)
{
	char		*tmp;

	if ((*p_n = (ft_strchr(*buff, '\n'))))
	{
		*(*p_n) = '\0';
		tmp = *rem;
		*rem = ft_strdup(++(*p_n));
		free(tmp);
	}
	**line = ft_strjoin(**line, *buff);
}

char				*remainer_check(char *remainer, char **line)
{
	char	*p_nextline;

	p_nextline = NULL;
	if (remainer)
		if ((p_nextline = ft_strchr(remainer, '\n')))
		{
			*p_nextline = '\0';
			*line = ft_strdup(remainer);
			p_nextline++;
			ft_strcpy(remainer, p_nextline);
		}
		else
		{
			*line = ft_strdup(remainer);
			ft_bzero(remainer);
		}
	else
		*line = ft_strdup("");
	return (p_nextline);
}

int					get_next_line(int fd, char **line)
{
	char		*buff;
	int			read_byte;
	static char	*remainer;
	char		*p_nextline;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!(buff = (char *)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
	{
		free(buff);
		return (-1);
	}
	p_nextline = remainer_check(remainer, line);
	while (!p_nextline && (read_byte = read(fd, buff, BUFFER_SIZE)))
	{
		if (read_byte == -1)
		{
			free(buff);
			return (-1);
		}
		buff[read_byte] = '\0';
		n_line(&p_nextline, &remainer, &buff, &line);
	}
	free(buff);
	return ((read_byte || p_nextline || ft_strlen(remainer)) ? 1 : 0);
}
