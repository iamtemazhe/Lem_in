/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:59:50 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/10 16:35:50 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void		ant_leg(t_fdf fdf, int x, int y)
{
	if (!((0 <= x && x < fdf.img.w) && (0 <= y && y < fdf.img.h)))
		return ;
	fdf.line.pix0.x = x;
	fdf.line.pix0.y = y;
	draw_line(fdf, fdf.line, 0);
}

static void		ant_leg1(t_fdf fdf, int x, int y, int rez)
{
	int			rad;

	rad = fdf.circle.rad;
	fdf.line.pix1.x = x - ((rez < 6 || rez == 11) ? 0 : rad / 16);
	fdf.line.pix1.y = y + rad / 8;
	ant_leg(fdf, x, y);
	fdf.line.pix1.x = x - rad / 16;
	fdf.line.pix1.y = y + rad / 16;
	ant_leg(fdf, x - ((rez < 6 || rez == 11) ? 0 : rad / 16),\
										y + rad / 8);
	fdf.line.pix1.x = x - ((rez < 6 || rez == 11) ? 3 : 4) * rad / 16;
	fdf.line.pix1.y = y + rad / 4;
	ant_leg(fdf, x - rad / 16, y + rad / 16);
	fdf.line.pix1.y = y + ((rez < 6 || rez == 11) ? 5 : 4) * rad / 16;
	if (rez < 6 || rez == 11)
		ant_leg(fdf, x - 3 * rad / 16, y + rad / 4);
	fdf.line.pix1.x = x - 5 * rad / 16;
	ant_leg(fdf, x - ((rez < 6 || rez == 11) ? 3 : 4) * rad / 16,\
						y + ((rez < 6 || rez == 11) ? 5 : 4) * rad / 16);
}

static void		ant_leg2_3(t_fdf fdf, int x, int y, int rez)
{
	int			rad;

	rad = fdf.circle.rad;
	fdf.line.pix1.x = x - rad / 16;
	fdf.line.pix1.y = y - rad / 8;
	ant_leg(fdf, x, y);
	fdf.line.pix1.x = x - ((rez < 6 || rez == 11) ? 1 : 3) * rad / 16;
	fdf.line.pix1.y = y + ((rez < 6 || rez == 11) ? 4 : 3) * rad / 16;
	ant_leg(fdf, x - rad / 16, y - rad / 8);
	fdf.line.pix1.x = x - ((rez < 6 || rez == 11) ? 1 : 2) * rad / 8;
	ant_leg(fdf, x - ((rez < 6 || rez == 11) ? 1 : 3) * rad / 16,\
						y + ((rez < 6 || rez == 11) ? 4 : 3) * rad / 16);
	fdf.line.pix1.x = x + ((2 <= rez && rez <= 6) ? 1 : 3) * rad / 16;
	fdf.line.pix1.y = y - ((2 <= rez && rez <= 6) ? 3 : 2) * rad / 16;
	ant_leg(fdf, x, y);
	fdf.line.pix1.x = x + ((4 <= rez && rez <= 6) ? 3 : 6) * rad / 16;
	fdf.line.pix1.y = y + ((rez == 1) ? 1 : 2) * rad / 8;
	ant_leg(fdf, x + ((2 <= rez && rez <= 6) ? 1 : 3) * rad / 16,\
				y - ((2 <= rez && rez <= 6) ? 3 : 2) * rad / 16);
	fdf.line.pix1.x += rad / 8;
	ant_leg(fdf, x + ((4 <= rez && rez <= 6) ? 3 : 6) * rad / 16,\
				y + ((rez == 1) ? 1 : 2) * rad / 8);
}

static void		ant_face(t_fdf fdf, int x, int y, int rad)
{
	fdf.circle.rad = rad / 32;
	ant_seg(fdf, x - rad / 16, y - rad / 16);
	ant_seg(fdf, x + rad / 16, y - rad / 16);
	fdf.line.pix1.x = x - rad / 32;
	fdf.line.pix1.y = y + 3 * rad / 16;
	ant_leg(fdf, x - rad / 8, y);
	ant_leg(fdf, x - rad / 32, y + rad / 16);
	fdf.line.pix1.x = x + rad / 32;
	ant_leg(fdf, x + rad / 8, y);
	ant_leg(fdf, x + rad / 32, y + rad / 16);
	fdf.line.pix1.y = y + 25 * rad / 128;
	fdf.line.pix1.x = x - rad / 64;
	ant_leg(fdf, x - rad / 32, y + 3 * rad / 16);
	fdf.line.pix1.x = x + rad / 64;
	ant_leg(fdf, x + rad / 32, y + 3 * rad / 16);
	fdf.line.pix1.x = x + rad / 8;
	fdf.line.pix1.y = y - 3 * rad / 16;
	ant_leg(fdf, x, y - rad / 16);
	fdf.line.pix1.x = x - rad / 8;
	ant_leg(fdf, x, y - rad / 16);
	fdf.line.pix1.x = x - rad / 4;
	ant_leg(fdf, x - rad / 8, y - 3 * rad / 16);
	fdf.line.pix1.x = x + rad / 4;
	ant_leg(fdf, x + rad / 8, y - 3 * rad / 16);
}

void			ant_body(t_fdf fdf, t_line line, int rez)
{
	int			rad;

	fdf.circle.rad *= 1.75;
	rad = fdf.circle.rad;
	fdf.circle.pix0.col = 0x996600;
	fdf.circle.pix1.col = 0x663300;
	fdf.line.pix0.col = 0x663300;
	line.pix.y += (rez == 11) ? rad / 8 : 0;
	fdf.circle.rad = rad / 16;
	ant_seg(fdf, line.pix.x - rad / 16, line.pix.y - 3 * rad / 8);
	fdf.circle.rad = rad / 14;
	ant_seg(fdf, line.pix.x + rad / 16, line.pix.y - 5 * rad / 16);
	fdf.circle.rad = 3 * rad / 16;
	ant_seg(fdf, line.pix.x + 5 * rad / 16, line.pix.y - rad / 4);
	fdf.circle.rad = rad / 8;
	ant_seg(fdf, line.pix.x - rad / 4, line.pix.y - 3 * rad / 8);
	fdf.line.pix1.col = fdf.line.pix0.col;
	fdf.circle.pix0.col = fdf.circle.pix1.col;
	ant_face(fdf, line.pix.x - rad / 4, line.pix.y - 3 * rad / 8, rad);
	fdf.line.pix1.col = 0x996600;
	fdf.circle.rad = rad;
	line.pix.y -= (rez == 11) ? rad / 8 : 0;
	ant_leg1(fdf, line.pix.x - rad / 16, line.pix.y - 5 * rad / 16, rez);
	ant_leg2_3(fdf, line.pix.x + rad / 16, line.pix.y - 3.8 * rad / 16, rez);
}
