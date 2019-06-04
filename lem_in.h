/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:31:34 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/24 15:49:16 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct		s_str
{
	char			*str;
	int				n;
	struct s_str	*prev;
	struct s_str	*next;
}					t_str;

typedef struct		s_link
{
	char			*name;
	int				prant;
	int				ant;
	int				x;
	int				y;
	int				n_l;
	int				len_p;
	int				*sm;
	int				*path;
	struct s_link	*next;
}					t_link;

typedef struct		s_lem
{
	t_str			*oper;
	t_str			*cur_op;
	t_link			*start;
	t_link			**link;
	t_link			*end;
	int				*path;
	int				*m;
	int				len;
	int				n_a;
	int				n_r;
	int				n_p;
	int				err;
}					t_lem;

int					find_path(t_lem *lem, int i);
int					find_path_all(t_lem *lem, int i);
int					solution(t_lem *lem);
int					check_intersection(t_lem *lem);
int					del_intersection(t_lem *lem);

int					lem_err(int retv, t_lem *lem);
int					lem_null_par(t_lem *lem, int mod);
int					argreader(t_lem *lem, int mod);

void				link_del(t_link **link_p);
int					link_err(int retv, t_link **link_p);
int					link_nerr(int retv, t_link **link_p, int n);
t_link				*link_new(char *line);
t_link				*link_add(char *line, t_link *link_dst);

void				t_strdel(t_str **str_p);
int					t_strerr(int retv, t_str **str_p);
t_str				*t_strnew(char *str, int n);
t_str				*t_stradd(char *str, t_str *str_dst);
#endif
