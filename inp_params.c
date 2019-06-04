/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:15:44 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/17 16:51:36 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static int		close_win(t_fdf *fdf)
{
	exit(lem_err(0, &fdf->lem));
	return (0);
}

static int		generic(t_fdf *fdf)
{
	if (fdf->mod & ANI)
		put_img(fdf);
	return (0);
}

static void		null_params_0(t_fdf *fdf)
{
	fdf->mod = MCOL;
	fdf->line.col = 1;
	fdf->img.proec = 0;
	fdf->circle.col = 0x6600;
	fdf->ant.i = 0;
	fdf->ant.idle = 0;
	fdf->lem.link[0]->ant = fdf->lem.n_a;
	fdf->win.w = WEIGHT;
	fdf->win.h = HEIGHT;
	fdf->menu.w = fdf->win.w;
	fdf->menu.h = fdf->win.h / 15;
	fdf->img.w = fdf->win.w;
	fdf->img.h = fdf->win.h - 2 * fdf->menu.h;
	fdf->win.p = mlx_new_window(fdf->mlx, fdf->win.w, fdf->win.h, "Lem_in");
	fdf->menu.p = mlx_new_image(fdf->mlx, fdf->menu.w, fdf->menu.h);
	fdf->menu.cp = (int*)mlx_get_data_addr(fdf->menu.p, &fdf->menu.bpp,\
										&fdf->menu.ls, &fdf->menu.end);
	fdf->img.p = mlx_new_image(fdf->mlx, fdf->img.w, fdf->img.h);
	fdf->img.cp = (int*)mlx_get_data_addr(fdf->img.p, &fdf->img.bpp,\
										&fdf->img.ls, &fdf->img.end);
	mlx_hook(fdf->win.p, 2, 0, &keyboard_press, fdf);
	mlx_hook(fdf->win.p, 4, 0, &mouse_press, fdf);
	mlx_hook(fdf->win.p, 5, 0, &mouse_release, fdf);
	mlx_hook(fdf->win.p, 17, 0, &close_win, fdf);
	mlx_loop_hook(fdf->mlx, &generic, fdf);
}

void			null_params(t_fdf *fdf, int mod)
{
	if (!mod)
		null_params_0(fdf);
	if (0 <= mod && mod < 2)
	{
		fdf->img.zoom = 1;
		fdf->ant.speed = 100;
		fdf->circle.rad_step = 0;
		fdf->img.step = (fdf->w) ? fdf->win.w / (3 * fdf->w) : 1;
		if (fdf->h > fdf->w)
			fdf->img.step = fdf->win.h / (2 * fdf->h);
		fdf->img.step = (fdf->img.step) ? fdf->img.step : 1;
	}
	if (0 <= mod && mod < 3)
	{
		fdf->img.alpha = 0;
		fdf->img.betta = 0;
		fdf->img.gamma = 0;
		fdf->img.mvx = 0;
		fdf->img.mvy = 0;
	}
}
