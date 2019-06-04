/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:21:19 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/17 14:30:35 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(size_t nbr)
{
	size_t		i;

	i = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			i;
	char		sign;
	size_t		nbr;
	char		*str;

	sign = 0;
	if (n < 0)
	{
		nbr = -n;
		sign = 1;
	}
	else
		nbr = n;
	i = ft_nbrlen(nbr) + sign;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (--i >= sign)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
