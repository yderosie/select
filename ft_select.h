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

#define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct termios t_termios;

typedef struct		s_max_xy
{
	int y_min;
	int x_min;
	int y_max;
	int x_max;
	int c_max;
	int nb_arg_min;
}					t_max_xy;

typedef	struct 		s_xy
{
	int y;
	int x;
}					t_xy;

typedef struct		s_liste
{
	int				x;
	int				y;
	char			*s;
	int				first;
	int				last;
	int				select;
	int				curseur;
	struct s_liste	*prec;
	struct s_liste	*next;
}					t_liste;

typedef struct 	s_env
{
	int		width;
	int		height;
	int		tmp;
	int		tmp2;
	int		auto_wrap;
	char	**s1;
	int		nb_arg;
	int		x;
	int		y;
	int		first;
	int		c_max;
}				t_env;

t_liste		*putarg(t_env *e);
t_liste		*curseur(t_liste *place, int x, int y);
t_liste		*espace(t_liste *first, int *x, int *y, t_max_xy *max);
t_liste		*fleche_horizontal(t_liste *first, t_max_xy *max, t_xy *xy, int i);
t_liste		*fleche_vertical(t_liste *first, t_max_xy *max, t_xy *xy, int i);
t_liste		*del_lst(t_liste *lst, t_max_xy *max);
int		ft_putchar2(int c);

#endif
