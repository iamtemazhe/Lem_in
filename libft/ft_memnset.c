/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memnset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:48:48 by hgysella          #+#    #+#             */
/*   Updated: 2019/04/16 16:17:09 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memnset(void *dst, int c, size_t nc, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (nc == 1)
			((unsigned char*)dst)[i] = (unsigned char)c;
		else if (nc == 2)
			((unsigned short int*)dst)[i] = (unsigned short int)c;
		else if (nc == 4)
			((unsigned int*)dst)[i] = (unsigned int)c;
	}
	return (dst);
}
