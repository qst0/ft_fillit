/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mino.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:17:50 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/07 12:17:53 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*get_string_stamp(t_decode code)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = ft_strnew(g_sqr_size * g_sqr_size);
	while (j < 64)
	{
		if ((g_minos[code.index].stamp << j) & 0x8000000000000000)
			out[i] = code.index + 'A';
		else
			out[i] = '0';
		i++;
		if (i % g_sqr_size == 0)
			j += 16 - g_sqr_size;
		j++;
	}
	return (out);
}

char	*get_output(void)
{
	char	*out;
	char	*stamp;
	int		iters[4];

	out = (char*)malloc(g_sqr_size * g_sqr_size);
	iters[0] = -1;
	while (++iters[0] < g_sqr_size * g_sqr_size)
		out[iters[0]] = '.';
	out[iters[0]] = '\0';
	iters[0] = -1;
	iters[3] = -1;
	while (g_decodes[++iters[0]].type != END && ++iters[3] < g_decode_index)
	{
		iters[1] = g_decodes[iters[0]].offset - 1;
		iters[2] = -1;
		stamp = get_string_stamp(g_decodes[iters[0]]);
		while (out[++iters[1]] && stamp[++iters[2]])
			if (stamp[iters[2]] != '0')
				out[iters[1]] = stamp[iters[2]];
		free(stamp);
	}
	return (out);
}

void	print_minos(void)
{
	char	*buf;
	int		i;

	buf = get_output();
	i = -1;
	while (++i < g_sqr_size)
	{
		write(1, buf, g_sqr_size);
		write(1, "\n", 1);
		buf += g_sqr_size;
	}
}
