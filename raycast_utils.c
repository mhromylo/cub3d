/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:57:57 by mhromylo          #+#    #+#             */
/*   Updated: 2024/06/27 17:50:45 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	walltype_detection(t_raycast *rc)

{
	if (rc->side == 0)
	{
		if (rc->raydir_x <= 0)
			rc->wall_type = 1;
		else
			rc->wall_type = 0;
	}
	else
	{
		if (rc->raydir_y >= 0)
			rc->wall_type = 3;
		else
			rc->wall_type = 2;
	}
}

void	texture_assign(t_game *game, t_raycast *rc)
{
	double	wall_hit;

	if (rc->side == 0)
		wall_hit = game->player_pos_y + rc->wall_dist * rc->raydir_y;
	else
		wall_hit = game->player_pos_x + rc->wall_dist * rc->raydir_x;
	wall_hit -= floor(wall_hit);
	rc->texture_x = (int)(wall_hit * (double)(game->wall[rc->wall_type].width));
	rc->texture_step = 1.0 * game->wall[rc->wall_type].height / rc->line_h;
	rc->texture_pos = (rc->draw_start - S_H / 2
			+ rc->line_h / 2) * rc->texture_step;
}

void	put_pixel(t_imag *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_imag *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_walls(t_game *game, t_raycast *rc, int x, int y)

{
	rc->texture_pos += rc->texture_step;
	rc->texture_y = (int)rc->texture_pos
		& (game->wall[rc->wall_type].height - 1);
	rc->color = get_pixel(game->wall[rc->wall_type].img,
			rc->texture_x, rc->texture_y);
	put_pixel(&game->img, x, y, rc->color);
}
