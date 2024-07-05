/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:55:07 by mhromylo          #+#    #+#             */
/*   Updated: 2024/06/24 18:12:50 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	err_str_helper(char **map, int i)

{
	if (ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3)
		&& ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)
		&& ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)
		&& ft_strncmp(map[i], "\n", 1))
		return (1);
	return (0);
}

int	error_string(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map_data;
	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\0' || map[i][0] == ' ')
		{
			while (map[i][j] && map[i][j] != '\0')
			{
				if (map[i][j] != ' ' && map[i][j] != '\t')
					return (1);
				j++;
			}
		}
		else if (err_str_helper(map, i))
			return (1);
		if (!ft_strncmp(map[i], game->l_el, ft_strlen_int(game->l_el)))
			break ;
		i++;
	}
	return (0);
}

int	check_char(char map, int i)
{
	if (i == 0)
	{
		if (ft_strchr("NEWS01", map))
			return (1);
	}
	if (i == 1)
	{
		if (ft_strchr("NEWS01 ", map))
			return (1);
	}
	if (i == 2)
	{
		if (ft_strchr("NEWS01 \n", map))
			return (1);
	}
	return (0);
}

int	error_symbols(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	x = 0;
	y = 0;
	map = game->map;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\0')
		{
			if (!check_char(map[y][x], 2))
			{
				printf("Symbol = %c\n", map[y][x]);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	error_corners(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = game->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NEWS0", game->map[y][x]))
			{
				if (!map[y - 1][x + 1] || !map[y + 1][x + 1]
					|| !check_char(map[y - 1][x - 1], 0)
					|| !check_char(map[y + 1][x - 1], 0)
					|| !check_char(map[y - 1][x + 1], 0)
					|| !check_char(map[y + 1][x + 1], 0))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}