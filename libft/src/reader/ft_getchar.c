/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:34:48 by ngrasset          #+#    #+#             */
/*   Updated: 2015/11/27 17:46:22 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getchar(int fd)
{
	int		c;
	int		ret;

	c = 0;
	ret = read(fd, &c, 1);
	if (ret != 1)
		return (-1);
	return (c);
}
