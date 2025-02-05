/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:18:57 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/05 16:48:25 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	keys_execute(t_game *game)
{
	double	old_plane_x;
	double	old_direction_x;

	old_direction_x = game->raycast->dir_x;
	old_plane_x = game->raycast->view_x;
	if (game->key_esc)
		close_after_mlx(game);
	if (game->key_w)
		front_move(game);
	if (game->key_s)
		back_move(game);
	if (game->key_a)
		left_move(game);
	if (game->key_d)
		right_move(game);
	if (game->key_left)
		rotate_left(game, old_direction_x, old_plane_x);
	if (game->key_right)
		rotate_right(game, old_direction_x, old_plane_x);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		game->key_esc = 1;
	if (key == KEY_S)
		game->key_s = 1;
	if (key == KEY_W)
		game->key_w = 1;
	if (key == KEY_A)
		game->key_a = 1;
	if (key == KEY_D)
		game->key_d = 1;
	if (key == KEY_LEFT && game->key_right == 0)
		game->key_left = 1;
	if (key == KEY_RIGHT && game->key_left == 0)
		game->key_right = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		game->key_esc = 0;
	if (key == KEY_S)
		game->key_s = 0;
	if (key == KEY_W)
		game->key_w = 0;
	if (key == KEY_A)
		game->key_a = 0;
	if (key == KEY_D)
		game->key_d = 0;
	if (key == KEY_LEFT)
		game->key_left = 0;
	if (key == KEY_RIGHT)
		game->key_right = 0;
	return (0);
}