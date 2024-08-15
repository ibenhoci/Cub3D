/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:03:34 by smallem           #+#    #+#             */
/*   Updated: 2024/01/24 12:22:23 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rec_valid(char **map, t_cub *data, t_vec v, int flag)
{
	if (flag && (v.x < 0 || v.y < 0 || !map[v.x] || v.y
			>= (int)ft_strlen(map[v.x]) || !map[v.x][v.y]))
		ft_error("Error\nMap not closed properly", data, map, 1);
	if (v.x < 0 || v.y < 0 || !map[v.x] || v.y >= (int)ft_strlen(map[v.x])
		|| !map[v.x][v.y])
		return (0);
	if (map[v.x][v.y] == '1' || map[v.x][v.y] == 'V')
		return (0);
	if (map[v.x][v.y] == ' ')
		ft_error("Error\nMap not closed properly", data, map, 1);
	if (map[v.x][v.y] == '0' || is_pos(map[v.x][v.y]))
	{
		map[v.x][v.y] = 'V';
		rec_valid(map, data, (t_vec){v.x + 1, v.y}, 1);
		rec_valid(map, data, (t_vec){v.x, v.y + 1}, 1);
		rec_valid(map, data, (t_vec){v.x - 1, v.y}, 1);
		rec_valid(map, data, (t_vec){v.x, v.y - 1}, 1);
	}
	return (0);
}

void	check_map(t_cub *data, char *line, int ind)
{
	char	**cp;
	t_vec3	v;
	int		i;
	int		j;

	data->map = ft_split(line + ind, '\n');
	free(line);
	if (!data->map)
		ft_error("Error\nMalloc error", data, NULL, 1);
	i = -1;
	v = (t_vec3){0, 0, 0};
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (is_pos(data->map[i][j]))
				v = (t_vec3){i, j, ++v.z};
		}
	}
	if (v.z != 1)
		ft_error("Error\nInvalid starting position parameter", data, NULL, 1);
	cp = cp_map(data);
	rec_valid(cp, data, (t_vec){v.x, v.y}, 0);
	free_split(cp);
}

static void	valid_map_line(t_cub *data, char *line, int i, int last)
{
	while (i < last)
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != 'N' && line[i] != 'S')
			call_err(data, "Error\nInvalid characters in map", NULL, line);
		i++;
	}
}

static int	find_last(char *line, int i)
{
	int	last;

	last = i;
	while (line[last])
		last++;
	last--;
	while (last >= 0)
	{
		if (line[last] && line[last] != ' ' && line[last] != '\n')
			break ;
		last--;
	}
	return (last);
}

void	get_map(t_cub *data, char *line, int i)
{
	int	last;
	int	ind;

	if (!line[i])
		call_err(data, "Error\nMap not present", NULL, line);
	last = find_last(line, i);
	valid_map_line(data, line, i, last);
	ind = i;
	while (i < last)
	{
		if (line[i] == '\n')
		{
			i++;
			while (i < last && line[i] == ' ')
				i++;
			if (i < last && line[i] == '\n')
				call_err(data, "Error\nNewlines present in map", NULL, line);
		}
		i++;
	}
	check_map(data, line, ind);
}
