/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:49:16 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/05 16:48:15 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player(t_game *game, int x, int y)
{
	game->direction = game->map[y][x];
	game->player_index++;
	game->player_pos_x = x + 0.5;
	game->player_pos_y = y + 0.5;
}

void	ceiling_floor(t_game *game)

{
	unsigned int	*dst;
	int				i;

	dst = (unsigned int *)game->img.addr;
	i = S_W * S_H / 2 + 1;
	while (--i > 0)
		*dst++ = game->ceiling_bit;
	i = S_W * S_H / 2 + 1;
	while (--i > 0)
		*dst++ = game->floor_bit;
}

int	draw_world(t_game *game)

{
	ceiling_floor(game);
	raycast(game, game->raycast);
	keys_execute(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	close_after_mlx(t_game *game)
{	
	int	i;
	
	i = 0;
	if (game->wall->img->img)
	{	
		while (i <= 3)
		{
			mlx_destroy_image(game->mlx, game->wall[i].img->img);
			free(game->wall[i++].img);
			
		}
		game->wall->img = NULL;
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (close_game(game));
}