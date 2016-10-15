/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:19:47 by myoung            #+#    #+#             */
/*   Updated: 2016/10/14 23:38:49 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fillit.h"

t_mino			g_all_minos[20] = {
	{LINE_V, 49, 0, 1, 0, 0x8000800080008000},
	{LINE_H, 4, 0, 4, 0, 0xF000000000000000},
	{L_DOWN, 17, 0, 3, 0, 0xE000800000000000},
	{T_DOWN, 18, 0, 3, 0, 0xE000400000000000},
	{J_DOWN, 19, 0, 3, 0, 0xE000200000000000},
	{SQUARE, 18, 0, 2, 0, 0xC000C00000000000},
	{J_RIGHT, 33, 0, 2, 0, 0xC000800080000000},
	{Z_H, 19, 0, 2, 0, 0xC000600000000000},
	{L_LEFT, 34, 0, 2, 0, 0xC000400040000000},
	{T_RIGHT, 34, 0, 1, 0, 0x8000C00080000000},
	{J_UP, 19, 0, 1, 0, 0x8000E00000000000},
	{L_RIGHT, 34, 0, 1, 0, 0x80008000C0000000},
	{S_V, 34, 0, 1, 0, 0x8000C00040000000},
	{S_H, 18, 1, 3, 0, 0x6000C00000000000},
	{T_UP, 19, 1, 2, 0, 0x4000E00000000000},
	{Z_V, 33, 1, 2, 0, 0x4000C00080000000},
	{T_LEFT, 34, 1, 2, 0, 0x4000C00040000000},
	{L_UP, 19, 2, 3, 0, 0x2000E00000000000},
	{J_LEFT, 34, 1, 2, 0, 0x40004000C0000000},
	{END, 0, 0, 0, 0, 0}
};

uint8_t g_left_to_place;
t_mino	*g_minos;

void	mino_error(int status)
{
	if (status)
		ft_putstr("usage: fillit mino_file\n");
	else
	ft_putstr("error\n");
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
	mino_error(0);
	return (END);
}

/*
** Read a mino from the file and return if we have another to read
*/

int		read_mino(int fd, char *buf)
{
	int has_next;
	int	read_ret;

	has_next = 0;
	if ((read_ret = read(fd, buf, 21)))
	{
		buf[21] = '\0';
		if (buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n'
			&& buf[19] == '\n')
		{
			buf[4] = '.';
			buf[9] = '.';
			buf[14] = '.';
			buf[19] = '.';
			if (buf[20] == '\n')
				has_next = 1;
			else if (read_ret == 21)
				mino_error(0);
			buf[20] = '.';
		}
		else
			mino_error(0);	
	}
	if (has_next)
		return (1);
	else
		return (0);
}

/*
** Read all the minos from a file
*/

void		read_minos(int fd)
{
	int			i;
	char		*buf;
	t_minotype	cur_mino;

	i = 0;	
	buf = (char*)malloc(22);
	ft_bzero(buf, 22);
	while (read_mino(fd, buf))
	{
		cur_mino = mino_id(buf);
		g_minos[i] = g_all_minos[cur_mino];
		ft_bzero(buf, 22);
		i++;
	}
	cur_mino = mino_id(buf);
	g_minos[i] = g_all_minos[cur_mino];
	i++;
	g_minos[i] = g_all_minos[END];
	free(buf);
}

int		main(int argc, char **argv)
{
	int			fd;
	int			i;

	g_minos = (t_mino*)malloc(sizeof(t_mino) * 27);
	g_left_to_place = 0;
	if (argc != 2)
		mino_error(1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		mino_error(0);
	read_minos(fd);
	i = -1;
	while (g_minos[++i].type != END)
		g_left_to_place++;
	close(fd);
	fillit();
}
