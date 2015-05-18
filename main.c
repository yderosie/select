/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:40:43 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/08 15:21:29 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		touche2(t_liste **place, t_max_xy *max, t_xy *xy, char buffer[])
{
	if (buffer[0] == 32 && buffer[1] == 0 && buffer[2] == 0)
		espace(place, &xy->x, &xy->y, max);
	else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
		return (0);
	else if ((buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51) ||
		(buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0))
	{
		if (del_lst(place, max, xy) == 0)
			return (0);
		clear();
	}
	else if (buffer[0] == 27 && buffer[1] == 0 && buffer[2] == 0)
		return (-1);
	*max = max_x_y(*place);
	return (1);
}

static int		touche(t_liste **place, t_max_xy *max, t_xy *xy)
{
	char	buffer[7];
	int		i;

	i = 0;
	ft_bzero(buffer, 7);
	read(0, buffer, 7);
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
		fleche_horizontal(place, max, xy, 0);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		fleche_vertical(place, max, xy, 0);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
		fleche_horizontal(place, max, xy, 1);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		fleche_vertical(place, max, xy, 1);
	i = touche2(place, max, xy, buffer);
	if (i != 1)
		return (i);
	ft_bzero(buffer, 7);
	return (1);
}

static void		init_touche(t_env *e, t_xy *xy, t_max_xy *max)
{
	xy->x = 0;
	xy->y = 0;
	max->c_max = e->c_max;
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
	init_e(e);
	clear();
}

t_liste			*voir_touche(t_env *e)
{
	t_xy		xy;
	t_liste		*first;
	t_max_xy	max;
	int			i;

	i = 0;
	init_touche(e, &xy, &max);
	first = putarg(e);
	if (first != NULL)
		first->curseur = 1;
	while (1)
	{
		max = max_x_y(first);
		if (!redim(e, first, &xy, &max))
			return (NULL);
		tputs(tgoto(tgetstr("cm", NULL), xy.x, xy.y), 1, ft_putchar2);
		max = max_x_y(first);
		i = touche(&first, &max, &xy);
		if (i == -1)
			return (NULL);
		else if (i == 0)
			return (first);
	}
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_termios		term;
	t_env			e;
	int				i;
	t_liste			*lst;

	i = 0;
	lst = NULL;
	if (argc < 2)
		return (0);
	tty();
	if (init_term(&term) == 0)
		return (0);
	first_init_e(&e, argv + 1, argc - 1, max_c(argv + 1));
	clear();
	if ((lst = voir_touche(&e)) == NULL)
		i++;
	conf_defaut(&term);
	close(tty());
	if (i == 0)
		print(lst);
	free(lst);
	return (0);
}
