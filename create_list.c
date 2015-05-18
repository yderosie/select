/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:02:54 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 15:02:55 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_liste		*list(t_liste *first, t_liste *maillon)
{
	t_liste *point;

	point = first;
	while (point->next != NULL)
		point = point->next;
	point->next = maillon;
	point->next->prec = point;
	return (first);
}

static t_liste		*new_maillon(t_env *e, char *s)
{
	t_liste	*maillon;

	maillon = (t_liste*)malloc(sizeof(t_liste));
	if (maillon == NULL)
		return (NULL);
	maillon->x = e->x;
	maillon->y = e->y;
	maillon->s = s;
	maillon->select = 0;
	maillon->curseur = 0;
	maillon->next = NULL;
	maillon->prec = NULL;
	return (maillon);
}

static t_liste		*liste_cas_1(t_env *e, t_liste *place)
{
	int		i;
	int		y;
	int		x;
	t_liste	*maillon;

	i = 0;
	y = 0;
	x = 0;
	while (e->s1[i] != '\0')
	{
		e->x = x;
		e->y = y;
		maillon = new_maillon(e, e->s1[i]);
		place = (place == NULL) ? new_maillon(e, e->s1[i]) :
			list(place, maillon);
		i++;
		y++;
	}
	return (place);
}

static t_liste		*liste_cas_2(t_env *e, t_liste *place)
{
	int		i;
	int		y;
	int		x;
	t_liste	*maillon;

	i = 0;
	y = 0;
	x = 0;
	while (e->s1[i] != '\0')
	{
		e->x = x;
		e->y = y;
		maillon = new_maillon(e, e->s1[i]);
		place = (place == NULL) ? new_maillon(e, e->s1[i]) :
			list(place, maillon);
		i++;
		if (y + 1 == e->height)
		{
			y = 0;
			x += 25;
		}
		else
			y++;
	}
	return (place);
}

t_liste				*putarg(t_env *e)
{
	t_liste *place;

	place = NULL;
	if (e->nb_arg < e->height)
		place = liste_cas_1(e, place);
	else
		place = liste_cas_2(e, place);
	return (place);
}
