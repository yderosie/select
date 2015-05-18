/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:04:03 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 15:04:03 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		resize_cas_1(t_liste *place, t_xy *xy)
{
	int i;
	int y;
	int x;

	i = 0;
	y = 0;
	x = 0;
	while (place != NULL)
	{
		if (place->curseur == 1)
		{
			xy->x = x;
			xy->y = y;
		}
		place->x = x;
		place->y = y;
		y++;
		place = place->next;
	}
}

static void		resize_cas_2(t_env *e, t_liste *place, t_xy *xy)
{
	int i;
	int y;
	int x;

	i = 0;
	y = 0;
	x = 0;
	while (place != NULL)
	{
		if (place->curseur == 1)
		{
			xy->x = x;
			xy->y = y;
		}
		place->x = x;
		place->y = y;
		if (y + 1 == e->height)
		{
			y = 0;
			x += 25;
		}
		else
			y++;
		place = place->next;
	}
}

t_liste			*re_putarg(t_env *e, t_liste *first, t_xy *xy)
{
	t_liste *place;

	place = first;
	if (e->nb_arg < e->height)
		resize_cas_1(place, xy);
	else
		resize_cas_2(e, place, xy);
	return (first);
}
