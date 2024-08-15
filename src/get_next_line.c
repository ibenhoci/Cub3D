/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:39:16 by smallem           #+#    #+#             */
/*   Updated: 2023/12/12 16:42:08 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_get_buffer(char *str)
{
	char	*buffer;
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	buffer = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	free(str);
	str = NULL;
	return (buffer);
}

char	*free_all(char *str, char *buffer)
{
	free(buffer);
	buffer = NULL;
	free(str);
	str = NULL;
	return (NULL);
}

char	*ft_read(char *str, int fd, ssize_t bytes_read)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(str, buffer));
		buffer[bytes_read] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read == 0 && str[0] == 0)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		*line;
	ssize_t		bytes_read;
	int			i;

	if (!str)
		str = ft_calloc(1, 1);
	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_read(str, fd, bytes_read);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i + 1);
	tmp = str;
	str = ft_get_buffer(tmp);
	return (line);
}
