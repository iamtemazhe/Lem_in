/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:32:18 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/25 15:47:12 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		graffiller(char *line, char *str, t_lem *lem)
{
	int			i;
	int			j;
	int			len;

	if (!str)
	{
		if (!(lem->start->next = link_add(line, lem->start->next)))
			return (-1);
		return (!(++lem->n_r));
	}
	i = -1;
	j = -1;
	while (++i < lem->n_r)
		if ((len = ft_strlen(lem->link[i]->name)) &&\
			!ft_strncmp(lem->link[i]->name, line,\
			(len > str - line) ? len : str - line))
			break ;
	while (++j < lem->n_r)
		if (!ft_strcmp(lem->link[j]->name, str + 1))
			break ;
	if (i == lem->n_r || j == lem->n_r)
		return (-1);
	if ((lem->link[i]->sm[j] = 1) && ++lem->link[i]->n_l && ++lem->link[j]->n_l)
		lem->link[j]->sm[i] = 1;
	return (0);
}

static int		grafcreater(char *line, char *str, t_lem *lem, int mod)
{
	t_link		*link;
	int			j;
	int			i;

	if (lem_null_par(lem, mod))
		return (-1);
	j = lem->n_r - 1;
	lem->link[j] = lem->end;
	link = lem->start->next;
	while (--j > 0)
	{
		if (!(link->sm = (int*)ft_memalloc(sizeof(int) * lem->n_r)))
			return (-1);
		lem->link[j] = link;
		link = link->next;
	}
	lem->link[j--] = lem->start;
	while (++j < lem->n_r - 1)
	{
		i = j;
		while (++i < lem->n_r)
			if (!ft_strcmp(lem->link[j]->name, lem->link[i]->name))
				return (-1);
	}
	return (graffiller(line, str, lem));
}

static int		command_analis(char **line, t_lem *lem, int mod)
{
	int			pr[2];
	char		*str;
	t_link		*link;

	if (!(ft_strcmp(line[0] + 2, "start")) && !lem->start->name)
		link = lem->start;
	else if (!(ft_strcmp(line[0] + 2, "end")) && !lem->end->name)
		link = lem->end;
	else
		return (0);
	ft_strdel(line);
	if ((lem->err = get_next_line(0, line)) == -1 || !lem->err)
		return (-1);
	if (mod == 1 && !(lem->oper = t_stradd(*line, lem->oper)))
		return (-1);
	str = ft_strchr(*line, ' ');
	if (!str || !(link->name = ft_strsub(*line, 0, str - *line)))
		return (-1);
	link->x = pratoi(&str, &pr[0]);
	link->y = pratoi(&str, &pr[1]);
	if (pr[0] == -1 || pr[1] == -1)
		return (-1);
	lem->n_r++;
	return (0);
}

static int		map_validator(char **line, t_lem *lem, int mod)
{
	char		*str;

	if (!**line || (mod == 1 && **line == 'L'))
		return ((mod == 1) ? -1 : 0);
	if (**line == 'L')
		return ((lem->oper = t_stradd(*line, lem->oper)) ? 0 : -1);
	if (**line == '#')
		lem->err = (*(line[0] + 1) == '#') ?\
				command_analis(line, lem, mod) : 0;
	else if (!lem->n_a)
	{
		str = *line;
		lem->n_a = pratoi(&str, &lem->err);
		return ((lem->err == -1 || *str) ? -1 : 0);
	}
	else if ((str = ft_strchr(line[0], '-')))
	{
		if (!lem->start->name || !lem->end->name)
			return (-1);
		lem->err = (!lem->link) ? grafcreater(*line, str, lem, mod) :\
										graffiller(*line, str, lem);
	}
	else
		lem->err = graffiller(*line, NULL, lem);
	return (lem->err);
}

int				argreader(t_lem *lem, int mod)
{
	char		*line;

	line = NULL;
	if (lem_null_par(lem, 0))
		return (-1);
	while ((lem->err = get_next_line(0, &line)))
	{
		if (lem->err == -1)
			return (ft_strerr(-1, &line));
		if (mod == 1 && !(lem->oper = t_stradd(line, lem->oper)))
			return (ft_strerr(-1, &line));
		if (map_validator(&line, lem, mod))
			return (ft_strerr(-1, &line));
		ft_strdel(&line);
	}
	if (!lem->link || (lem->start && !lem->start->n_l) ||\
						(lem->end && !lem->end->n_l))
		return (-1);
	return (0);
}
