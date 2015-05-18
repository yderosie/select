/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:08:49 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 15:08:50 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		max_x_y2(t_max_xy *max, t_liste **move)
{
	if ((*move)->prec == NULL)
	{
		max->x_min = (*move)->x;
		max->y_min = (*move)->y;
	}
	if (max->x_max < (*move)->x)
		max->x_max = (*move)->x;
	if (max->y_max < (*move)->y)
		max->y_max = (*move)->y;
	(*move) = (*move)->next;
}

t_max_xy		max_x_y(t_liste *first)
{
	t_max_xy	max;
	t_liste		*move;

	move = first;
	max.nb_arg_min = 0;
	while (move != NULL)
	{
		max_x_y2(&max, &move);
	}
	move = first;
	while (move != NULL)
	{
		if (move->x == max.x_max)
			max.nb_arg_min++;
		if (move->next != NULL)
			move = move->next;
		else
			break ;
	}
	max.nb_arg_min -= 1;
	return (max);
}
