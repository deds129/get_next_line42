/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:26:02 by hanisha           #+#    #+#             */
/*   Updated: 2020/11/24 16:26:21 by hanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "get_next_line.h"
//cc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c



//метод очищающий строку переводящий все байты в строки в ноль без аллокации
// памяти
void	ft_bzero(void *s)
{
	size_t i;

	i = 0;
	while (*s && s)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
char *reminer_check(char *remainder, **line)
{
char *p_nextline;

p_nextline = NULL;
if (remainder)
if ((p_nextline = (ft_strchr(remainder,'\n'))))
{
*p_nextline = '\0';
*line = ft_strdup(remainder);
p_nextline++;
ft_strcpy(remainder); // нужно подобрать новый метод, не совсем
// подходит
}
else
{
*line = ft_strdup(remainder);
b_zero(remainder); // нужно ли испольщовать??

}
}
else
*line = ft_strdup("");
return (p_nextline);
}

int get_next_line(int fd, char **line)
{
	//буффер для хранения части строки(проверить на '\0'!
	char				*buff;
	//для хранения результата чтения файла (read)
	int					read_byte;
	//статическая переменная под остаток (после \0) буффера, чтобы продолжать
	// чтение, чтобы не перепрыгивать через остаток буффера
	static char 		*remainder;
	//переменная указывающая на \n в буффере строки
	char *p_nextline;

	p_nextline = remainer_check(remainder,line);
	//защита от неправильных значений fd, line и BUFFER_SIZE = 5
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	//выделить память маллоком под строку
	if(!(buff = (char *)(malloc(sizeof(char) * BUFFER_SIZE +1)) ))
		return (-1);

	/*
	//для того чтобы в line не было мусора изначально
	if (remainder)
		*line = ft_strdup(remainder);
	else
		*line = ft_strdup("");
	 */

	reminder_check(remainder,line);
	//читаем строки и записываем все в одну строку
	while (!p_nextline && (read_byte = read(fd,buff,BUFFER_SIZE)))
	{
		buff[read_byte] = '\0';
		//проверка буффера на \n
		if((p_nextline = (ft_strchr(buff,'\n'))))
		{
			*p_nextline = '\0';
			flag = 0;
			//записываем прочитанный, но не записанный остаток буффера в стат
			// .переменную
			p_nextline++;

			//проблемы с размером буффера
			remainder = ft_strdup(p_nextline);
			//return (1);
		}
		*line = ft_strjoin(*line,buff);
	}
	return (0);
}

int main(void)
{
	int fd = open("text.txt",O_RDONLY);
	char *line;
	//int i;
	/*
	while ((i = get_next_line(fd, &line)))
	{
		printf("i = %d %s\n",i,line);
		free(line);
	}
	 */
	get_next_line(fd, &line);
	printf("%s\n",line);

	get_next_line(fd, &line);
	printf("Next line : %s\n",line);

	free(line);
	return (0);
}

