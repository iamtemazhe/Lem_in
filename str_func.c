/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:22:24 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/09 15:28:16 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static void		t_countn(t_str **str_p, int dir)
{
	t_str		*str_str;

	str_str = *str_p;
	while (1)
	{
		if (str_str->n == 1)
			break ;
		str_str = str_str->next;
	}
	if (dir)
		str_str->next->n += (str_str->next->n < 3) ? 0 : 1;
	else
		str_str->next->n -= (str_str->next->n < 3) ? 0 : 1;
}

void			t_strdel(t_str **str_p)
{
	t_str		*str_str;

	if (!(str_p && *str_p))
		return ;
	t_countn(str_p, 0);
	str_str = *str_p;
	str_str->prev->next = str_str->next;
	str_str->next->prev = str_str->prev;
	ft_strdel(&str_str->str);
	*str_p = (str_str->n > 1) ? str_str->next : NULL;
	free(str_str);
	str_str = NULL;
}

int				t_strerr(int retv, t_str **str_p)
{
	t_str		*str_tmp;

	if (!(str_p && *str_p))
		return (retv);
	while (1)
	{
		if (str_p[0]->n == 1)
		{
			t_strdel(str_p);
			break ;
		}
		str_tmp = str_p[0]->next;
		t_strdel(str_p);
		*str_p = str_tmp;
	}
	*str_p = NULL;
	return (retv);
}

t_str			*t_strnew(char *str, int n)
{
	t_str		*str_elem;

	if (!(str_elem = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	str_elem->next = str_elem;
	str_elem->n = n;
	str_elem->prev = str_elem;
	if (!(str_elem->str = ft_strdup(str)))
		return (NULL);
	return (str_elem);
}

t_str			*t_stradd(char *str, t_str *str_dst)
{
	t_str		*str_elem;

	if (!str_dst)
		return (str_dst = t_strnew(str, 1));
	if (!(str_elem = t_strnew(str, str_dst->n + 1)))
		return (NULL);
	if (str_dst->n == 1)
	{
		str_dst->next = str_elem;
		str_elem->prev = str_dst;
	}
	else
	{
		t_countn(&str_dst, 0);
		str_dst->prev->next = str_elem;
		str_elem->prev = str_dst->prev;
	}
	str_dst->prev = str_elem;
	str_elem->next = str_dst;
	str_dst = str_elem;
	return (str_dst);
}
