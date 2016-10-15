/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_mino.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 13:15:37 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/07 12:47:34 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define HEX 0x8000000000000000
#define GETB(z) ((g_grid[z / 64] << (z % 64) & HEX) == HEX)

#define CHECK1 (((mino->stamp >> (offset % 64)) & g_grid[offset / 64]) == 0)
#define GROSS ((offset + mino->total_offset) / 64)
#define CHECK2 (((mino->stamp << (64 - offset % 64)) & g_grid[GROSS]) == 0)

uint8_t		g_left_to_place;
uint8_t		g_sqr_size;
uint8_t		g_decode_index;
t_decode	*g_decodes;
t_ull		*g_grid;

t_ull		g_inits[13] = {
	0,
	0,
	0,
	0x1000100010001000,
	0x0800080008000800,
	0x0400040004000400,
	0x0200020002000200,
	0x0100010001000100,
	0x0080008000800080,
	0x0040004000400040,
	0x0020002000200020,
	0x0010001000100010,
	0x0008000800080008
};

int		attempt_place(int offset, t_mino *mino, uint8_t index)
{
	if (CHECK1 && CHECK2)
	{
		g_grid[offset / 64] |= mino->stamp >> (offset % 64);
		g_grid[GROSS] |= mino->stamp << (64 - offset % 64);
		mino->placed = 1;
		g_left_to_place--;
		g_decodes[g_decode_index].type = mino->type;
		g_decodes[g_decode_index].index = index;
		g_decodes[g_decode_index].offset = (offset / 16) * g_sqr_size
			+ offset % 16;
		g_decode_index++;
		if (g_left_to_place == 0 || backtrack(index + 1))
			return (1);
		else
		{
			g_grid[offset / 64] ^= mino->stamp >> (offset % 64);
			if (offset / 64 != GROSS)
				g_grid[GROSS] ^= mino->stamp << (64 - offset % 64);
			mino->placed = 0;
			g_left_to_place++;
			g_decode_index--;
		}

	}
	return (0);
}

/*
**	int		backtrack(int offset)
**	{
**		int		i;
**	
**		i = -1;
**		if (GETB(offset) && g_left_to_place > 0)
**		{
**			while (g_minos[++i].type != END)
**			{
**				if (g_minos[i].placed || !g_minos[i].added_blanks)
**					continue ;
**				if (attempt_place(offset, &g_minos[i], i))
**					return (1);
**			}
**			if (offset < (g_sqr_size - 1) * 16 + g_sqr_size)
**			{
**				if ((offset % 16 + 1) % g_sqr_size != 0)
**					return (backtrack(offset + 1));
**				else
**					return (backtrack(offset + (16 - g_sqr_size) + 1));
**			}
**		}
**		else if (g_left_to_place > 0)
**		{
**			while (g_minos[++i].type != END)
**			{
**				if (g_minos[i].placed)
**					continue ;
**				if (attempt_place(offset, &g_minos[i], i))
**					return (1);
**			}
**			if (offset < (g_sqr_size - 1) * 16 + g_sqr_size)
**			{
**				if ((offset % 16 + 1) % g_sqr_size != 0)
**					return (backtrack(offset + 1));
**				else
**					return (backtrack(offset + (16 - g_sqr_size) + 1));
**			}
**		}
**		else
**			return (1);
**		return (0);
**	}
*/

int		backtrack(int index)
{
	int		offset;

	offset = 0;
	while (offset < (g_sqr_size - 1) * 16 + g_sqr_size)
	{
		if ((!GETB(offset) || g_minos[index].added_blanks))
			if (attempt_place(offset, &g_minos[index], index))
				return (1);
		offset++;
		if ((offset % 16) % g_sqr_size == 0)
			offset += 16 - g_sqr_size;
	}
	return (0);
}

int		find_next_square(int nb)
{
	int i;

	i = 0;
	while (i <= 46340)
	{
		if (i * i >= nb)
			return (i);
		i++;
	}
	return (0);
}

void	fillit(void)
{
	int i;

	g_decodes = (t_decode*)malloc(sizeof(t_decode) * 26);
	i = -1;
	while (++i < 26)
		g_decodes[i].type = END;
	g_sqr_size = find_next_square(g_left_to_place * 4);
	i = -1;
	g_grid = (t_ull*)malloc(sizeof(t_ull) * 4);
	while (++i < 4)
		g_grid[i] = g_inits[g_sqr_size];
	g_grid[g_sqr_size / 4] |= 0xFFFF000000000000 >> (g_sqr_size % 4) * 16;
	g_decode_index = 0;
	while (!backtrack(0))
	{
		g_sqr_size++;
		i = -1;
		while (++i < 4)
			g_grid[i] = g_inits[g_sqr_size];
		g_grid[g_sqr_size / 4] |= 0xFFFF000000000000 >> (g_sqr_size % 4) * 16;
	}
	print_minos();
}
