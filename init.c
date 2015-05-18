/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 14:13:30 by yderosie          #+#    #+#             */
/*   Updated: 2015/05/17 14:13:32 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		tty(void)
{
	static int fd = -1;

	if (fd == -1)
		fd = open("/dev/tty", O_RDWR);
	return (fd);
}

void	conf_defaut(t_termios *term)
{
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar2);
	tputs(tgetstr("ve", NULL), 0, ft_putchar2);
	tputs(tgetstr("te", NULL), 0, ft_putchar2);
	tputs(tgetstr("cr", NULL), 0, ft_putchar2);
	tcgetattr(0, term);
	term->c_lflag |= (ICANON & ECHO);
	tcsetattr(0, 0, term);
}

int		init_term(struct termios *term)
{
	if (getenv("TERM") == NULL)
		return (0);
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, term);
	tputs(tgetstr("vi", NULL), 0, ft_putchar2);
	tputs(tgetstr("ti", NULL), 0, ft_putchar2);
	return (1);
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
