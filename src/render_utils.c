/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:47:30 by smallem           #+#    #+#             */
/*   Updated: 2024/01/23 16:06:45 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_vec(char c, t_cub *data)
{
	int	sign;

	sign = 1;
	if (c == 'S' || c == 'E')
		sign *= -1;
	if (c == 'N' || c == 'S')
	{
		data->vecs[1] = (t_vec2){0.0, 1 * -sign};
		data->vecs[2] = (t_vec2){FOV * sign, 0.0};
	}
	else
	{
		data->vecs[1] = (t_vec2){-1.0 * sign, 0.0};
		data->vecs[2] = (t_vec2){0.0, FOV * -sign};
	}
}

void	get_data(t_cub *data)
{
	int		i;
	int		j;
	size_t	w;

	i = -1;
	w = 0;
	while (data->map[++i])
	{
		if (ft_strlen(data->map[i]) > w)
			w = ft_strlen(data->map[i]);
		j = -1;
		while (data->map[i][++j])
		{
			if (is_pos(data->map[i][j]))
			{
				data->vecs[0].x = (double)j + 0.5;
				data->vecs[0].y = (double)i + 0.5;
				set_vec(data->map[i][j], data);
				data->map[i][j] = '0';
			}
		}
	}
}

void	init(t_cub *data)
{
	get_data(data);
	data->win = NULL;
	data->win = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
	if (!data->win)
		ft_error("Error\nMlx_init failure!", data, NULL, 1);
	data->img = mlx_new_image(data->win, WIDTH, HEIGHT);
	if (!data->img)
		ft_error("Error\nCould not create image!", data, NULL, 1);
	if (mlx_image_to_window(data->win, data->img, 0, 0) == -1)
		ft_error("Error\nImg2Win mlx failure!", data, NULL, 1);
}

int	rotate_camera(t_vec2 *vecs, short dir)
{
	double	cos_a;
	double	sin_a;
	double	tmp;

	cos_a = cos(dir * ROT);
	sin_a = sin(dir * ROT);
	tmp = vecs[1].x;
	vecs[1].x = (vecs[1].x * cos_a) - (vecs[1].y * sin_a);
	vecs[1].y = (tmp * sin_a) + (vecs[1].y * cos_a);
	tmp = vecs[2].x;
	vecs[2].x = (vecs[2].x * cos_a) - (vecs[2].y * sin_a);
	vecs[2].y = (tmp * sin_a) + (vecs[2].y * cos_a);
	return (1);
}

int	movement(t_vec2 *vecs, char **map, int dir)
{
	t_vec2	v;
	t_vec2	p;

	p = (t_vec2){vecs[0].x, vecs[0].y};
	v = (t_vec2){vecs[1].x * MV, vecs[1].y * MV};
	if (dir == 1 && map[(int)(p.y + v.y)][(int)(p.x + v.x)] != '1')
		vecs[0] = (t_vec2){p.x + v.x, p.y + v.y};
	else if (dir == 2 && map[(int)(p.y - v.y)][(int)(p.x - v.x)] != '1')
		vecs[0] = (t_vec2){p.x - v.x, p.y - v.y};
	else if (dir == 3 && map[(int)(p.y - v.x)][(int)(p.x + v.y)] != '1')
		vecs[0] = (t_vec2){p.x + v.y, p.y - v.x};
	else if (dir == 4 && map[(int)(p.y + v.x)][(int)(p.x - v.y)] != '1')
		vecs[0] = (t_vec2){p.x - v.y, p.y + v.x};
	return (1);
}
