/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 14:15:13 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 14:15:15 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		call_del1(t_liste *first, t_max_xy *max)
{
	if (first->y > 0)
		first->y--;
	else if (first->y == max->y_min && first->x != max->x_min)
	{
		first->y = max->y_max;
		first->x -= 25;
	}
}

int				del_lst(t_liste **lst, t_max_xy *max, t_xy *xy)
{
	t_liste	*first;
	int		i;

	i = 0;
	first = *lst;
	while (first != NULL)
	{
		if (i != 0)
			call_del1(first, max);
		if (first->curseur == 1 && i == 0)
		{
			if (!call_del2(lst, &first, xy))
				return (0);
			i++;
		}
		if (first->next != NULL)
			first = first->next;
		else
			break ;
	}
	return (1);
}
