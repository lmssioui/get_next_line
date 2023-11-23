/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouyata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:43:23 by abouyata          #+#    #+#             */
/*   Updated: 2023/11/23 14:10:16 by abouyata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ajouteligne(char **s, char **line)
{
	int	len;
	char *tmp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		tmp = ft_strdup(&((*s)[len + 1]));
		if ((*s)[len + 1] == '\0')
			ft_strdelete(s);
		else 
		{
			free(*s);
			*s = tmp;
		}
	}
	else
	{
		*line = ft_strdup(*s);
		ft_strdelete(s);
	}
	return (1);
}

static int	output(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (ajouteligne(&s[fd], line));
}

int	get_next_line(const int fd, char **line)
{
	int	ret;
	static char	*s[FD_SIZE];
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (output(s, line, ret, fd));
}
int main()
{
	int fd;

	char *line;

	fd = open("exemple.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n",line);
	get_next_line(fd, &line);
	printf("%s\n",line);
	get_next_line(fd, &line);
	printf("%s\n",line);
	get_next_line(fd, &line);
	printf("%s\n",line);

}
