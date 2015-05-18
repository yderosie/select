/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 14:17:10 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 14:17:13 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		fleche_bot(t_max_xy *max, t_xy *xy)
{
	if (xy->y == max->y_max && xy->x != max->x_max)
	{
		xy->y = max->y_min;
		if (xy->x < max->x_max)
			xy->x += 25;
	}
	else if (xy->x == max->x_max && xy->y == max->nb_arg_min)
	{
		xy->y = max->y_min;
		xy->x = max->x_min;
	}
	else
		xy->y++;
}

static void		fleche_top(t_max_xy *max, t_xy *xy)
{
	if (xy->x != max->x_min && xy->y == max->y_min)
	{
		xy->y = max->y_max;
		if (xy->x > max->x_min)
			xy->x -= 25;
	}
	else if (xy->x == max->x_min && xy->y == max->y_min)
	{
		xy->y = max->nb_arg_min;
		xy->x = max->x_max;
	}
	else
		xy->y--;
}

void			fleche_vertical(t_liste **first, t_max_xy *max, t_xy *xy, int i)
{
	if (i == 0)
		fleche_bot(max, xy);
	else if (i == 1)
		fleche_top(max, xy);
	curseur(*first, xy->x, xy->y);
}
