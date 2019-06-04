/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:04:40 by jwinthei          #+#    #+#             */
/*   Updated: 2019/04/09 16:11:39 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include "mlx.h"
# include "lem_in.h"

# define ISO     0x1
# define PAR     0x2
# define MCOL    0x1
# define MONOC   0x2
# define ANI     0x4
# define ANIR    0x8

# define WEIGHT  2560
# define HEIGHT  1395

typedef struct		s_ant
{
	int				i;
	int				idle;
	int				speed;
}					t_ant;

typedef struct		s_pix
{
	int				x;
	int				y;
	int				z;
	int				col;
}					t_pix;

typedef struct		s_circle
{
	t_pix			pix;
	t_pix			pix0;
	t_pix			pix1;
	int				rad;
	int				rad_step;
	int				err;
	int				dr;
	int				col;
}					t_circle;

typedef struct		s_line
{
	t_pix			pix;
	t_pix			pix0;
	t_pix			pix1;
	int				err;
	int				mod;
	int				dx;
	int				dy;
	int				dirx;
	int				diry;
	int				col;
	int				len;
}					t_line;

typedef struct		s_mouse
{
	int				mvx;
	int				mvy;
	long double		rotx;
	long double		roty;
	long double		rota;
	long double		rotb;
	long double		rotz;
}					t_mouse;

typedef struct		s_img
{
	void			*p;
	int				*cp;
	int				bpp;
	int				ls;
	int				end;
	int				w;
	int				h;
	int				wp;
	int				hp;
	int				mvx;
	int				mvy;
	int				step;
	int				zoom;
	int				proec;
	int				rot;
	long double		alpha;
	long double		betta;
	long double		gamma;
}					t_img;

typedef struct		s_win
{
	void			*p;
	int				w;
	int				h;
}					t_win;

typedef struct		s_fdf
{
	t_ant			ant;
	t_lem			lem;
	t_circle		circle;
	t_line			line;
	t_img			img;
	t_img			menu;
	t_win			win;
	t_mouse			mouse;
	void			*mlx;
	int				w;
	int				h;
	int				mod;
	int				maxz;
	int				*map;
	int				*map_col;
	int				err;
}					t_fdf;

void				draw_circle(t_fdf fdf, t_circle circle, int mod);
void				draw_line(t_fdf fdf, t_line line, int mod);
void				ant_body(t_fdf fdf, t_line line, int rez);
void				ant_seg(t_fdf fdf, int x, int y);
void				operalis(int keycode, t_fdf *fdf);
void				circle_color(t_fdf fdf, t_circle *circle, long i);
void				room_maker(t_fdf fdf);
void				put_img(t_fdf *fdf);
void				null_params(t_fdf *fdf, int mod);
void				rotate_img(t_fdf fdf, int *x, int *y, int *z);
void				proect_iso_par(t_fdf fdf, int *x, int *y, int *z);

int					get_color(t_line line);
int					keyboard_press(int keycode, t_fdf *fdf);
int					mouse_move(int x, int y, t_fdf *fdf);
int					mouse_press(int keycode, int x, int y, t_fdf *fdf);
int					mouse_release(int keycode, int x, int y, t_fdf *fdf);
#endif
