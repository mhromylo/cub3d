/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:48 by mhromylo          #+#    #+#             */
/*   Updated: 2024/06/26 17:24:17 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_left(t_game *game, double old_direction_x, double old_plane_x)
{
	game->raycast->dir_x = game->raycast->dir_x * cos(ROTATION_SPEED)
		- game->raycast->dir_y * sin(ROTATION_SPEED);
	game->raycast->dir_y = old_direction_x * sin(ROTATION_SPEED)
		+ game->raycast->dir_y * cos(ROTATION_SPEED);
	game->raycast->view_x = game->raycast->view_x * cos(ROTATION_SPEED)
		- game->raycast->view_y * sin(ROTATION_SPEED);
	game->raycast->view_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->raycast->view_y * cos(ROTATION_SPEED);
}

void	rotate_right(t_game *game, double old_direction_x, double old_plane_x)
{
	game->raycast->dir_x = game->raycast->dir_x * cos(-ROTATION_SPEED)
		- game->raycast->dir_y * sin(-ROTATION_SPEED);
	game->raycast->dir_y = old_direction_x * sin(-ROTATION_SPEED)
		+ game->raycast->dir_y * cos(-ROTATION_SPEED);
	game->raycast->view_x = game->raycast->view_x * cos(-ROTATION_SPEED)
		- game->raycast->view_y * sin(-ROTATION_SPEED);
	game->raycast->view_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->raycast->view_y * cos(-ROTATION_SPEED);
}