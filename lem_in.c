/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:21:08 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/24 16:09:21 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int			main(int argc, char **argv)
{
	t_lem		lem;

	if (argc > 1 && argv)
		return (0);
	if (!(lem.err = argreader(&lem, 1)))
	{
		find_path(&lem, 0);
		if (lem.n_p < lem.n_r)
		{
			while (--lem.n_p >= 0)
				ft_masserr(0, &lem.link[lem.n_p]->path);
			lem.n_p = 0;
			find_path_all(&lem, 0);
		}
		if (!lem.n_p)
			lem.err = -1;
		else
			solution(&lem);
	}
	return (lem_err(lem.err, &lem));
}
