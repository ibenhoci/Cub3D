/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:54:23 by smallem           #+#    #+#             */
/*   Updated: 2024/01/24 12:24:04 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_number(char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] < '0' || val[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static t_vec3	get_col_vec(t_cub *data, char *str, char *line)
{
	t_vec3	vec;
	char	**mat;
	char	*val;
	int		i;

	mat = ft_split(str, ',');
	if (!mat)
		call_err(data, "Error\nMalloc error", NULL, line);
	if (!mat[0] || !mat[1] || !mat[2] || mat[3])
		call_err(data, "Error\nInvalid rgb format", mat, line);
	i = -1;
	while (++i < 3)
	{
		val = ft_strtrim(mat[i], " \n");
		if (!val)
			call_err(data, "Error\nMalloc error", mat, line);
		free(mat[i]);
		mat[i] = val;
		if (!is_valid_number(mat[i]))
			call_err(data, "Error\nInvalid rgb format", mat, line);
	}
	vec = (t_vec3){ft_atoi(mat[0]), ft_atoi(mat[1]), ft_atoi(mat[2])};
	free_split(mat);
	return (vec);
}

void	get_rgb(char *name, char *str, t_cub *data, char *line)
{
	t_vec3	v;

	v = get_col_vec(data, str, line);
	if (v.x > 255 || v.x < 0 || v.y > 255 || v.y < 0 || v.z > 255 || v.z < 0)
		call_err(data, "Error\nInvalid rgb format", NULL, line);
	if (!ft_strncmp(name, "F", 2))
	{
		if (data->cols[0].x == 256 && data->cols[0].y == 256
			&& data->cols[0].z == 256)
			data->cols[0] = v;
		else
			call_err(data, "Error\nMultiple initializations", NULL, line);
	}
	else
	{
		if (data->cols[1].x == 256 && data->cols[1].y == 256
			&& data->cols[1].z == 256)
			data->cols[1] = v;
		else
			call_err(data, "Error\nMultiple initializations", NULL, line);
	}
}

void	get_path(char *name, char *str, t_cub *data, char *line)
{
	char			*path;
	mlx_texture_t	*tex;

	path = ft_strtrim(str, " \n");
	if (!path)
		call_err(data, "Error\nMalloc error", NULL, line);
	tex = mlx_load_png(path);
	free(path);
	if (!tex)
		call_err(data, "Error\nMlx_load_png failure", NULL, line);
	if (!ft_strncmp(name, "EA", 3) && !data->tex[3])
		data->tex[3] = tex;
	else if (!ft_strncmp(name, "WE", 3) && !data->tex[2])
		data->tex[2] = tex;
	else if (!ft_strncmp(name, "NO", 3) && !data->tex[0])
		data->tex[0] = tex;
	else if (!ft_strncmp(name, "SO", 3) && !data->tex[1])
		data->tex[1] = tex;
	else
		call_err(data, "Error\nMultiple initializations", NULL, line);
}

void	get_config(t_cub *data, char *str, char *line)
{
	int	flag;
	int	i;
	int	size;
	int	count;

	i = 0;
	flag = (!ft_strncmp(str, "C ", 2) || !ft_strncmp(str, "F ", 2));
	while (str[i] && str[i] != ' ')
		i++;
	str[i++] = '\0';
	if (flag)
	{
		size = i;
		count = 0;
		while (str[size])
			if (str[size++] == ',')
				count++;
		if (count != 2)
			call_err(data, "Error\nInvalid rgb format", NULL, line);
	}
	if (flag)
		get_rgb(str, str + i, data, line);
	else
		get_path(str, str + i, data, line);
}
