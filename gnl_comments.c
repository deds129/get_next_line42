/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:26:02 by hanisha           #+#    #+#             */
/*   Updated: 2020/12/01 14:42:23 by hanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//метод для зануления всех байтов строки, типо чистка
void		ft_bzero(char *s)
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

//метод возвращающий \n в остатке(static переменная) меняющая его на \0
char		*remainer_check(char *remainer, char **line)
{
	//указатель на \n
	char				*p_nextline;

	p_nextline = NULL;

	//пока есть остаток(static)
	if (remainer)
		//ищем  остатке \n
		if ((p_nextline = (ft_strchr(remainer, '\n'))))
		{
			//заменяем на \0
			*p_nextline = '\0';

			//записываем в line до \0???
			*line = ft_strdup(remainer);

			//передвигаем указатель
			p_nextline++;

			//в остаток записываем новую строку начиная со след символа от \n т.е. в line добавили строку до \n и остальное после \n помещаем в остаток
			//места должно хватить т.к. remainer > p_nextline
			ft_strcpy(remainer, p_nextline);
		}
		//если /n  на найден (т.e. это строка была последней/содержит \0)
		else
		{
			//остаток идет в line т.е. остаток это и есть строка
			*line = ft_strdup(remainer);
			//зачищаем остаток ОЧЕНЬ СПОРНЫЙ МОМЕНТ
			ft_bzero(remainer);
		}
	//если же остатка нет то сощдаем пустой лайн СПОРНО тоже кажется
	else
		*line = ft_strdup("");
	return (p_nextline);
}

int			get_next_line(int fd, char **line)
{
	//буффер размерностью  BUFFER_SIZE + 1
	char				*buff;

	//количество прочитанных байт с помощью read
	int					read_byte;

	//статическая переменная для хранения остатка поле записи строки, для последующих вызовов функции
	static	char		*remainer;

	//указатель на новую строку (\n) (чтобы его заменить на \0 и с помощью strjoin загнать в line, остаток же идет в static переменную)
	char				*p_nextline;

	//временная переменная для корректной очистки line после записи
	char				*temp;

	//проверяем входные параметры на корректность => если ошибка возвращаем -1)
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);

	//выделяем память под заданный буффер ( можно было объявлять как массив и там уже все делать, но места в стеке может нехватит поэтому маллочим
	// если ошибка возвращаем -1)
	if (!(buff = (char *)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);

	//находим указалель на новую строку с помощью метода
	p_nextline = remainer_check(remainer, line);

	//пока 1)указатель на \n != NULL 2)считано байт != 0 ??
	while (!p_nextline && (read_byte = read(fd, buff, BUFFER_SIZE)))
	{
		//в конец буффера ставим обязательно \0
		buff[read_byte] = '\0';

		//если в буффере захвачен(найден) \n и его указатель не равен  NULL
		if ((p_nextline = (ft_strchr(buff, '\n'))))
		{
			// \n заменяем на \0
			*p_nextline = '\0';

			//передвигаем указалель направо от \n -> \0
			p_nextline++;

			//весь остаток перемещаем в static переменную
			remainer = ft_strdup(p_nextline);
		}

		//премещаем в временную переменую указатель на line т.к. при  *line = ft_strjoin(*line, buff); мы теряем ссылку на line => leak
		temp = *line;
		*line = ft_strjoin(*line, buff);
		free(temp);
	}
	//ПЛОХАЯ ОБРАБОТКА ВОЗВРАЩАЕМЫХ ЗНАЧЕНИЙ???
	if (read_byte || ft_strlen(*line) || ft_strlen(remainer))
		return (1);
	else
		return (0);
}


int			main(void)
{
	int i;
	int fd = open("test.txt", O_RDONLY);
	char *line;

	/*
	get_next_line(fd, &line);
	printf("%s\n",line);
	free(line);
	 */


	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf(" i = %d : Str: %s \n", i, line);
		free(line);
	}

	//контрольный тест
	i = get_next_line(fd, &line);
	printf(" i = %d : Str: %s \n", i, line);
	free(line);
	return (0);
}

