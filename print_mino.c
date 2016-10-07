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

char	*get_string_stamp(t_mino mino)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = ft_strnew(g_sqr_size * g_sqr_size);
	while (j < 64)
	{
		if ((mino->stamp << j) & 0x8000000000000000)
			out[i] = mino->index + 'A';
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
