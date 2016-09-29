/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 18:55:06 by myoung            #+#    #+#             */
/*   Updated: 2016/09/28 20:50:09 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
int		readmino(int fd, int offset, char* buf)
{
	while (offset < 16 && read(fd, buf + offset, 1) != -1)
	{
		if(offset + 1 % 4 != 0)
		{
			if(buf[offset] == '.' || buf[offset] == '#')
				offset++;
			else if(buf[offset] != '\n')
				return (0); //FAILED BAD CHAR
		}
		else if(buf[offset] != '\n')
			return (0); //FAILED, LINE TOO LONG
	}
	write(1, buf, 16);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		offset;
	char	buf[16];
	if (argc != 2)
		return (0); //USAGE GOES HERE
	fd = open(argv[1], O_RDONLY);
	offset = 0;
	if (fd == -1)
		return (1); //Error opening file!
	if (readmino(fd, offset, buf))
	{
		write(1, buf, offset);
		//ID MINO
		//ADD MINO TO ARRAY
	}
	else
		write(1, "FAIL", 4);
}
