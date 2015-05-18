/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:07:10 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 15:07:11 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_putchar2(int c)
{
	write(tty(), &c, 1);
	return (0);
}

void	clear(void)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 80)
	{
		j = 0;
		while (j < 170)
		{
			tputs(tgoto(tgetstr("cm", NULL), j++, i), 0, ft_putchar2);
			tputs(" ", 0, ft_putchar2);
		}
		i++;
	}
}

void	printarg(t_liste *place)
{
	while (place != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), place->x, place->y), 0, ft_putchar2);
		if (place->select == 1)
			tputs(tgetstr("mr", NULL), 0, ft_putchar2);
		if (place->curseur == 1)
			tputs(tgetstr("us", NULL), 0, ft_putchar2);
		tputs(place->s, 1, ft_putchar2);
		tputs(tgetstr("me", NULL), 0, ft_putchar2);
		tputs(tgetstr("ue", NULL), 0, ft_putchar2);
		place = place->next;
	}
}

int		max_c(char **s1)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if ((int)ft_strlen(s1[i]) > j)
			j = ft_strlen(s1[i]);
		i++;
	}
	return (j);
}

void	print(t_liste *place)
{
	int		i;
	t_liste	*first;

	i = 0;
	first = place;
	while (first != NULL)
	{
		if (first->select == 1 && first->s != NULL)
		{
			if (i > 0)
				ft_putchar(' ');
			ft_putstr(first->s);
			i++;
		}
		if (first->next != NULL)
			first = first->next;
		else
			break ;
	}
}
