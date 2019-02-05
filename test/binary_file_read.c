/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_file_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:13:27 by sdremora          #+#    #+#             */
/*   Updated: 2019/01/24 10:50:44 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void binary(int fd)
{
	unsigned char buf[1];
	int mask;
	unsigned char bit[1];
	int i;

	while (read(fd, buf, 1) > 0)
	{
		mask = 1 << 7;
		write(1, &buf, 1);
		write(1, &"==>", 1);
		i = 0;
		while (i < 8)
		{
			bit[0] = (buf[0] & mask) > 0 ? 1 : 0;
			bit[0] += '0';
			mask = mask >> 1;
			write(1, bit, 1);
			i++;
		}
		write(1, &" ", 1);
	}
	write(1, &"\n", 1);
}

int	main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
	{
		puts("Missing arguments!");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		puts("File does't exist!");
		return (-1);
	}
	binary(fd);
	return (0);
}