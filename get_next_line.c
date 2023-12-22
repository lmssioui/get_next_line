/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouyata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:05:31 by abouyata          #+#    #+#             */
/*   Updated: 2023/12/22 10:54:22 by abouyata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*after_ln(char *str)
{
	char *s;
	int	i;
	int	j;

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

char	*line(char *str)
{
	char *s;
	int	i;
	int	j;

	i = 0;
	if (!str[0])
		return (NULL);
	while(str[i] != '\n' && str[i] != '\0')
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

char	*new_line(int fd, char *str)
{
	ssize_t ret;
	char 	*buff;

	ret = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			free(str);
			return(NULL);
		}
		else if (ret == 0)
			break ;
		buff[ret] = '\0';
		str = ft_strjoin(str,buff);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char	*s;
	static char  *str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	str = new_line(fd, str);
	if (str == NULL)
		return (NULL);
	s = line(str);
	str = after_ln(str);
	return (s);
}
