/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:13:52 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/23 18:35:41 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static char		*null_operalis(int keycode, t_fdf *fdf)
{
	int			i;

	if (!fdf->lem.oper)
		return (0);
	if (!fdf->lem.cur_op && keycode == 49)
		fdf->lem.cur_op = fdf->lem.oper->prev;
	else if ((!fdf->lem.cur_op && keycode == 51) ||\
			(keycode == 51 && fdf->lem.cur_op == fdf->lem.oper->prev) ||\
			(keycode == 49 && fdf->lem.cur_op == fdf->lem.oper))
		fdf->lem.cur_op = NULL;
	else if (keycode == 49)
		fdf->lem.cur_op = fdf->lem.cur_op->prev;
	else if (keycode == 51)
		fdf->lem.cur_op = fdf->lem.cur_op->next;
	fdf->ant.i = 0;
	i = -1;
	while (++i < fdf->lem.n_r)
		fdf->lem.link[i]->prant = (fdf->lem.link[i]->ant) ?\
									fdf->lem.link[i]->ant : 0;
	while (--i)
		fdf->lem.link[i]->ant = 0;
	if (!fdf->lem.cur_op)
		fdf->lem.link[0]->ant = fdf->lem.n_a;
	return ((!fdf->lem.cur_op) ? NULL : fdf->lem.cur_op->str);
}

void			operalis(int keycode, t_fdf *fdf)
{
	int			i;
	int			ant;
	int			len;
	char		*str;
	char		*str1;

	if (!(str = null_operalis(keycode, fdf)))
		return ;
	while (*str)
	{
		str = ft_strchr(str, 'L');
		ant = ft_atoi(++str);
		str = ft_strchr(str, '-');
		if (!(str1 = ft_strchr(++str, ' ')))
			str1 = ft_strchr(str, 0);
		i = -1;
		while (++i < fdf->lem.n_r)
			if (!ft_strncmp(fdf->lem.link[i]->name, str,\
				((len = ft_strlen(fdf->lem.link[i]->name)) > str1 - str) ?\
															len : str1 - str))
				break ;
		str = str1;
		fdf->lem.link[i]->ant = (!i) ? 0 : ant;
	}
	fdf->lem.link[0]->ant -= (fdf->lem.link[0]->ant > 0) ? 1 : 0;
}

static int		keyboard_press_3(int keycode, t_fdf *fdf)
{
	if (keycode == 27)
		fdf->circle.rad_step -= (ft_abs(fdf->img.step / 2 +\
								fdf->circle.rad_step) > 1) ? 1 : 0;
	else if (keycode == 24)
		fdf->circle.rad_step += 1;
	else if (keycode == 49 || keycode == 51)
		operalis(keycode, fdf);
	else if (keycode == 0)
		fdf->mod = (fdf->mod & ANIR) ? fdf->mod - ANIR : fdf->mod | ANIR;
	else if (keycode == 1)
		fdf->mod = (fdf->mod & ANI) ? fdf->mod - ANI : fdf->mod | ANI;
	else if (keycode == 25)
		fdf->ant.speed += (fdf->ant.speed < 1000) ? 50 : 0;
	else if (keycode == 29)
		fdf->ant.speed -= (fdf->ant.speed >= 100) ? 50 : 0;
	if (keycode == 25 || keycode == 29)
		fdf->ant.i = 0;
	return (0);
}

static int		keyboard_press_2(int keycode, t_fdf *fdf)
{
	if (keycode == 86 || keycode == 88)
		fdf->img.alpha += (keycode == 88) ? M_PI / 45.0 : -M_PI / 45.0;
	else if (keycode == 91 || keycode == 84)
		fdf->img.betta += (keycode == 84) ? M_PI / 45.0 : -M_PI / 45.0;
	else if (keycode == 92 || keycode == 89)
		fdf->img.gamma += (keycode == 92) ? M_PI / 45.0 : -M_PI / 45.0;
	else if (keycode == 75)
		fdf->img.zoom -= (fdf->img.zoom > 1) ? 1 : 0;
	else if (keycode == 67)
		fdf->img.zoom += 1;
	else if (keycode == 124 || keycode == 123)
		fdf->img.mvx = (keycode == 123) ? fdf->img.mvx - 4 : fdf->img.mvx + 4;
	else if (keycode == 126 || keycode == 125)
		fdf->img.mvy = (keycode == 126) ? fdf->img.mvy - 4 : fdf->img.mvy + 4;
	else if (keycode == 31)
		fdf->img.proec = 0;
	else if (keycode == 34)
		fdf->img.proec = ISO;
	else if (keycode == 35)
		fdf->img.proec = PAR;
	else
		keyboard_press_3(keycode, fdf);
	return (0);
}

int				keyboard_press(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		exit(ft_masserr(0, &fdf->map) + ft_masserr(0, &fdf->map_col));
	else if (keycode == 87)
		null_params(fdf, 2);
	else if (keycode == 15)
		null_params(fdf, 1);
	else if (keycode == 46)
		fdf->mod = (fdf->mod & ANI) ? ANI | MONOC : MONOC;
	else if (keycode == 8)
		fdf->mod = (fdf->mod & ANI) ? ANI | MCOL : MCOL;
	else if (keycode == 33)
		fdf->line.col -= (fdf->line.col > 0xfffff) ? 0xff300 : 0;
	else if (keycode == 30)
		fdf->line.col += 0xff300;
	else if (keycode == 78)
		fdf->img.step -= (fdf->img.step - 3 >= 1) ? 3 : 0;
	else if (keycode == 69)
		fdf->img.step += 3;
	else
		keyboard_press_2(keycode, fdf);
	put_img(fdf);
	return (0);
}
