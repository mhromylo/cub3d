/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:03 by mhromylo          #+#    #+#             */
/*   Updated: 2024/06/26 17:21:58 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	front_move(t_game *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(game->player_pos_x
			+ game->raycast->dir_x * (PLAYER_SPEED * 2));
	delta_y = (int)(game->player_pos_y
			+ game->raycast->dir_y * (PLAYER_SPEED * 2));
	if (game->map[(int)game->player_pos_y][delta_x] != '1')
		game->player_pos_x += game->raycast->dir_x * PLAYER_SPEED;
	if (game->map[delta_y][(int)game->player_pos_x] != '1')
		game->player_pos_y += game->raycast->dir_y * PLAYER_SPEED;
}

void	back_move(t_game *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(game->player_pos_x
			- game->raycast->dir_x * (PLAYER_SPEED * 2));
	delta_y = (int)(game->player_pos_y
			- game->raycast->dir_y * (PLAYER_SPEED * 2));
	if (game->map[(int)game->player_pos_y][delta_x] != '1')
		game->player_pos_x -= game->raycast->dir_x * PLAYER_SPEED;
	if (game->map[delta_y][(int)game->player_pos_x] != '1')
		game->player_pos_y -= game->raycast->dir_y * PLAYER_SPEED;
}

void	left_move(t_game *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(game->player_pos_x
			- game->raycast->dir_y * (PLAYER_SPEED * 2));
	delta_y = (int)(game->player_pos_y
			+ game->raycast->dir_x * (PLAYER_SPEED * 2));
	if (game->map[(int)game->player_pos_y][delta_x] != '1')
		game->player_pos_x -= game->raycast->dir_y * PLAYER_SPEED;
	if (game->map[delta_y][(int)game->player_pos_x] != '1')
		game->player_pos_y += game->raycast->dir_x * PLAYER_SPEED;
}

void	right_move(t_game *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(game->player_pos_x
			+ game->raycast->dir_y * (PLAYER_SPEED * 2));
	delta_y = (int)(game->player_pos_y
			- game->raycast->dir_x * (PLAYER_SPEED * 2));
	if (game->map[(int)game->player_pos_y][delta_x] != '1')
		game->player_pos_x += game->raycast->dir_y * PLAYER_SPEED;
	if (game->map[delta_y][(int)game->player_pos_x] != '1')
		game->player_pos_y -= game->raycast->dir_x * PLAYER_SPEED;
}