/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:40:39 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/04 17:15:52 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	error_elemens(t_game *game)
{
	if (game->s_index.ceiling > 1 || game->s_index.floor > 1
		|| game->s_index.north > 1 || game->s_index.south > 1
		|| game->s_index.east > 1 || game->s_index.west > 1)
	{
		printf("Error: Duplicating map elements\n");
		close_game(game);
	}
}

void	chek_elements(t_game *game, int i)
{
	if (!ft_strncmp(game->map_data[i], "C", 1))
		game->s_index.ceiling++;
	if (!ft_strncmp(game->map_data[i], "F", 1))
		game->s_index.floor++;
	if (!ft_strncmp(game->map_data[i], "NO", 2))
		game->s_index.north++;
	if (!ft_strncmp(game->map_data[i], "SO", 2))
		game->s_index.south++;
	if (!ft_strncmp(game->map_data[i], "EA", 2))
		game->s_index.east++;
	if (!ft_strncmp(game->map_data[i], "WE", 2))
		game->s_index.west++;
	error_elemens(game);
}

void	last_element(t_game *game)
{
	int	i;

	i = -1;
	while (game->map_data[++i])
	{
		if (!ft_strncmp(game->map_data[i], "C", 1))
			game->l_el = "C";
		else if (!ft_strncmp(game->map_data[i], "F", 1))
			game->l_el = "F";
		else if (!ft_strncmp(game->map_data[i], "NO", 2))
			game->l_el = "NO";
		else if (!ft_strncmp(game->map_data[i], "SO", 2))
			game->l_el = "SO";
		else if (!ft_strncmp(game->map_data[i], "EA", 2))
			game->l_el = "EA";
		else if (!ft_strncmp(game->map_data[i], "WE", 2))
			game->l_el = "WE";
		chek_elements(game, i);
	}
}

int	error_walls(t_game *game)
{
	size_t	x;
	int		y;
	char	**map;

	y = -1;
	map = game->map;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (error_walls_helper(game, x, y))
				return (1);
		}
	}
	return (0);
}

int	map_check(t_game *game)
{
	if (error_symbols(game))
		return (printf("Error: The map must be composed of only 6 characters(NEWS01):\n"), 1);
	if (!game->north || !game->south || !game->east || !game->west)
		return (printf("Error: Missing cardinal directions\n"), 1);
	if (!game->floor || !game->ceiling
		|| !game->floor_bit || !game->ceiling_bit)
		return (printf("Error: Missing floor/ceiling\n"), 1);
	if (error_walls(game))
		return (printf("Error: The map must be closed/surrounded by walls\n"), 1);
	if (error_corners(game))
		return (printf("Error: Empty corner exists\n"), 1);
	if (game->player_index != 1)
		return (printf("Error: Wrong player position\n"), 1);
	return (0);
}