/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 18:55:06 by myoung            #+#    #+#             */
/*   Updated: 2016/09/30 16:03:42 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>

void	fillmino(char *buf)
{
	unsigned char i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0 && buf[i] != '#' && buf[i + 1] != '#'
				&& buf[i + 2] != '#' && buf[i + 3] != '#')
		{
			buf[i] = 'x';
			buf[i + 1] = 'x';
			buf[i + 2] = 'x';
			buf[i + 3] = 'x';
		}
		if (i < 4 && buf[i] != '#'
			   	&& buf[i + 4] != '#'
				&& buf[i + 8] != '#' && buf[i + 12] != '#')
		{
			buf[i] = 'x';
			buf[i + 4] = 'x';
			buf[i + 8] = 'x';
			buf[i + 12] = 'x';
		}
		i++;
	}
}

/*
** Check that our mino has only four '#' blocks
*/

int		mino_valid(char* buf)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 16)
	{
		if (buf[i] == '#')
			count++;
		i++;
	}
	if (count != 4)
	{
		printf("Not 4\n");
		return (0);
	}
	return (1);
}

int		mino_offset(char *buf)
{
	int	fill_offset;
	
	fill_offset = 0;
	while (buf[fill_offset] == 'x')
		fill_offset++;
	return fill_offset;
}

int		*mino_blanks(char* buf, int fill_offset)
{
	int		*blanks;
	int		i;

	blanks = (int*)malloc(sizeof(int) * 2);
	blanks[0] = -1;
	blanks[1] = -1;
	printf("fill_offset: %d\n", fill_offset);
	i = 0;
	while ((blanks[0] == -1 || blanks[1] == -1) && i < 16 - fill_offset)
	{
		if (blanks[0] == -1 && buf[i + fill_offset] == '.')
			blanks[0] = i;
		else if (blanks[0] != -1 && buf[i + fill_offset] == '.')
			blanks[1] = i;
		i++;
	}
	printf("blank 1: %d\n", blanks[0]);
	printf("blank 2: %d\n", blanks[1]);
	return (blanks);
}

t_minotype	idmino(char *buf)
{
	int		fill_offset;
	int		*blanks;

	fill_offset = mino_offset(buf);
	blanks = mino_blanks(buf, fill_offset);
	if (blanks[0] == -1)
	{
		return(SQUARE); //We have a sq or line
	}
	else
		return(L_DOWN); //We have something else
}

int		readmino(int fd, char* buf)
{
	int offset;
	offset = 0;
	while (offset < 16 && read(fd, buf + offset, 1) != -1)
	{
		if (offset + 1 % 4 != 0)
		{
			if (buf[offset] == '.' || buf[offset] == '#')
				offset++;
			else if (buf[offset] != '\n')
				return (0); //FAILED BAD CHAR
		}
		else if (buf[offset] != '\n')
		{	
			return (0); //FAILED, LINE TOO LONG
		}
		//printf("%d\n", buf[offset]);
	}
	write(1, buf, 16);
	write(1, "\n", 1);
	fillmino(buf);
	write(1, buf, 16);
	write(1, "\n", 1);
	if (mino_valid(buf) == 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		read_offset;
	char	buf[16];
	if (argc != 2)
		return (0); //USAGE GOES HERE
	fd = open(argv[1], O_RDONLY);
	read_offset = 0;
	if (fd == -1)
		return (1); //Error opening file!
	readmino(fd, buf);
	printf("id: %d\n", idmino(buf)); //ID MINO
	//ADD MINO TO ARRAY
	if(read(fd, buf, 2) != -1)
	{
		while(buf[1] == '\n')
		{
			printf("We have more to read\n");
			if(readmino(fd, buf))
			{
				printf("id: %d\n", idmino(buf)); //ID MINO
				if(read(fd, buf, 2) == -1)
					return (0); //error nothing left to read;
			}
			else
				return (1); //error readmino problem;
		}
		printf("That's All folks!");
		return (0);
	}
}
