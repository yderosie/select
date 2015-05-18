/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:45:19 by yderosie          #+#    #+#             */
/*   Updated: 2015/03/25 15:45:21 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H

# define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct termios	t_termios;

typedef struct	s_max_xy
{
	int y_min;
	int x_min;
	int y_max;
	int x_max;
	int c_max;
	int nb_arg_min;
}				t_max_xy;

typedef	struct	s_xy
{
	int y;
	int x;
}				t_xy;

typedef struct	s_liste
{
	int				x;
	int				y;
	char			*s;
	int				select;
	int				curseur;
	struct s_liste	*prec;
	struct s_liste	*next;
}				t_liste;

typedef struct	s_env
{
	int		width;
	int		height;
	int		tmp;
	int		tmp2;
	int		auto_wrap;
	char	**s1;
	int		fd;
	int		nb_arg;
	int		x;
	int		y;
	int		first;
	int		c_max;
}				t_env;

t_liste			*putarg(t_env *e);
void			curseur(t_liste *place, int x, int y);
void			espace(t_liste **first, int *x, int *y, t_max_xy *max);
void			fleche_horizontal(t_liste **first, t_max_xy *max, t_xy *xy,
					int i);
void			fleche_vertical(t_liste **first, t_max_xy *max, t_xy *xy,
					int i);
int				del_lst(t_liste **lst, t_max_xy *max, t_xy *xy);
int				ft_putchar2(int c);
int				init_term(struct termios *term);
void			sig_handler(int signo);
int				tty(void);
t_max_xy		max_x_y(t_liste *first);
int				redim(t_env *e, t_liste *first, t_xy *xy, t_max_xy *max);
int				ft_putchar2(int c);
void			clear(void);
void			print(t_liste *place);
int				max_c(char **s1);
void			printarg(t_liste *place);
t_liste			*re_putarg(t_env *e, t_liste *first, t_xy *xy);
t_liste			*putarg(t_env *e);
int				call_del2(t_liste **lst, t_liste **first, t_xy *xy);
void			init_e(t_env *e);
void			first_init_e(t_env *e, char **argv, int argc, int max);
void			conf_defaut(struct termios *term);
void			sig_handler(int signo);

#endif
