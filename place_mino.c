/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_mino.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 13:15:37 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/06 13:15:38 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HEX 0x8000000000000000
#define GETB(z) ((g_grid[z / 64] << (z % 64) & HEX) == HEX)

#define CHECK1 (((mino->stamp >> (offset % 64)) & g_grid[offset / 64]) == 0)
#define GROSS ((offset + mino->total_offset) / 64)
#define CHECK2 (((mino->stamp << (64 - offset % 64)) & g_grid[GROSS]) == 0)

uint8_t	g_left_to_place;

int		attempt_place(int sqr_size, int offset, t_mino *mino)
{
	if (CHECK1 && CHECK2)
	{
		//	Add mino to grid
		g_grid[offset / 64] |= mino->stamp >> (offset % 64);
		g_grid[GROSS] |= mino->stamp << (64 - offset % 64);
		//	Mark it as placed
		mino->placed = 1;
		g_left_to_place--;
		//	Try to move forward with it
		if (backtrack(sqr_size, offset + 1))
			return (1);
		else
		{
			//	Remove mino from grid
			g_grid[offset / 64] ^= mino->stamp >> (offset % 64);
			g_grid[GROSS] ^= mino->stamp << (64 - offset % 64);
			mino->placed = 0;
			g_left_to_place++;
		}
	}
	return (0);
}

int		backtrack(int sqr_size, int offset)
{
	int i;

	i = -1;
	if (GETB(z) && g_left_to_place > 0)
	{
		while (g_minos[++i].type != END)
		{
			if (g_minos[i].placed || !g_minos[i].added_blanks)
				continue ;
			if (attempt_place(sqr_size, offset, &g_minos[i]))
				return (1);
		}
		//	If we are here then the six didn't work, lets move forward
		if ((offset + 1) % sqr_size != 0)
			return (backtrack(sqr_size, offset + 1));
		else if ((offset + 1) / sqr_size > offset / sqr_size)
			return (backtrack(sqr_size, offset + (64 - sqr_size)));
	}
	else if (g_left_to_place > 0)
	{
		while (g_minos[++i].type != END)
		{
			if (g_minos[i].placed)
				continue ;
			if (attempt_place(sqr_size, offset, &g_minos[i]))
				return (1);
		}
	}
	return (1);
}

void	fillit(void)
{
	g_left_to_place = /* num_minos */;
}
