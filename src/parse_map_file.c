/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:24:34 by ngrasset          #+#    #+#             */
/*   Updated: 2017/12/17 18:50:39 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
#include <fcntl.h>

static void *	log_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}

static int		open_file(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open file ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

static int		malloc_map_data(t_map *map)
{
	int		i;

	i = 0;
	map->data = (int **)malloc(sizeof(int *) * map->height);
	if (!map->data)
		return (1);
	while (i < map->height)
	{
		map->data[i] = (int *)malloc(sizeof(int) * map->width);
		if (!map->data[i])
			return (1);
		i++;
	}
	return (0);
}

static int		parse_line(t_map *map, char *line, int i)
{
	int		j;
	char	extract[2];

	j = 0;
	extract[1] = '\0';
	while (j < map->width)
	{
		if (*line < '0' || *line > NUM_TEXTURES + '0')
			return (1);
		extract[0] = *line;
		map->data[i][j] = ft_atoi(extract);
		line++;
		j++;
		if (*line == '\0' && j == map->width)
			return (0);
		if (*line != ' ' && j != map->width)
			return (1);
		line++;
	}
	return (0);
}

t_map 			*parse_map_file(char *path)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		ret;
	int		i;

	if ((fd = open_file(path)) < 0)
		return (NULL);
	if ((map = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (log_error("Malloc error"));
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (log_error("Empty file"));
	map->width = ft_atoi(line);
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (log_error("Header heigth is missing"));
	map->height = ft_atoi(line);
	if (malloc_map_data(map) != 0)
		return (log_error("Malloc error"));
	i = 0;
	while (i < map->height)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0 || (ret == 0 && i != map->height - 1))
			return (log_error("File is shorter than header specified"));
		if (parse_line(map, line, i) != 0)
			return (log_error("Error parsing line"));
		i++;
	}
	return (map);
}
