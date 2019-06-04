/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:48:59 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/24 15:32:58 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

int				main(int argc, char **argv)
{
	t_fdf		fdf;
	int			j;

	if (argc > 1 && argv)
		return (0);
	if (!(fdf.err = argreader(&fdf.lem, 2)))
	{
		j = -1;
		fdf.h = 0;
		fdf.w = 0;
		while (++j < fdf.lem.n_r)
		{
			fdf.w = (fdf.lem.link[j]->x > fdf.w) ? fdf.lem.link[j]->x : fdf.w;
			fdf.h = (fdf.lem.link[j]->y > fdf.h) ? fdf.lem.link[j]->y : fdf.h;
		}
		fdf.mlx = mlx_init();
		null_params(&fdf, 0);
		put_img(&fdf);
		mlx_loop(fdf.mlx);
	}
	return (lem_err(fdf.err, &fdf.lem));
}
