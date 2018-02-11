/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:24:34 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 15:07:42 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>
#include <fcntl.h>

static void		*log_error(char *str, int fd, t_map *map)
{
	ft_putendl_fd(str, 2);
	close(fd);
	if (map)
		free_map_data(map);
	return (NULL);
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
		if (*line != '0' && *line != '1')
		{
			printf("error: %c\n", *line);
			return (1);
		}
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

t_map			*read_map_data(t_map *map, int fd)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	while (i < map->height)
	{
		ret = get_next_line(fd, &line);
		if (!line || ret < 0 || (ret == 0 && i != map->height - 1))
			return (log_error("File is shorter than expected", fd, map));
		if (parse_line(map, line, i) != 0)
			return (log_error("Error parsing line", fd, map));
		i++;
	}
	close(fd);
	return (map);
}

t_map			*parse_map_file(char *path)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Could not open file ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	if ((map = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (log_error("Malloc error", fd, NULL));
	ft_memset(map, 0, sizeof(t_map));
	if ((ret = get_next_line(fd, &line) <= 0))
		return (log_error("Empty file", fd, map));
	map->width = ft_atoi(line);
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (log_error("Header heigth is missing", fd, map));
	map->height = ft_atoi(line);
	if (malloc_map_data(map) != 0)
		return (log_error("Malloc error", fd, map));
	return (read_map_data(map, fd));
}
