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

t_liste		*curseur(t_liste *place, int x, int y)
{
	t_liste *point;
	static int x2;
	static int y2;

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
	return (place);
}

t_liste		*del_lst(t_liste *lst, t_max_xy *max)
{
	t_liste *first;
	t_liste *prec;
	t_liste *next;
	t_liste *elem;
	int i;
	int j;

	i = 0;
	j = 15;
	first = lst;
	while (first != NULL)
	{
		if (i != 0)
		{
			if (first->y > 0)
				first->y--;
			else if (first->y == max->y_min && first->x != max->x_min)
			{
				first->y = max->y_max;
				first->x -= 25;
			}
		}
		if (first->curseur == 1 && i == 0)
		{
			if (lst->next == NULL && lst->prec == NULL)
			{
				free(lst);
				return (NULL);
			}
			else if (first->first == 1)
			{
				lst->first = 0;
				lst->s = NULL;
				lst->curseur = 0;
				lst = lst->next;
				lst->first = 1;
				lst->curseur = 1;
				free(first->prec);
				lst->prec = NULL;
			}
			else if (first->last == 1)
			{
				first->s = NULL;
				first->last = 0;
				first->curseur = 0;
				first = first->prec;
				first->last = 1;
				first->curseur = 1;
				free(first->next);
				first->next = NULL;
			}
			else
			{
				elem = first;
				if (elem->prec != NULL)
					prec = elem->prec;
				if (elem->next != NULL)
					next = elem->next;
				if (next != NULL)
				{
					next->x = first->x;
					next->y = first->y;
				}
				if (prec != NULL)
					prec->next = next;
				if (next != NULL)
					next->prec = prec;
				if (next != NULL)
					next->curseur = 1;
				free(elem);
				elem = NULL;
				if (prec != NULL)
					first = next;
				else
					first = prec;
			}
			i++;
		}
		if (first->next != NULL)
			first = first->next;
		else
			break ;
	}
	return (lst);
}

t_liste		*espace(t_liste *first, int *x, int *y, t_max_xy *max)
{
	t_liste	*place;

	place = first;
	while (place != NULL)
	{
		if (place->prec != NULL && place->prec->x == *x && place->prec->y == *y)
			place->curseur = 1;
		else
			place->curseur = 0;
		if (place->x == *x && place->y == *y)
		{
			if (place->select == 0)
				place->select = 1;
			else
				place->select = 0;
		}
		if (place->next != NULL)
		{
			place = place->next;
		}
		else
			break ;
	}
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
	return (first);
}

void		fleche_right(t_max_xy *max, t_xy *xy)
{
	if (xy->x == max->x_max && xy->y == max->nb_arg_min)
		xy->x = max->x_min;
	else if (xy->x == max->x_max && xy->y != max->nb_arg_min)
		xy->x = max->x_min;
	else if (xy->x != max->x_max && xy->y > max->nb_arg_min)
		xy->x += 0;
	else
		xy->x += 25;
}

void		fleche_left(t_max_xy *max, t_xy *xy)
{
	if (xy->x == max->x_min && xy->y == max->y_min)
		xy->x = max->x_max;
	else if (xy->x == max->x_min && xy->y != max->y_min)
	{
		if (xy->y <= max->nb_arg_min + 1)
			xy->x = max->x_max;
	}
	else
		xy->x -= 25;
}

t_liste		*fleche_horizontal(t_liste *first, t_max_xy *max, t_xy *xy, int i)
{
	if (i == 0)
		fleche_right(max, xy);
	else if (i == 1)
		fleche_left(max, xy);
	first = curseur(first, xy->x, xy->y);
	return (first);
}

void		fleche_bot(t_max_xy *max, t_xy *xy)
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

void		fleche_top(t_max_xy *max, t_xy *xy)
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

t_liste		*fleche_vertical(t_liste *first, t_max_xy *max, t_xy *xy, int i)
{
	if (i == 0)
		fleche_bot(max, xy);
	else if (i == 1)
		fleche_top(max, xy);
	first = curseur(first, xy->x, xy->y);
	return (first);
}