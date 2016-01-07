/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touches.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 17:06:01 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/01 17:06:02 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			curseur(t_liste *place, int x, int y)
{
	t_liste		*point;
	static int	x2;
	static int	y2;

	point = place;
	while (point != NULL)
	{
		if (point->x == x && point->y == y && point->curseur == 0)
			point->curseur = 1;
		else
		{
			if (x2 == x && y == y2 && point->curseur == 1)
				point->curseur = 1;
			else
				point->curseur = 0;
		}
		if (point->next != NULL)
			point = point->next;
		else
			break ;
	}
	x2 = x;
	y2 = y;
}

static void		espace2(int *x, int *y, t_max_xy *max)
{
	if (*y == max->y_max && *x != max->x_max)
	{
		*y = max->y_min;
		if (*x < max->x_max)
			*x += 25;
	}
	else if (*x == max->x_max && *y == max->nb_arg_min)
	{
		*y = max->y_min;
		*x = max->x_min;
	}
	else
		(*y)++;
}

void			espace(t_liste **first, int *x, int *y, t_max_xy *max)
{
	t_liste	*place;

	place = *first;
	while (place != NULL)
	{
		if (place->prec != NULL && place->prec->x == *x && place->prec->y == *y)
			place->curseur = 1;
		else
			place->curseur = 0;
		if (place->x == *x && place->y == *y)
		{
			place->select = (place->select == 0) ? 1 : 0;
			if (place->next == NULL)
				(*first)->curseur = 1;
		}
		place = place->next;
	}
	espace2(x, y, max);
}
