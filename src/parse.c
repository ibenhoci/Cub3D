/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:26 by smallem           #+#    #+#             */
/*   Updated: 2024/01/23 16:11:57 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_2(t_cub *data, char *str, int i)
{
	int	tmp;

	tmp = i;
	while (str[tmp] && (str[tmp] == ' ' || str[tmp] == '\n'))
	{
		if (str[tmp] == '\n')
			i = tmp;
		tmp++;
	}
	get_map(data, str, i);
}

void	parse(t_cub *data, char *str)
{
	char	*ptr[6];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && j < 6)
	{
		if (!ft_strncmp(str + i, "EA ", 3) || !ft_strncmp(str + i, "WE ", 3)
			|| !ft_strncmp(str + i, "SO ", 3) || !ft_strncmp(str + i, "NO ", 3)
			|| !ft_strncmp(str + i, "C ", 2) || !ft_strncmp(str + i, "F ", 2))
		{
			ptr[j++] = str + i;
			while (str[i] && str[i] != '\n')
				i++;
			str[i] = '\0';
		}
		else if (str[i] != ' ' && str[i] != '\n')
			call_err(data, "Error\nInvalid config data", NULL, str);
		i++;
	}
	while (j > 0)
		get_config(data, ptr[--j], str);
	parse_2(data, str, i);
}

static void	set_initial_data(t_cub *data)
{
	int	i;

	data->img = NULL;
	data->win = NULL;
	data->map = NULL;
	i = -1;
	while (++i < 4)
		data->tex[i] = NULL;
	data->cols[0] = (t_vec3){256, 256, 256};
	data->cols[1] = (t_vec3){256, 256, 256};
}

char	*read_stuff(int fd)
{
	char	*line;
	char	*tmp;
	char	*t;

	line = ft_strdup("");
	if (!line)
	{
		close(fd);
		ft_error("Error\nMalloc error!", NULL, NULL, 0);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		t = line;
		line = ft_strjoin(t, tmp);
		free(tmp);
		free(t);
	}
	close(fd);
	return (line);
}

void	read_content(t_cub *data, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	i = ft_strlen(argv[1]);
	if (i < 4)
		ft_error("Error\nBad file name", NULL, NULL, 0);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4))
		ft_error("Error\nBad file format", NULL, NULL, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCould not open file!", NULL, NULL, 0);
	line = read_stuff(fd);
	set_initial_data(data);
	parse(data, line);
}
