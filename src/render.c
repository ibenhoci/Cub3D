/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:53:55 by smallem           #+#    #+#             */
/*   Updated: 2024/01/23 16:09:08 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	raycast(t_cub *data, t_ray *ray)
{
	short	x;
	short	w;
	t_vec	vec[2];
	t_vec2	vecs[2];

	x = -1;
	w = (short)data->img->width;
	while (++x < w)
	{
		get_info(data, ray, x, vecs);
		fix_ray(data->vecs, ray, vecs, vec);
		launch_ray(data->map, ray, vecs, vec[0]);
		if (ray->axis == 'X')
		{
			ray->distance = vecs[1].x - vecs[0].x;
			ray->hit = vec[1].x;
		}
		else
		{
			ray->distance = vecs[1].y - vecs[0].y;
			ray->hit = vec[1].y;
		}
		render_walls(ray, x, data);
	}
}

void	paint(mlx_image_t *img, t_vec3 *cols)
{
	unsigned short	x;
	unsigned short	y;
	short			h;
	short			w;
	int32_t			co[2];

	co[0] = col(cols[0].x, cols[0].y, cols[0].z);
	co[1] = col(cols[1].x, cols[1].y, cols[1].z);
	w = (short)img->width;
	h = (short)img->height;
	x = -1;
	while (++x < w)
	{
		y = 0;
		while (y < h / 2)
			mlx_put_pixel(img, x, y++, co[1]);
		while (y < h - 1)
			mlx_put_pixel(img, x, y++, co[0]);
	}
}

void	events(void *param)
{
	t_cub	*data;
	t_ray	ray;
	int		f;

	data = param;
	f = 0;
	if (mlx_is_key_down(data->win, MLX_KEY_ESCAPE))
		mlx_close_window(data->win);
	if (mlx_is_key_down(data->win, MLX_KEY_RIGHT))
		f = rotate_camera(data->vecs, 1);
	if (mlx_is_key_down(data->win, MLX_KEY_LEFT))
		f = rotate_camera(data->vecs, -1);
	if (mlx_is_key_down(data->win, MLX_KEY_W))
		f = movement(data->vecs, data->map, 1);
	if (mlx_is_key_down(data->win, MLX_KEY_S))
		f = movement(data->vecs, data->map, 2);
	if (mlx_is_key_down(data->win, MLX_KEY_A))
		f = movement(data->vecs, data->map, 3);
	if (mlx_is_key_down(data->win, MLX_KEY_D))
		f = movement(data->vecs, data->map, 4);
	if (f)
	{
		paint(data->img, data->cols);
		raycast(data, &ray);
	}
}

int32_t	col(int32_t r, int32_t g, int32_t b)
{
	return (r << 24 | g << 16 | b << 8 | 0x000000FF);
}
