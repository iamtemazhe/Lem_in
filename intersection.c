/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:26:59 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/26 15:51:39 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		path_select(t_lem *lem, int n_p)
{
	int			i;
	int			j;
	int			s;

	s = 0;
	ft_memcpy(lem->path, lem->m, sizeof(int) * n_p);
	ft_memnset(lem->m, 0, 4, lem->n_r);
	while (s < lem->n_a)
	{
		i = 0;
		while (++i < n_p)
			while (lem->link[lem->path[0]]->len_p + lem->m[0] <\
						lem->link[lem->path[i]]->len_p && s < lem->n_a)
			{
				j = -1;
				while (++j < i && s++ < lem->n_a)
					lem->m[j]++;
			}
		j = -1;
		while (++j < i && s++ < lem->n_a)
			lem->m[j]++;
	}
	lem->n_p = n_p;
	return (0);
}

static int		circle_intersection(t_lem *lem, int i1, int mod)
{
	int			i[6];

	i[5] = 0;
	i[2] = -1;
	while (++i[2] < lem->n_p)
	{
		i[3] = -1;
		while (++i[3] < lem->link[lem->path[i1]]->len_p - 1)
		{
			if (lem->path[i[2]] < 0 || i1 == i[2])
				break ;
			i[4] = -1;
			while (++i[4] < lem->link[lem->path[i[2]]]->len_p - 1)
				if (lem->link[lem->path[i1]]->path[i[3]] ==\
							lem->link[lem->path[i[2]]]->path[i[4]])
				{
					if (mod)
						lem->path[i[2]] = -1;
					else
						i[5]++;
					break ;
				}
		}
	}
	return (i[5]);
}

static void		count_intersection(t_lem *lem, int i1)
{
	int			i[8];

	i[7] = i1;
	if (lem->n_r > 1000 || lem->n_a > 1)
	{
		i[1] = i1 - 1;
		i[6] = MAXINT;
		i[0] = lem->link[lem->path[i1]]->path[0];
		while (++i[1] < lem->n_p)
			if (lem->path[i[1]] >= 0 && i[0] ==\
				lem->link[lem->path[i[1]]]->path[0])
			{
				i[5] = circle_intersection(lem, i[1], 0);
				i[7] = (i[6] >= i[5]) ? i[1] : i[7];
				i[6] = (i[6] > i[5]) ? i[5] : i[6];
			}
	}
	circle_intersection(lem, i[7], 1);
}

int				check_intersection(t_lem *lem)
{
	int			i[6];

	i[5] = 0;
	i[1] = -1;
	while (++i[1] < lem->n_p - 1)
		if (lem->path[i[1]] >= 0)
			count_intersection(lem, i[1]);
	i[0] = 0;
	i[1] = -1;
	while (++i[1] < lem->n_p)
		if (lem->path[i[1]] >= 0)
			lem->m[i[0]++] = lem->path[i[1]];
	return (path_select(lem, i[0]));
}

int				del_intersection(t_lem *lem)
{
	int			i[5];

	i[0] = 0;
	i[1] = -1;
	while (++i[1] < lem->n_p - 1)
		if (lem->path[i[1]] >= 0 && (lem->m[i[0]++] = lem->path[i[1]]))
		{
			i[3] = lem->link[lem->path[i[1]]]->len_p;
			i[2] = i[1];
			while (++i[2] < lem->n_p)
			{
				if (lem->path[i[2]] < 0)
					continue ;
				i[4] = lem->link[lem->path[i[2]]]->len_p;
				if ((lem->link[lem->path[i[1]]]->path[0] ==\
					lem->link[lem->path[i[2]]]->path[0] ||\
					(i[3] > 1 && i[4] > 1 &&\
					lem->link[lem->path[i[1]]]->path[i[3] - 2] ==\
					lem->link[lem->path[i[2]]]->path[i[4] - 2])))
					lem->path[i[2]] = -1;
			}
		}
	return (path_select(lem, i[0]));
}
