/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:58:12 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/05 17:14:46 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>

typedef unsigned long long t_ull;

typedef enum	e_minotype
{
	LINE_V = 0,
	LINE_H = 1,
	L_DOWN = 2,
	T_DOWN = 3,
	J_DOWN = 4,
	SQUARE = 5,
	J_RIGHT = 6,
	Z_H = 7,
	L_LEFT = 8,
	T_RIGHT = 9,
	J_UP = 10,
	L_RIGHT = 11,
	S_V = 12,
	S_H = 13,
	T_UP = 14,
	Z_V = 15,
	T_LEFT = 16,
	L_UP = 17,
	J_LEFT = 18,
	END = 19
}				t_minotype;

typedef struct	s_mino
{
	t_minotype	type;
	uint8_t		width_offset:3;
	uint8_t		added_blanks:2;
	uint8_t		placed:1;
	t_ull		stamp;
}				t_mino;

t_mino			g_all_minos[20] = {
	{LINE_V, 1, 0, 0, 0x8000800080008000},
	{LINE_H, 4, 0, 0, 0xF000000000000000},
	{L_DOWN, 3, 0, 0, 0xE000800000000000},
	{T_DOWN, 3, 0, 0, 0xE000400000000000},
	{J_DOWN, 3, 0, 0, 0xE000200000000000},
	{SQUARE, 2, 0, 0, 0xC000C00000000000},
	{J_RIGHT, 2, 0, 0, 0xC000800080000000},
	{Z_H, 2, 0, 0, 0xC000600000000000},
	{L_LEFT, 2, 0, 0, 0xC000400040000000},
	{T_RIGHT, 1, 0, 0, 0x8000C00080000000},
	{J_UP, 1, 0, 0, 0x8000E00000000000},
	{L_RIGHT, 1, 0, 0, 0x80008000C0000000},
	{S_V, 1, 0, 0, 0x8000C00040000000},
	{S_H, 3, 1, 0, 0x6000C00000000000},
	{T_UP, 2, 1, 0, 0x4000E00000000000},
	{Z_V, 2, 1, 0, 0x4000C00080000000},
	{T_LEFT, 2, 1, 0, 0x4000C00040000000},
	{L_UP, 3, 2, 0, 0x2000E00000000000},
	{J_LEFT, 2, 1, 0, 0x40004000C0000000},
	{END, 0, 0, 0, 0}
};

extern t_mino	*g_minos;
extern t_ull	*g_grid;

#endif
