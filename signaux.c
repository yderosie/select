/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:09:50 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 15:09:50 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		signaux(int i, int k, int l)
{
	static int		j;
	struct termios	term;
	char			cp[2];

	tcgetattr(0, &term);
	if (i != 0)
		j++;
	if (k == 1)
	{
		init_term(&term);
		clear();
		signal(SIGTSTP, sig_handler);
	}
	if (l == 1)
	{
		cp[0] = term.c_cc[VSUSP];
		conf_defaut(&term);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, cp);
	}
	return (j);
}

void			sig_handler(int signo)
{
	if (signo == SIGINT)
		signaux(1, 0, 0);
	if (signo == SIGCONT)
		signaux(0, 1, 0);
	if (signo == SIGTSTP)
		signaux(0, 0, 1);
}

static int		redim_signaux(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCONT, sig_handler);
	if (signaux(0, 0, 0) != 0)
		return (0);
	return (1);
}

int				redim(t_env *e, t_liste *first, t_xy *xy, t_max_xy *max)
{
	t_liste *place;

	place = first;
	tgetent(NULL, getenv("TERM"));
	if (!redim_signaux())
		return (0);
	if (e->height != tgetnum("li") || e->width != tgetnum("co"))
	{
		clear();
		e->height = tgetnum("li");
		e->width = tgetnum("co");
		first = re_putarg(e, first, xy);
		place = first;
		tputs(tgoto(tgetstr("cm", NULL), xy->x, xy->y), 1, ft_putchar2);
	}
	*max = max_x_y(place);
	if (max->x_max + e->c_max > e->width || max->y_max > e->height)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
		tputs("Fenetre trop petite", 0, ft_putchar2);
	}
	else
		printarg(first);
	return (1);
}
