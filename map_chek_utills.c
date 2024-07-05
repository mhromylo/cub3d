/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chek_utills.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:53:33 by mhromylo          #+#    #+#             */
/*   Updated: 2024/07/05 16:28:55 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	error_walls_helper(t_game *game, size_t x, int y)
{
	char	**map;

	map = game->map;
	if (ft_strchr("NEWS0", map[y][x]))
	{
		if (ft_strchr("NEWS", map[y][x]))
			init_player(game, x, y);
		if (y - 1 < 0 || (int)x - 1 < 0 || !map[y - 1] || !map[y + 1]
			|| ft_strlenn(map[y - 1]) <= x
			|| ft_strlenn(map[y + 1]) <= x
			|| !map[y][x - 1] || !map[y][x + 1]
			|| !check_char(map[y][x + 1], 0)
			|| !check_char(map[y + 1][x], 0)
			|| !check_char(map[y][x - 1], 0)
			|| !check_char(map[y - 1][x], 0))
			return (1);
	}
	return (0);
}

static void	find_map(t_game *game, char **map, int *i)
{
	int	x;

	x = 0;
	while (map[*i])
	{
		x = 0;
		while (map[*i][x])
		{
			if (!check_char(map[*i][x], 2))
			{
				printf("Error: Wrong map symbols\n");
				close_game(game);
			}
			if (check_char(map[*i][x], 0))
				return ;
			x++;
		}
		(*i)++;
	}
}

char	**map_create(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	j = 0;
	i = 0;
	map = NULL;
	while (game->map_data[i++]
		&& ft_strncmp(game->map_data[i], game->l_el, ft_strlenn(game->l_el)))
		continue ;
	i++;
	find_map(game, game->map_data, &i);
	map = ft_calloc((sizeof(char *)) * (game->map_height - i), 1);
	while (game->map_data[i])
		map[j++] = ft_strdup(game->map_data[i++]);
	map[j] = NULL;
	i = 0;
	while (game->map_data[i])
	{
		free(game->map_data[i++]);
	}
	
	return (map);
}

void	map_maker(t_game *game, char *str)
{
	map_load(game, str);
	map_fix(game);
	last_element(game);
	if (error_string(game))
	{
		printf("Error: Wrong map element\n");
		close_game(game);
	}
	game->mlx = mlx_init();
	map_alloc(game);
	if (map_check(game))
		close_game(game);
	init_facing_direction(game);
}
