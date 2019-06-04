/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:55 by hgysella          #+#    #+#             */
/*   Updated: 2019/04/23 14:39:30 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int		save_path(t_lem *lem)
{
	int			i;
	int			j;
	int			max;

	i = lem->n_p;
	if (lem->n_p < lem->n_r)
		lem->n_p++;
	else
	{
		max = 0;
		while (--i >= 0)
			if (lem->link[i]->len_p > max && (j = i))
				max = lem->link[i]->len_p;
		if (lem->len - 1 > max)
			return (0);
		i = j;
		free(lem->link[i]->path);
	}
	lem->link[i]->len_p = lem->len - 1;
	if (!(lem->link[i]->path = ft_memdup(lem->path + 1,\
						sizeof(int) * lem->link[i]->len_p)))
		return (-1);
	return (0);
}

static int		check_room(int *arr, int i, int room)
{
	while (--i > 0)
		if (arr[i] == room)
			return (0);
	return (1);
}

int				find_path_all(t_lem *lem, int i)
{
	int			k;

	lem->path[lem->len++] = i;
	if (i == lem->n_r - 1)
	{
		if (save_path(lem))
			exit(lem_err(-1, lem));
		lem->path[lem->len--] = -1;
		return (1);
	}
	k = lem->n_r;
	while (--k > 0)
		if (lem->link[i]->sm[k] &&\
			check_room(lem->path, lem->len, k) && find_path_all(lem, k))
			break ;
	lem->path[lem->len--] = -1;
	return (0);
}

int				find_path(t_lem *lem, int i)
{
	int			k;

	if (i < lem->n_r - 1 && lem->len > lem->m[i])
		return (0);
	lem->m[i] = lem->len;
	lem->path[lem->len++] = i;
	if (i == lem->n_r - 1)
	{
		if (save_path(lem))
			exit(lem_err(-1, lem));
		lem->path[--lem->len] = -1;
		return (1);
	}
	k = 0;
	while (++k < lem->n_r - 1)
		if (lem->link[i]->sm[k] && lem->len < lem->m[k])
			lem->m[k] = lem->len;
	k = lem->n_r;
	while (--k > 0)
		if (lem->link[i]->sm[k] && find_path(lem, k))
			break ;
	lem->path[--lem->len] = -1;
	return (0);
}
