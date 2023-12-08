/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouyata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:43:23 by abouyata          #+#    #+#             */
/*   Updated: 2023/12/08 19:12:10 by abouyata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    ft_strdelete(char **s)
{
    if (s != NULL && *s != NULL)
    {
        free (*s);
        *s = NULL;
    }
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
	{
		return (s);
	}
	return (NULL);
}
static char	*ajouteligne(char **s, char **line)
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
	return (*line);
}

char *get_next_line(const int fd)
{
	int	ret;
	static char	*s[FD_SIZE];
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	char	*line;

	if (fd < 0)
		return (NULL);
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
	if (ret <= 0 && s[fd] == NULL)
		return (0);
	return (ajouteligne(&s[fd], &line));
}
