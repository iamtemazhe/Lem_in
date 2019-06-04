/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:30:40 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/24 16:22:38 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void			link_del(t_link **link_p)
{
	if (!(link_p && *link_p))
		return ;
	free(*link_p);
	*link_p = NULL;
}

int				link_err(int retv, t_link **link_p)
{
	t_link		*link_tmp;

	if (!(link_p && *link_p))
		return (retv);
	while (*link_p)
	{
		link_tmp = link_p[0]->next;
		ft_strdel(&link_p[0]->name);
		ft_masserr(0, &link_p[0]->sm);
		ft_masserr(0, &link_p[0]->path);
		link_del(&link_p[0]);
		*link_p = link_tmp;
	}
	return (retv);
}

int				link_nerr(int retv, t_link **link_p, int n)
{
	if (!link_p)
		return (retv);
	while (--n >= 0)
	{
		ft_strdel(&link_p[n]->name);
		ft_masserr(0, &link_p[n]->sm);
		ft_masserr(0, &link_p[n]->path);
		link_del(&link_p[n]);
	}
	return (retv);
}

t_link			*link_new(char *line)
{
	int			pr_x;
	int			pr_y;
	char		*str;
	t_link		*link_elink;

	if (!(link_elink = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	link_elink->name = NULL;
	link_elink->sm = NULL;
	link_elink->path = NULL;
	link_elink->next = NULL;
	link_elink->n_l = 0;
	link_elink->ant = 0;
	link_elink->prant = 0;
	link_elink->len_p = MAXINT;
	if (!line)
		return (link_elink);
	str = ft_strchr(line, ' ');
	if (!(link_elink->name = ft_strsub(line, 0, str - line)))
		return (NULL);
	link_elink->x = pratoi(&str, &pr_x);
	link_elink->y = pratoi(&str, &pr_y);
	if (pr_x == -1 || pr_y == -1)
		return (NULL);
	return (link_elink);
}

t_link			*link_add(char *line, t_link *link_dst)
{
	t_link		*link_elink;

	if (!link_dst)
		return (link_dst = link_new(line));
	if (!(link_elink = link_new(line)))
		return (NULL);
	link_elink->next = link_dst;
	return (link_elink);
}
