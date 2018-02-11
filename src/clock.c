/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 12:00:06 by ngrasset          #+#    #+#             */
/*   Updated: 2018/02/11 16:41:37 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		clock_init(t_clock *clock)
{
	return (gettimeofday(&(clock->time), NULL));
}

float	clock_tick(t_clock *clock)
{
	struct timeval	current_time;

	ft_memcpy(&current_time, clock, sizeof(struct timeval));
	if (gettimeofday(&(clock->time), NULL) != 0)
		return (-1);
	if (clock->time.tv_sec != current_time.tv_sec)
	{
		clock->last_tick_fps = clock->current_fps;
		clock->current_fps = 1;
	}
	else
		clock->current_fps++;
	return (fmax((clock->time.tv_usec - current_time.tv_usec) / 1000, 0));
}
