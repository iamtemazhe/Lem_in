/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:47:19 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/17 13:35:26 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcsub(const char *s, unsigned int start, size_t len,\
															int c)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (!(i = ft_strlen(&s[start])))
		len = 0;
	else if (len > i)
		len = i;
	if (!(str = (char*)malloc(sizeof(*str) *\
					(len + 1 + ((c) ? 1 : 0)))))
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	if (c)
		str[i++] = (unsigned char)c;
	str[i] = '\0';
	return (str);
}
