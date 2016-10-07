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
			j += 16 - (j % g_sqr_size);
		else
			j++;
	}
	return (out);
}

char	*get_output(void)
{
	char	*out;
	char	*stamp;
	int		i;
	int		j;
	int		k;

	out = (char*)malloc(g_sqr_size * g_sqr_size);
	i = -1;
	while (++i < g_sqr_size * g_sqr_size)
		out[i] = '.';
	out[i] = '\0';
	i = -1;
	while (g_decodes[++i].type != END)
	{
		j = g_decodes[i].offset - 1;
		k = -1;
		stamp = get_string_stamp(g_decodes[i]);
		while (out[++j] && stamp[++k])
			if (stamp[k] != '0')
				out[j] = stamp[k];
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
	free(buf);
}
