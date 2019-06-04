/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:07:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/23 20:03:07 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void			ant_seg(t_fdf fdf, int x, int y)
{
	fdf.circle.pix0.x = x;
	fdf.circle.pix0.y = y;
	if (!((0 <= x && x < fdf.img.w) && (0 <= y && y < fdf.img.h)))
		return ;
	draw_circle(fdf, fdf.circle, 0);
}

static void		pix_color(t_fdf fdf, t_line *line, int ant)
{
	if (fdf.mod & MCOL)
	{
		line->pix0.col = 0x006600 + ant * 0xac66 + line->col;
		line->pix1.col = 0x006600 + ant * 0x6600ff + line->col;
	}
	else if (fdf.mod & MONOC)
	{
		line->pix0.col = 0x006600 + line->col;
		line->pix1.col = 0x006600 + line->col;
	}
}

static void		link_maker(t_fdf fdf, int i)
{
	int			j;

	j = i;
	fdf.line.pix0.y = fdf.lem.link[i]->y * fdf.img.step - fdf.img.hp;
	fdf.line.pix0.x = fdf.lem.link[i]->x * fdf.img.step - fdf.img.wp;
	while (++j < fdf.lem.n_r)
	{
		if (!fdf.lem.link[i]->sm[j])
			continue;
		fdf.line.pix0.z = fdf.img.zoom;
		fdf.line.pix1.z = fdf.img.zoom;
		fdf.line.pix1.y = fdf.lem.link[j]->y * fdf.img.step - fdf.img.hp;
		fdf.line.pix1.x = fdf.lem.link[j]->x * fdf.img.step - fdf.img.wp;
		pix_color(fdf, &fdf.line, (((!i && fdf.lem.link[j]->ant) ||\
			(i && fdf.lem.link[j]->ant == fdf.lem.link[i]->prant) ||\
			(j == fdf.lem.n_r - 1 && fdf.lem.link[i]->prant)) &&\
			fdf.lem.link[j]->ant));
		fdf.line.pix0.z *= fdf.img.step / 0x7f;
		fdf.line.pix1.z *= fdf.img.step / 0x7f;
		draw_line(fdf, fdf.line, (((!i && fdf.lem.link[j]->ant) ||\
			(i && fdf.lem.link[j]->ant == fdf.lem.link[i]->prant) ||\
			(j == fdf.lem.n_r - 1 && fdf.lem.link[i]->prant)) &&\
			fdf.lem.link[j]->ant) ? 2 : 1);
	}
}

void			room_maker(t_fdf fdf)
{
	int			i;

	i = -1;
	while (++i < fdf.lem.n_r)
	{
		fdf.circle.pix0.y = fdf.lem.link[i]->y * fdf.img.step - fdf.img.hp;
		fdf.circle.pix0.x = fdf.lem.link[i]->x * fdf.img.step - fdf.img.wp;
		fdf.circle.pix1.z = fdf.img.zoom;
		circle_color(fdf, &fdf.circle, i);
		fdf.circle.pix1.z *= fdf.circle.rad / 0x7f;
		link_maker(fdf, i);
		draw_circle(fdf, fdf.circle, 1);
		if (!(fdf.lem.link[i]->ant && (!i || i == fdf.lem.n_r - 1 ||\
			(fdf.ant.speed * 0.95 <= fdf.ant.i && fdf.ant.i <= fdf.ant.speed))))
			continue ;
		fdf.line.pix.x = fdf.circle.pix0.x;
		fdf.line.pix.y = fdf.circle.pix0.y;
		fdf.line.pix.z = fdf.img.zoom;
		rotate_img(fdf, &fdf.line.pix.x, &fdf.line.pix.y, &fdf.line.pix.z);
		proect_iso_par(fdf, &fdf.line.pix.x, &fdf.line.pix.y, &fdf.line.pix.z);
		fdf.line.pix.x += fdf.img.w / 2 + fdf.img.mvx - 3 * fdf.circle.rad / 32;
		fdf.line.pix.y += fdf.img.h / 2 + fdf.img.mvy + fdf.circle.rad / 2;
		ant_body(fdf, fdf.line, (fdf.ant.idle < fdf.ant.speed / 4) ? 0 : 11);
	}
}
