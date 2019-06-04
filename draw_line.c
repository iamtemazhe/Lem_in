/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:12:04 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/10 17:07:46 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void		ant_pos(t_fdf fdf, t_line line, int mod)
{
	int			len;
	int			rez;

	if (mod < 2)
		return ;
	line.dx = ft_abs(line.pix.x - line.pix0.x);
	line.dy = ft_abs(line.pix.y - line.pix0.y);
	rez = line.dx * line.dx + line.dy * line.dy;
	len = sqrt(rez) + 0.5;
	rez = (line.len) ? (len * fdf.ant.speed) / line.len : 0;
	if (line.len && (rez <= fdf.ant.i &&\
		fdf.ant.i < rez + fdf.ant.speed * 0.009) &&\
		(fdf.ant.speed * 0.05 < fdf.ant.i &&\
		fdf.ant.i < fdf.ant.speed * 0.95))
		ant_body(fdf, line, rez % 11);
}

static void		calc_line_param(t_fdf fdf, t_line *line, int mod)
{
	line->err = 0;
	if (mod)
	{
		rotate_img(fdf, &line->pix0.x, &line->pix0.y, &line->pix0.z);
		rotate_img(fdf, &line->pix1.x, &line->pix1.y, &line->pix1.z);
		proect_iso_par(fdf, &line->pix0.x, &line->pix0.y, &line->pix0.z);
		proect_iso_par(fdf, &line->pix1.x, &line->pix1.y, &line->pix1.z);
		line->pix0.x += fdf.img.w / 2 + fdf.img.mvx;
		line->pix1.x += fdf.img.w / 2 + fdf.img.mvx;
		line->pix0.y += fdf.img.h / 2 + fdf.img.mvy;
		line->pix1.y += fdf.img.h / 2 + fdf.img.mvy;
	}
	line->mod = (line->pix0.x == line->pix1.x ||\
				line->pix0.y == line->pix1.y) ? 1 : 0;
	line->dx = ft_abs(line->pix1.x - line->pix0.x);
	line->dy = ft_abs(line->pix1.y - line->pix0.y);
	line->dirx = (line->pix1.x - line->pix0.x >= 0) ? 1 : -1;
	line->diry = (line->pix1.y - line->pix0.y >= 0) ? 1 : -1;
	line->pix.x = line->pix0.x;
	line->pix.y = line->pix0.y;
	line->pix.z = line->pix0.z;
	line->pix.col = line->pix0.col;
	line->len = sqrt(line->dx * line->dx + line->dy * line->dy);
}

void			draw_line(t_fdf fdf, t_line line, int mod)
{
	calc_line_param(fdf, &line, mod);
	while (1)
	{
		if (line.pix.x == line.pix1.x && line.pix.y == line.pix1.y)
			break ;
		line.pix.col = get_color(line);
		ant_pos(fdf, line, mod);
		if ((0 <= line.pix.x && line.pix.x < fdf.img.w) &&\
			(0 <= line.pix.y && line.pix.y < fdf.img.h))
			fdf.img.cp[line.pix.x + (fdf.img.w * line.pix.y)] = line.pix.col;
		if (line.dy > line.dx)
		{
			line.err += line.dx;
			line.pix.x += (2 * line.err >= line.dy) ? line.dirx : 0;
			line.err -= (2 * line.err >= line.dy) ? line.dy : 0;
			line.pix.y += line.diry;
		}
		else
		{
			line.err += line.dy;
			line.pix.y += (2 * line.err >= line.dx) ? line.diry : 0;
			line.err -= (2 * line.err >= line.dx) ? line.dx : 0;
			line.pix.x += line.dirx;
		}
	}
}
