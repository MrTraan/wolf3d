/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 12:00:06 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/19 12:13:56 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		clock_init(t_clock *clock)
{
	return(gettimeofday(&(clock->time), NULL));
}

int		clock_tick(t_clock *clock)
{
	time_t		current_time;

	current_time = clock->time.tv_sec;
	if (gettimeofday(&(clock->time), NULL) != 0)
		return (-1);
	if (clock->time.tv_sec != current_time)
	{
		clock->last_tick_fps = clock->current_fps;
		clock->current_fps = 1;
	}
	else
		clock->current_fps++;
	return (clock->last_tick_fps);
}
