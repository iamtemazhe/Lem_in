/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:55:44 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/10 17:09:19 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void		put_back(t_fdf *fdf)
{
	int			razm;

	ft_bzero(fdf->menu.cp, fdf->menu.w * fdf->menu.h * sizeof(int));
	razm = fdf->menu.h * fdf->menu.w;
	while (--razm >= 0)
		fdf->menu.cp[razm] = 0x006600 + fdf->line.col;
	mlx_put_image_to_window(fdf->mlx, fdf->win.p, fdf->menu.p, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win.p, fdf->menu.p, 0,\
												fdf->win.h - fdf->menu.h);
}

static void		put_submenu(t_fdf fdf, int col)
{
	fdf.menu.w = fdf.win.w * 0.9;
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h, col,\
														"Colors: [ | ]");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 30, col,\
															"Color mode:");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 60, col,\
																"Mono  - M");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 90, col,\
																"Color - C");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 120, col,\
																"Proections:");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 150, col,\
																"None  - O");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 180, col,\
																"ISO   - I");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 210, col,\
																"Persp - P");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 240, col,\
														"Animation: S");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 270, col,\
														"Auto mode: A");
}

static void		put_menu(t_fdf fdf)
{
	int			col;

	fdf.menu.w = fdf.win.w * 0.03;
	col = 0x006600 + fdf.line.col;
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h, col,\
									"Move: < | ^ | \\/ | > | mouse left");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 30, col,\
											"Zoom: + | - | mouse scroll");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 60, col,\
											"Rotate x: 8 | 2 | mouse left");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 90, col,\
											"Rotate y: 4 | 6 | mouse left");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 120, col,\
										"Rotate z: 7 | 9 | mouse middle");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 150, col,\
											"Restore default position: 5");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 180, col,\
										"Room's & ant's size: - | + (main)");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 210, col,\
													"Ant's speed: ( | )");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 240, col,\
													"Restore defaults: R");
	mlx_string_put(fdf.mlx, fdf.win.p, fdf.menu.w, fdf.menu.h + 270, col,\
										"Change step: backspace | space");
	put_submenu(fdf, col);
}

static void		put_names(t_fdf fdf)
{
	int			x;
	int			y;
	int			z;
	long		i;

	i = -1;
	while (++i < fdf.lem.n_r)
	{
		y = fdf.lem.link[i]->y * fdf.img.step - fdf.img.hp;
		x = fdf.lem.link[i]->x * fdf.img.step - fdf.img.wp;
		z = fdf.img.zoom;
		circle_color(fdf, &fdf.circle, i);
		fdf.circle.pix1.z *= fdf.circle.rad / 0x7f;
		rotate_img(fdf, &x, &y, &z);
		if (fdf.img.proec)
			proect_iso_par(fdf, &x, &y, &z);
		x += fdf.img.w / 2 + fdf.img.mvx - ft_strlen(fdf.lem.link[i]->name) * 5;
		y += fdf.img.h / 2 + fdf.img.mvy - fdf.circle.rad + fdf.menu.h -\
																fdf.win.h / 35;
		mlx_string_put(fdf.mlx, fdf.win.p, x, y,\
					fdf.circle.pix1.col, fdf.lem.link[i]->name);
	}
}

void			put_img(t_fdf *fdf)
{
	if (fdf->mod & ANI)
	{
		fdf->ant.i += (fdf->ant.i < fdf->ant.speed) ? 1 : 0;
		fdf->ant.idle = (fdf->ant.idle < fdf->ant.speed / 2) ?\
											fdf->ant.idle + 1 : 0;
		if (fdf->mod & ANIR && fdf->ant.i == fdf->ant.speed)
			operalis(49, fdf);
		if (!fdf->lem.cur_op)
			fdf->mod -= (fdf->mod & ANIR) ? ANIR : 0;
	}
	else
	{
		fdf->ant.i = fdf->ant.speed;
		fdf->ant.idle = 0;
	}
	fdf->circle.rad = 7 * fdf->img.step / 12 + fdf->circle.rad_step;
	fdf->img.wp = fdf->img.step * (fdf->w - 1) / 2;
	fdf->img.hp = fdf->img.step * (fdf->h - 1) / 2;
	ft_bzero(fdf->img.cp, fdf->img.w * fdf->img.h * sizeof(int));
	room_maker(*fdf);
	put_back(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win.p, fdf->img.p, 0, fdf->menu.h);
	put_names(*fdf);
	put_menu(*fdf);
}
