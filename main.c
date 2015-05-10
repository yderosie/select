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

int		ft_putchar2(int c)
{
	write(1, &c, 1);
	return (0);
}

void	init_e(t_env *e)
{
	e->height = tgetnum("li");
	e->width = tgetnum("co");
}

void	first_init_e(t_env *e, char **argv, int argc, int max)
{
	e->s1 = argv;
	e->nb_arg = argc;
	e->c_max = max;
	e->height = tgetnum("li");
	e->width = tgetnum("co");
}

void	clear(t_env *e)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 80 && e->height != 0)
	{
		j = 0;
		while (j < 130)
		{
			tputs(tgoto(tgetstr("cm", NULL), j++, i), 0, ft_putchar2);
			tputs(" ", 0, ft_putchar2);
		}
		i++;
	}
}

void	printarg(t_liste *place)
{
	int i;
	int j;

	j = 0;
	i = 15;
	while (place != NULL)
	{
		tputs(tgetstr("cr", NULL), 0, ft_putchar2);
		tputs(tgoto(tgetstr("cm", NULL), place->x, place->y), 0, ft_putchar2);
		tputs(tgetstr("md", NULL), 0, ft_putchar2);
		if (place->select == 1)
			tputs(tgetstr("mr", NULL), 0, ft_putchar2);
		if (place->curseur == 1)
			tputs(tgetstr("us", NULL), 0, ft_putchar2);
		tputs(place->s, 1, ft_putchar2);
		tputs(tgetstr("me", NULL), 0, ft_putchar2);
		tputs(tgetstr("cr", NULL), 0, ft_putchar2);
		tputs(tgetstr("ue", NULL), 0, ft_putchar2);
		if (place->next != NULL)
			place = place->next;
		else
			break;
	}
}

t_max_xy	max_x_y(t_liste *first)
{
	t_max_xy	max;
	t_liste		*move;

	move = first;
	max.nb_arg_min = 0;
	while (move != NULL)
	{
		if (move->first == 1)
		{
			max.x_min = move->x;
			max.y_min = move->y;
		}
		if (max.x_max < move->x)
			max.x_max = move->x;
		if (max.y_max < move->y)
			max.y_max = move->y;
		if (move->next != NULL)
			move = move->next;
		else
			break ;
	}
	move = first;
	while (move != NULL)
	{
		if (move->x == max.x_max)
			max.nb_arg_min++;
		if (move->next != NULL)
			move = move->next;
		else
			break ;
	}
	max.nb_arg_min -= 1;
	return (max);
}

int			signaux(int i, int k, int l)
{
	static int j;

	if (i != 0 || k != 0 || l != 0)
		j++;
	return (j);
}

void			sig_handler(int signo)
{
	tputs(tgoto(tgetstr("cm", NULL), 15, 15), 1, ft_putchar2);
	if (signo == SIGINT)
		signaux(1, 0, 0);
	if (signo == SIGKILL)
		signaux(0, 1, 0);
}

