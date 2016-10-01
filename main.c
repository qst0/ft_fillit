/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 18:55:06 by myoung            #+#    #+#             */
/*   Updated: 2016/10/01 12:10:14 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>

void	mino_error()
{
	printf("error");
	exit(0);
}

/*
** Fill the fully blank rows and columns with x's
*/

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
		return (0);
	return (1);
}

/*
** Calculate the offset caused by blank spots in a filled mino
*/

int		mino_offset(char *buf)
{
	int	fill_offset;
	
	fill_offset = 0;
	while (buf[fill_offset] == 'x')
		fill_offset++;
	return fill_offset;
}

/*
** Return the location of the blanks in a mino relative to the fill_offset
*/

int		*mino_blanks(char* buf, int fill_offset)
{
	int		*blanks;
	int		i;

	blanks = (int*)malloc(sizeof(int) * 2);
	blanks[0] = -1;
	blanks[1] = -1;
	i = 0;
	while ((blanks[0] == -1 || blanks[1] == -1) && i < 16 - fill_offset)
	{
		if (blanks[0] == -1 && buf[i + fill_offset] == '.')
			blanks[0] = i;
		else if (blanks[0] != -1 && buf[i + fill_offset] == '.')
			blanks[1] = i;
		i++;
	}
	return (blanks);
}

/*
** Return the minotype of a mino
*/

t_minotype	idmino(char *buf)
{
	int		fill_offset;
	int		*blanks;
	int		mino_id;
	int		sum;
	int		dif;

	fill_offset = mino_offset(buf);
	blanks = mino_blanks(buf, fill_offset);
	if (blanks[0] == -1)
	{
		if (buf[5 + fill_offset] == '#') 
			return (SQUARE);
		else if (buf[2 + fill_offset] == '#')
			return (LINE_H);
		else
			return (LINE_V);
	}
	else
	{
		dif = blanks[1] - blanks[0];
		sum = blanks[0] + blanks[1];	
		printf("dif: %d\n", dif);
		printf("sum: %d\n", sum);
		if (dif == 1)
			printf("We have an L or J, L or R\n");
		if (dif == 4)
			printf("We have an L or J, U or D\n");
	}
		return(L_DOWN); //We have something else
}

/*
** Read a mino from the file and return if it was a success or not
*/

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
				mino_error(); //FAILED BAD CHAR
		}
		else if (buf[offset] != '\n')
		{	
			mino_error(); //FAILED, LINE TOO LONG
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

/*
** Read all the minos from a file
*/

void	readminos(fd)
{

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
				//ADD MINO TO ARRAY
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
