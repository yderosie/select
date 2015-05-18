/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 14:16:29 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 14:16:31 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		del_first(t_liste **lst)
{
	t_liste *first;

	first = *lst;
	if (first->next != NULL)
		first = first->next;
	first->curseur = 1;
	first->prec = NULL;
	free(*lst);
	*lst = NULL;
	*lst = first;
}

static void		del_last(t_liste **first, t_xy *xy)
{
	(*first)->curseur = 0;
	(*first) = (*first)->prec;
	(*first)->curseur = 1;
	free((*first)->next);
	(*first)->next = NULL;
	xy->y--;
}

static void		del_mid(t_liste **first, t_liste *elem)
{
	(elem) = (*first);
	(*first) = (elem)->prec;
	(*first)->next = (elem)->next;
	(*first) = (elem)->next;
	(*first)->prec = (elem)->prec;
	(*first)->x = (elem)->x;
	(*first)->y = (elem)->y;
	(*first)->curseur = 1;
	free((elem));
	(elem) = NULL;
}

int				call_del2(t_liste **lst, t_liste **first, t_xy *xy)
{
	t_liste *elem;

	elem = *first;
	if ((*lst)->next == NULL && (*lst)->prec == NULL)
	{
		free(*lst);
		*lst = NULL;
		return (0);
	}
	else if ((*first)->prec == NULL)
		del_first(lst);
	else if ((*first)->next == NULL)
		del_last(first, xy);
	else
		del_mid(first, elem);
	return (1);
}
