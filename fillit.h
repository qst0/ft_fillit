/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:58:12 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/05 17:13:57 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef unsigned long long t_ull;

typedef enum	e_minotype
{
	LINE_V,
	LINE_H,
	L_DOWN,
	T_DOWN,
	J_DOWN,
	SQUARE,
	J_RIGHT,
	Z_H,
	L_LEFT,
	T_RIGHT,
	J_UP,
	L_RIGHT,
	S_V,
	S_H,
	T_UP,
	Z_V,
	T_LEFT,
	L_UP,
	J_LEFT,
	END
}				t_minotype;

typedef struct	s_minos
{
	t_minotype		type;
	unsigned int	width_index:2;
	unsigned int	height_index:2;
	t_ull			stamp;
}				t_minos;

t_minos			g_minos[20] = {
	{LINE_V, 0, 3, 0x8000800080008000},
	{LINE_H, 3, 0, 0xF000000000000000},
	{L_DOWN, 2, 1, 0xE000800000000000},
	{T_DOWN, 2, 1, 0xE000400000000000},
	{J_DOWN, 2, 1, 0xE000200000000000},
	{SQUARE, 1, 1, 0xC000C00000000000},
	{J_RIGHT, 1, 2, 0xC000800080000000},
	{Z_H, 2, 1, 0xC000600000000000},
	{L_LEFT, 1, 2, 0xC000400040000000},
	{T_RIGHT, 1, 2, 0x8000C00080000000},
	{J_UP, 2, 1, 0x8000E00000000000},
	{L_RIGHT, 1, 2, 0x80008000C0000000},
	{S_V, 1, 2, 0x8000C00040000000},
	{S_H, 2, 1, 0x6000C00000000000},
	{T_UP, 2, 1, 0x4000E00000000000},
	{Z_V, 1, 2, 0x4000C00080000000},
	{T_LEFT, 1, 2, 0x4000C00040000000},
	{L_UP, 2, 1, 0x2000E00000000000},
	{J_LEFT, 1, 2, 0x40004000C0000000},
	{END, 0, 0, 0}
};

#endif
