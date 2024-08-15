/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:05:06 by smallem           #+#    #+#             */
/*   Updated: 2024/01/16 17:09:27 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_info(t_cub *data, t_ray *ray, short x, t_vec2 *dist)
{
	double	cam_x;

	cam_x = (2.0 * (double)x / (double)data->img->width - 1.0);
	ray->dir = (t_vec2){data->vecs[1].x + (data->vecs[2].x * cam_x),
		data->vecs[1].y + (data->vecs[2].y * cam_x)};
	if (ray->dir.x)
		dist->x = fabs(1.0 / ray->dir.x);
	else
		dist->x = INFINITY;
	if (ray->dir.y)
		dist->y = fabs(1.0 / ray->dir.y);
	else
		dist->y = INFINITY;
	ray->pos = (t_vec){data->vecs[0].x, data->vecs[0].y};
}

void	fix_ray(t_vec2 *v, t_ray *ray, t_vec2 *vecs, t_vec *vec)
{
	if (ray->dir.x < 0)
	{
		vec[0].x = -1;
		vecs[1].x = (v[0].x - (double)ray->pos.x) * vecs[0].x;
		vec[1].x = 3;
	}
	else
	{
		vec[0].x = 1;
		vecs[1].x = ((double)ray->pos.x + 1.0 - v[0].x) * vecs[0].x;
		vec[1].x = 2;
	}
	if (ray->dir.y < 0)
	{
		vec[0].y = -1;
		vecs[1].y = (v[0].y - (double)ray->pos.y) * vecs[0].y;
		vec[1].y = 0;
	}
	else
	{
		vec[0].y = 1;
		vecs[1].y = ((double)ray->pos.y + 1.0 - v[0].y) * vecs[0].y;
		vec[1].y = 1;
	}
}

void	launch_ray(char **map, t_ray *ray, t_vec2 *vecs, t_vec vec)
{
	int	*x;
	int	*y;

	x = &ray->pos.x;
	y = &ray->pos.y;
	while (1)
	{
		if (vecs[1].x < vecs[1].y)
		{
			vecs[1].x += vecs[0].x;
			ray->pos.x += vec.x;
			ray->axis = 'X';
		}
		else
		{
			vecs[1].y += vecs[0].y;
			ray->pos.y += vec.y;
			ray->axis = 'Y';
		}
		if (map[*y][*x] == '1')
			break ;
	}
}

static void	get_tex_info(t_vec2 *v, t_vec *ve, t_ray *ray, t_cub *data)
{
	int				l_h;
	double			wx;
	uint32_t		h;
	char			c;
	mlx_texture_t	*tex;

	tex = data->tex[ray->hit];
	h = data->img->height;
	l_h = (h) / (ray->distance);
	c = ray->axis;
	ve[0] = (t_vec){((int)h / 2) - (l_h / 2), ((int)h / 2) + (l_h / 2)};
	if (ve[0].x < 0)
		ve[0].x = 0;
	if (ve[0].y >= (int)h)
		ve[0].y = h - 1;
	if (c == 'X')
		wx = data->vecs[0].y + (ray->distance * ray->dir.y);
	else
		wx = data->vecs[0].x + (ray->distance * ray->dir.x);
	wx -= floor(wx);
	ve[1].x = (int)(wx * (double)tex->width);
	if ((c == 'X' && ray->dir.x > 0) || (c == 'Y' && ray->dir.y < 0))
		ve[1].x = tex->width - ve[1].x - 1;
	v->y = (double)(tex->height) / l_h;
	v->x = (ve[0].x - (h / 2) + (l_h / 2)) * v->y;
}

void	render_walls(t_ray *ray, short x, t_cub *data)
{
	t_vec			ve[2];
	t_vec2			v;
	int32_t			pxl;
	mlx_texture_t	*tex;

	get_tex_info(&v, ve, ray, data);
	tex = data->tex[ray->hit];
	while (ve[0].x < ve[0].y)
	{
		ve[1].y = v.x;
		pxl = (ve[1].y * tex->width + ve[1].x) * 4;
		mlx_put_pixel(data->img, x, ve[0].x, col(tex->pixels[pxl],
				tex->pixels[pxl + 1], tex->pixels[pxl + 2]));
		v.x += v.y;
		ve[0].x++;
	}
}
