/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrealloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:20:00 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/17 13:32:44 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcrealloc(char *dst, const char *src, size_t n,\
															int c)
{
	char	*sub;
	char	*tmp;

	if (!src && !dst && !n)
		return (NULL);
	if (!src && !dst && n)
		return (dst = ft_strnew(n + ((c) ? 1 : 0)));
	if (!src && dst)
		return (dst);
	if (!(sub = ft_strcsub(src, 0, n, c)))
		return (NULL);
	if (!dst)
		return (sub);
	if (!(tmp = ft_strjoin(dst, sub)))
		return (NULL);
	free(dst);
	free(sub);
	return (tmp);
}
