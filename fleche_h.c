/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 14:17:30 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 14:17:31 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	fleche_right(t_max_xy *max, t_xy *xy)
{
	if (xy->x == max->x_max && xy->y == max->nb_arg_min)
		xy->x = max->x_min;
	else if (xy->x == max->x_max)
		xy->x = max->x_min;
	else if (xy->x != max->x_max && xy->y > max->nb_arg_min)
	{
		if (xy->x + 25 == max->x_max)
			xy->x = max->x_min;
		else
			xy->x += 25;
	}
	else
		xy->x += 25;
}

static void	fleche_left(t_max_xy *max, t_xy *xy)
{
	if (xy->x == max->x_min && xy->y == max->y_min)
		xy->x = max->x_max;
	else if (xy->x == max->x_min && xy->y != max->y_min)
	{
		if (xy->y <= max->nb_arg_min)
			xy->x = max->x_max;
		else
			xy->x = max->x_max - 25;
	}
	else
		xy->x -= 25;
}

void		fleche_horizontal(t_liste **first, t_max_xy *max, t_xy *xy, int i)
{
	if (i == 0)
		fleche_right(max, xy);
	else if (i == 1)
		fleche_left(max, xy);
	curseur(*first, xy->x, xy->y);
}
