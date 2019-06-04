# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:26:35 by jwinthei          #+#    #+#              #
#    Updated: 2019/04/25 15:51:04 by jwinthei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
VISU = visu_hex
LIBN = libft.a
MLXN = mlx.a

SRC  = lem_func.c lem_func_2.c link_func.c str_func.c
SRC1 = lem_in.c $(SRC) find_path.c solution.c intersection.c
SRC2 = visu.c   $(SRC) inp_keyboard.c inp_mouse.c inp_params.c img_params.c put_image.c\
	   draw_line.c draw_circle.c ant.c room.c

INCL = libft/includes/
LIB  = libft/
MLX  = minilibx_macos/

FLG  = -Wall -Wextra -Werror
FRAEM= -framework OpenGL -framework AppKit
CFLAGS=-O3 -I $(INCL) -I $(MLX) $(FLG) 

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(MLXN) $(LIBN) $(NAME) $(VISU)

$(LIBN): $(LIB)*.c
	@make -C $(LIB)

$(MLXN): $(MLX)*.c
	@make -C $(MLX)

$(NAME): $(LIB)*.c $(MLX)*.c $(OBJ1)
	gcc -O2 -o $(NAME) $(OBJ1) $(CFLAGS) -L $(LIB) -lft

$(VISU): $(LIB)*.c $(MLX)*.c $(OBJ2)
	gcc -O2 -o $(VISU) $(OBJ2) $(CFALGS) -L $(LIB) -lft -L $(MLX) -lmlx $(FRAEM)

clean:
	rm -f *.o
	rm -f $(MLX)*.o
	make -C $(LIB) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(VISU)
	make -C $(LIB) fclean
	make -C $(MLX) clean

re: fclean all