t_liste 	*voir_touche(t_env *e)
{
	char	buffer[3];
	t_xy	xy;
	t_liste *place;
	t_liste	*first;
	t_max_xy max;

	xy.x = 0;
	xy.y = 0;
	max.c_max = e->c_max;
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
	init_e(e);
	clear(e);
	first = putarg(e);
	place = first;
	if (first != NULL)
		first->curseur = 1;
	while (1)
	{
		tgetent(NULL, getenv("TERM"));
		if (signal(SIGINT, sig_handler) == SIG_ERR)
			;
		if (signal(SIGKILL, sig_handler) == SIG_ERR)
			;
		if (signaux(0, 0, 0) != 0)
			return (NULL);
		if (e->height != tgetnum("li") || e->width != tgetnum("co"))
		{
			clear(e);
			e->height = tgetnum("li");
			e->width = tgetnum("co");
			first = putarg(e);
			place = first;
			xy.x = 0;
			xy.y = 0;
			if (first != NULL)
			first->curseur = 1;
			tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
		}
		max = max_x_y(place);
		if (max.x_max + e->c_max > e->width || max.y_max > e->height)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
			tputs("Fenetre trop petite", 0, ft_putchar2);
		}
		else
			printarg(first);
		tputs(tgoto(tgetstr("cm", NULL), xy.x, xy.y), 1, ft_putchar2);
		read(0, buffer, 3);
		if (buffer[0] == 32 && buffer[1] == 0 && buffer[2] == 0)
			place = espace(place, &xy.x, &xy.y, &max);
		else if (buffer[0] == 10 && buffer[1] == 0 && buffer[2] == 0)
			return(first);
		else if ((buffer[0] == 126 && buffer[1] == 0 && buffer[2] == 01) ||
			(buffer[0] == 127 && buffer[1] == 0 && buffer[2] == 0))
		{
			if ((place = del_lst(place, &max)) == NULL)
				return (NULL);
			clear(e);
		}
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
			place = fleche_horizontal(place, &max, &xy, 0);
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
			place = fleche_vertical(place, &max, &xy, 0);
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
			place = fleche_horizontal(place, &max, &xy, 1);
		else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
			place = fleche_vertical(place, &max, &xy, 1);
		else if (buffer[0] == 27 && buffer[1] == 0 && buffer[2] == 0)
			return (NULL);
		tputs(tgoto(tgetstr("cm", NULL), xy.x, xy.y), 1, ft_putchar2);
		ft_bzero(buffer, 3);
	}
	return (NULL);
}

t_liste		*list(t_liste *first, t_liste *maillon)
{
	t_liste *point;

	point = first;
	while (point->next != NULL)
		point = point->next;
	point->next = maillon;
	point->last = 0;
	point->next->prec = point;
	return (first);
}

t_liste		*new_maillon(int first, t_env *e, char *s)
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
	maillon->first = first;
	maillon->last = 1;
	maillon->next = NULL;
	maillon->prec = NULL;
	return (maillon);
}

t_liste		*liste_cas_1(t_env *e, t_liste *place)
{
	int i;
	int y;
	int x;
	t_liste *maillon;

	i = 0;
	y = 0;
	x = 0;
	while (e->s1[i] != '\0')
	{
		e->x = x;
		e->y = y;
		maillon = new_maillon(0, e, e->s1[i]);
		place = (place == NULL) ? new_maillon(1, e, e->s1[i]) :
			list(place, maillon);
		i++;
		y++;
	}
	return (place);
}

t_liste		*liste_cas_2(t_env *e, t_liste *place)
{
	int i;
	int y;
	int x;
	t_liste *maillon;

	i = 0;
	y = 0;
	x = 0;
	while (e->s1[i] != '\0')
	{
		e->x = x;
		e->y = y;
		maillon = new_maillon(0, e, e->s1[i]);
		place = (place == NULL) ? new_maillon(1, e, e->s1[i]) :
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

t_liste		*putarg(t_env *e)
{
	t_liste *place;

	place = NULL;
	if (e->nb_arg < e->height)
		place = liste_cas_1(e, place);
	else
		place = liste_cas_2(e, place);
	return (place);
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

int		init_term(struct termios *term)
{
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, term);
	return (0);
}

void	print(t_liste *place)
{
	int i;
	t_liste *first;

	i = 0;
	first = place;
	while (first != NULL)
	{
		if (first->select == 1)
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

int main(int argc, char **argv)
{
	struct termios	term;
	t_env 			e;
	int				i;
	t_liste			*lst;

	i = 0;
	lst = NULL;
	init_term(&term);
	tputs(tgetstr("vi", NULL), 0, ft_putchar2);
	tputs(tgetstr("ti", NULL), 0, ft_putchar2);
	first_init_e(&e, argv + 1, argc - 1, max_c(argv + 1));
	clear(&e);
	if ((lst = voir_touche(&e)) == NULL)
		i++;
	tputs(tgetstr("ve", NULL), 0, ft_putchar2);
	tputs(tgetstr("te", NULL), 0, ft_putchar2);
	tputs(tgetstr("cr", NULL), 0, ft_putchar2);
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON & ECHO);
 	tcsetattr(0, 0, &term);
 	if (i == 0)
 		print(lst);
	free(lst);
	return (0);
}
