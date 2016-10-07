/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:19:47 by myoung            #+#    #+#             */
/*   Updated: 2016/10/07 12:20:02 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	mino_error(void)
{
	ft_putstr("error");
	exit(0);
}

/*
** Return the minotype of a mino
*/

#define IDMINO(buf, str, type) if (ft_strequ(buf, str)) return (type);

char	*ft_strtrimc(const char *s, char c);

t_minotype	mino_id(char *buf)
{
	buf = ft_strtrimc(buf, '.');	
	IDMINO(buf, "#....#....#....#", LINE_V)
	IDMINO(buf, "####", LINE_H)
	IDMINO(buf, "###..#", L_DOWN)
	IDMINO(buf, "###...#", T_DOWN)
	IDMINO(buf, "###....#", J_DOWN)
	IDMINO(buf, "##...##", SQUARE)
	IDMINO(buf, "##...#....#", J_RIGHT)
	IDMINO(buf, "##....##", Z_H)
	IDMINO(buf, "##....#....#", L_LEFT)
	IDMINO(buf, "#....##...#", T_RIGHT)
	IDMINO(buf, "#....###", J_UP)
	IDMINO(buf, "#....#....##", L_RIGHT)
	IDMINO(buf, "#....##....#", S_V)
	IDMINO(buf, "##..##", S_H)
	IDMINO(buf, "#...###", T_UP)
	IDMINO(buf, "#...##...#", Z_V)
	IDMINO(buf, "#...##....#", T_LEFT)
	IDMINO(buf, "#..###", L_UP)
	IDMINO(buf, "#....#...##", J_LEFT)
	mino_error();
	return (END);
}

/*
** Read a mino from the file and return if we have another to read
*/

int		read_mino(int fd, char *buf)
{
	int has_next;

	has_next = 0;
	if (read(fd, buf, 21))
	{
		buf[21] = '\0';
		if (buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n' && buf[19] == '\n')
		{
			buf[4] = '.';
			buf[9] = '.';
			buf[14] = '.';
			buf[19] = '.';
			if (buf[20] == '\n')	
				has_next = 1;
			buf[20] = '.';
		}
		else
			mino_error();	
	}
	if (has_next)
		return (1);
	else
		return (0);
}

/*
** Read all the minos from a file
*/

t_minotype		*read_minos(int fd)
{
	int			i;
	char		*buf;
	t_minotype	cur_mino;
	t_minotype	*minos;

	i = 0;	
	buf = (char*)malloc(22);
	minos = (t_minotype*)malloc(26);
	while (read_mino(fd, buf))
	{
		cur_mino = mino_id(buf);
		
		minos[i] = cur_mino;
		i++;
	}
	cur_mino = mino_id(buf);
	minos[i] = cur_mino;
	i++;
	if (i < 26)
		minos[i] = END;
	return (minos);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_minotype	*minos;

	g_left_to_place = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	minos = read_minos(fd);
	while(*minos != END)
	{
		g_left_to_place++;
		ft_putnbr(*minos);
		ft_putchar('\n');
		minos++;
	}
	ft_putstr("left_to_place: ");
	ft_putnbr(g_left_to_place);
	ft_putchar('\n');
}
