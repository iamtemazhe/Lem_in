/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:00:50 by hgysella          #+#    #+#             */
/*   Updated: 2019/04/23 19:42:16 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		sort_path(t_lem *lem)
{
	int			j;
	int			k;

	j = -1;
	while (++j < lem->n_p)
		lem->path[j] = j;
	while (j)
	{
		j = 0;
		k = -1;
		while (++k < lem->n_p - 1)
			if (lem->link[lem->path[k]]->len_p >\
					lem->link[lem->path[k + 1]]->len_p && (j = 1))
				ft_swap(&lem->path[k], &lem->path[k + 1]);
	}
	if (lem->n_r > 1000 && lem->n_p == lem->n_r)
		return (del_intersection(lem));
	return (check_intersection(lem));
}

static void		print_result(t_lem *lem, int jj)
{
	int			i;
	int			j;
	int			k;
	int			n;
	int			m;

	j = -1;
	n = 0;
	m = 0;
	while (++j <= jj)
	{
		i = -1;
		while (lem->m[++i] - j > 0 && lem->len < lem->n_a)
			if (++n && lem->path[i] >= 0 &&\
				jj - j < lem->link[lem->path[i]]->len_p)
			{
				if ((k = lem->link[lem->path[i]]->path[jj - j]) == lem->n_r - 1)
					lem->len++;
				if (m)
					write(1, " ", 1);
				ft_printf("L%d-%s", n, lem->link[k]->name);
				m++;
			}
	}
	write(1, "\n", 1);
}

int				solution(t_lem *lem)
{
	int			j;
	t_str		*s_s;

	sort_path(lem);
	s_s = lem->oper;
	while (1)
	{
		s_s = s_s->prev;
		ft_printf("%s\n", s_s->str);
		if (s_s->prev->n == 1)
			break ;
	}
	write(1, "\n", 1);
	j = 0;
	lem->len = 0;
	while (lem->len < lem->n_a)
		print_result(lem, j++);
	return (0);
}
