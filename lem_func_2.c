/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_func_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:45:51 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/25 15:41:09 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void		lem_null_par_2(t_lem *lem)
{
	lem->link = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->path = NULL;
	lem->m = NULL;
	lem->cur_op = NULL;
	lem->oper = NULL;
	lem->n_a = 0;
	lem->n_r = 0;
	lem->n_p = 0;
	lem->len = 0;
}

int				lem_null_par(t_lem *lem, int mod)
{
	if (mod)
	{
		lem->link = (t_link**)malloc(sizeof(t_link*) * lem->n_r);
		lem->start->sm = (int*)ft_memalloc(sizeof(int) * lem->n_r);
		lem->end->sm = (int*)ft_memalloc(sizeof(int) * lem->n_r);
		if (!(lem->link && lem->start->sm && lem->end->sm))
			return (-1);
		if (mod < 2)
		{
			lem->path = (int*)ft_memalloc(sizeof(int) * lem->n_r);
			lem->m = (int*)ft_memalloc(sizeof(int) * lem->n_r);
			if (!(lem->path && lem->m))
				return (-1);
			ft_memnset(lem->path, -1, 4, lem->n_r);
			ft_memnset(lem->m, MAXINT, 4, lem->n_r);
		}
		return (0);
	}
	lem_null_par_2(lem);
	if (!(lem->start = link_new(NULL)))
		return (-1);
	if (!(lem->end = link_new(NULL)))
		return (-1);
	return (0);
}

int				lem_err(int retv, t_lem *lem)
{
	if (lem->link)
	{
		link_nerr(0, lem->link, lem->n_r);
		free(lem->link);
	}
	else
		lem->err = link_err(0, &lem->start) + link_err(0, &lem->end);
	lem->err = ft_masserr(0, &lem->m) + ft_masserr(0, &lem->path) +\
												t_strerr(0, &lem->oper);
	if (retv < 0)
		ft_puterr(retv, "ERROR");
	return (retv);
}
