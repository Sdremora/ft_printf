/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_4b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:37:33 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 16:53:20 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define SIZE_T_SIZE 4

static void	convert_to_utf8(unsigned int e_char, char *buf)
{
	if (e_char <= 0x7F)
		buf[0] = (char)e_char;
	else if (e_char <= 0x7FF)
	{
		buf[0] = 0xC0 | (e_char >> 6);
		buf[1] = 0x80 | (e_char & 0x3F);
	}
	else if (e_char <= 0xFFFF)
	{
		buf[0] = 0xE0 | (e_char >> 12);
		buf[1] = 0x80 | ((e_char >> 6) & 0x3F);
		buf[2] = 0x80 | ((e_char >> 0) & 0x3F);
	}
	else if (e_char <= 0x1FFFFF)
	{
		buf[0] = 0xF0 | (e_char >> 18);
		buf[1] = 0x80 | ((e_char >> 12) & 0x3F);
		buf[2] = 0x80 | ((e_char >> 6) & 0x3F);
		buf[3] = 0x80 | ((e_char >> 0) & 0x3F);
	}
}

/*
**	Печаете 4-х байтовый символ
**	Преобразуя его в последовательность чаров в кодировке UTF-8
**	Возвращает количество байт на которые конвертировался символ.
*/

int			ft_putchar_utf8(unsigned int e_char)
{
	char	buf[SIZE_T_SIZE];
	int		i;

	i = 1;
	convert_to_utf8(e_char, buf);
	write(1, buf, 1);
	while (i < SIZE_T_SIZE)
	{
		if (buf[i] != 0)
		{
			write(1, buf + i, 1);
			i++;
		}
	}
	return (i);
}

/*
**	Печает строку состоящую из 4-х байтовых сиволов.
**	Каждый символ преобразует в последовательность чаров в UTF-8 кодировке.
**	Возвращает длину строки.
*/

int			ft_pustr_utf8(unsigned int *str)
{
	int len;

	len = 0;
	while (str[len] != 0)
	{
		ft_putchar_utf8(str[len]);
		len++;
	}
	return (len);
}
