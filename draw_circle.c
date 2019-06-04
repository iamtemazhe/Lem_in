/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:05:10 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/10 17:08:20 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void		calc_circle_param(t_fdf fdf, t_circle *circle, int mod)
{
	circle->err = 0;
	if (mod)
	{
		rotate_img(fdf, &circle->pix0.x, &circle->pix0.y, &circle->pix0.z);
		proect_iso_par(fdf, &circle->pix0.x, &circle->pix0.y, &circle->pix0.z);
		circle->pix0.x += fdf.img.w / 2 + fdf.img.mvx;
		circle->pix0.y += fdf.img.h / 2 + fdf.img.mvy;
	}
	circle->dr = 1 - 2 * fdf.circle.rad;
	circle->pix1.x = 0;
	circle->pix1.y = fdf.circle.rad;
}

static void		put_pix(t_fdf fdf, t_circle circle, int y)
{
	int			x;

	x = circle.pix0.x + circle.pix1.x;
	if (0 <= x && x < fdf.img.w && 0 <= y && y < fdf.img.h)
		fdf.img.cp[x + fdf.img.w * y] = circle.pix1.col;
	x = circle.pix0.x - circle.pix1.x;
	if (0 <= x && x < fdf.img.w && 0 <= y && y < fdf.img.h)
		fdf.img.cp[x + fdf.img.w * y] = circle.pix1.col;
	if (!(circle.dr < 0 && circle.err <= 0))
		while (++x < circle.pix0.x + circle.pix1.x)
			if (0 <= x && x < fdf.img.w && 0 <= y && y < fdf.img.h)
				fdf.img.cp[x + fdf.img.w * y] = circle.pix0.col;
}

void			draw_circle(t_fdf fdf, t_circle circle, int mod)
{
	calc_circle_param(fdf, &circle, mod);
	while (circle.pix1.y >= 0)
	{
		put_pix(fdf, circle, circle.pix0.y + circle.pix1.y);
		put_pix(fdf, circle, circle.pix0.y - circle.pix1.y);
		circle.err = 2 * (circle.dr + circle.pix1.y) - 1;
		if (circle.dr < 0 && circle.err <= 0)
			circle.dr += 2 * (++circle.pix1.x) + 1;
		else if (circle.dr > 0 && circle.err > 0)
			circle.dr -= 2 * (--circle.pix1.y) + 1;
		else
			circle.dr += 2 * (++circle.pix1.x - circle.pix1.y--);
	}
}

void			circle_color(t_fdf fdf, t_circle *circle, long i)
{
	if (!i || i == fdf.lem.n_r - 1)
	{
		circle->pix0.col = (!i) ? 0xcc00 : 0xff3300;
		circle->pix1.col = (!i) ? 0xffffff : 0xffffff;
		return ;
	}
	circle->pix1.col = 0x9900ff;
	if (!fdf.lem.link[i]->ant)
		circle->pix0.col = 0;
	else if (fdf.mod & MCOL)
		circle->pix0.col = 0x006600 + (fdf.lem.link[i]->ant && 1) * 0xac66 +\
														fdf.line.col;
	else if (fdf.mod & MONOC)
		circle->pix0.col = 0x006600 + fdf.line.col;
}
