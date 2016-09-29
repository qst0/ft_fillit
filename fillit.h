/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:58:12 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/28 16:58:12 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef enum	e_minotype
{
	SQUARE,
	LINE_V,
	LINE_H,
	T_UP,
	T_LEFT,
	T_DOWN,
	T_RIGHT,
	L_DOWN,
	L_LEFT,
	L_UP,
	L_RIGHT,
	RL_DOWN,
	RL_LEFT,
	RL_UP,
	RL_RIGHT,
	S_H,
	S_V,
	Z_H,
	Z_V
}				t_minotype;

typedef struct	s_blank
{
	unsigned int	row:2;
	unsigned int	col:2;
}				t_blank;

typedef struct	s_minos
{
	t_minotype		minotype;
	unsigned int	width_index:2;
	unsigned int	height_index:2;
	t_blank			blanks[2];
}				t_minos;

t_minos			*g_minos = {
	{SQUARE, 1, 1, {0, 0}},
	{LINE_V, 0, 3, {0, 0}},
	{LINE_H, 3, 0, {0, 0}},
	{T_UP, 2, 1, {{0, 0}, {0, 2}}},
	{T_LEFT, 1, 2, {{0, 0}, {2, 0}}},
	{T_DOWN, 2, 1, {{1, 0}, {1, 2}}},
	{T_RIGHT, 1, 2, {{0, 1}, {2, 1}}},
	{L_DOWN, 2, 1, {{1, 1}, {1, 2}}},
	{L_LEFT, 1, 2, {{1, 0}, {2, 0}}},
	{L_UP, 2, 1, {{0, 0}, {0, 1}}},
	{L_RIGHT, 1, 2, {{0, 1}, {1, 1}}},
	{RL_DOWN, 2, 1, {{1, 0}, {1, 1}}},
	{RL_LEFT, 1, 2, {{0, 0}, {1, 0}}},
	{RL_UP, 2, 1, {{0, 1}, {0, 2}}},
	{RL_RIGHT, 1, 2, {{1, 1}, {1, 2}}},
	{S_H, 2, 1, {{0, 0}, {1, 2}}},
	{S_V, 1, 2, {{0, 1}, {2, 0}}},
	{Z_H, 2, 1, {{1, 0}, {0, 2}}},
	{Z_V, 1, 2, {{0, 0}, {2, 1}}},
	0
}

#endif
