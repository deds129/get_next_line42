/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:27:05 by hanisha           #+#    #+#             */
/*   Updated: 2020/11/24 16:27:09 by hanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*newstr;
	size_t				s1_len;
	size_t				s2_len;
	size_t				i;
	size_t				j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char *) * (s1_len + s2_len + 1));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstr[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*ft_strdup(const char *str)
{
	char		*s;
	int			i;

	s = NULL;
	i = 0;
	while (str[i] != '\0')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (s == NULL)
		return (NULL);
	s[i] = '\0';
	while (i >= 0)
	{
		s[i] = str[i];
		i--;
	}
	return (s);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}



char	*ft_strchr(const char *str, int c)
{
	int			i;

	i = 0;
	if ((char)c == '\0')
	{
		while (str[i])
		{
			i++;
		}
		return ((char *)str + i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
