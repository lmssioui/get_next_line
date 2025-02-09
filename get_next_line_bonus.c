/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouyata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:15:47 by abouyata          #+#    #+#             */
/*   Updated: 2023/12/22 18:16:48 by abouyata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*after_ln(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	s = malloc(ft_strlen(str) - i + 1);
	if (!s)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i] != '\0')
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

static char	*line(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i])
		i++;
	s = (char *)malloc(i + 1);
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		s[j++] = str[i++];
	if (str[i] == '\n')
	{
		s[j] = '\n';
		j++;
	}
	s[j] = '\0';
	return (s);
}

static char	*new_line(int fd, char *str)
{
	ssize_t	ret;
	char	*buff;

	ret = 1;
	buff = (char *)malloc((size_t) BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		else if (ret == 0)
			break ;
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*s;
	static char	*str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = new_line(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	s = line(str[fd]);
	str[fd] = after_ln(str[fd]);
	return (s);
}
