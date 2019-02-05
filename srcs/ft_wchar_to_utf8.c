/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_utf8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 11:55:40 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 17:05:01 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Вовращает кол-во байт на которые распадется символ при
**	кодировке в UTF-8
**	Если символ перекодировать нельзя (кол-во байт должно быть больше 4-х)
**	Вернет -1
**	Причину symbol >= 0xd800 && symbol <= 0xdfff смотри тут
**	https://lists.gnu.org/archive/html/coreutils/2016-03/msg00026.html
*/

int	ft_wchar_get_utf8_size(unsigned int symbol)
{
	if (symbol >= 0xd800 && symbol <= 0xdfff)
		return (-1);
	if (symbol <= 0x7F)
		return (1);
	if (symbol <= 0x7FF)
		return (2);
	if (symbol <= 0xFFFF)
		return (3);
	if (symbol <= 0x10FFFF)
		return (4);
	return (-1);
}

/*
**	Конвертирует 4-х байтовый символ в последовательность байт в кодировке UTF-8
**	Присланный буфер должен иметь размер не меньше 5 байт.
**	При невозможности конвертирования вернет -1.
*/

int	ft_wchar_to_utf8(unsigned int symbol, char *buf)
{
	int size;

	size = ft_wchar_get_utf8_size(symbol);
	if (size == -1)
		return (-1);
	ft_str_chrset(buf, 0, 0, 5);
	if (size == 1)
		buf[0] = (char)symbol;
	else if (size == 2)
		buf[0] = (char)(symbol >> 6) | 0xC0;
	else if (size == 3)
		buf[0] = (char)(symbol >> 12) | 0xE0;
	else if (size == 4)
		buf[0] = (char)(symbol >> 18) | 0xF0;
	while (size > 1)
	{
		size--;
		buf[size] = (char)(symbol & 0x3F) | 0x80;
		symbol >>= 6;
	}
	return (0);
}

/*
**	Возвращает количество байт, которые получатся при конвертирование
**	строки состоящей из 4-х байтовых символов в последовательность байт в UTF-8
**	Если символ не помещается в 4 байта -> выдает -1.
*/

int	ft_wchar_get_utf8_strlen(wchar_t *w_str)
{
	int i;
	int n;
	int count;

	i = 0;
	count = 0;
	while (w_str[i])
	{
		n = ft_wchar_get_utf8_size(w_str[i++]);
		if (n < 0)
			return (-1);
		count += n;
	}
	return (count);
}

/*
**	Строку состоящую из wchar_t преобразует в строку байт в UTF-8
**	Строку возвращает из кучи.
**	Если строка = NULL то вернет "(null)";
**	Если память не выделилась в str будет записан NULL и вернет -2
**	При неудачном конвертирование в UTF-8 вернет -1
*/

int	ft_wchar_str_to_utf8(wchar_t *w_str, char **str)
{
	char	temp[5];
	int		count;
	size_t	i;

	if (w_str == NULL)
	{
		*str = ft_strdup("(null)");
		return (0);
	}
	count = ft_wchar_get_utf8_strlen(w_str);
	if (count < 0)
		return (-1);
	*str = ft_strnew(count);
	if (str == NULL)
		return (-2);
	i = 0;
	while (w_str[i])
	{
		ft_wchar_to_utf8(w_str[i], temp);
		ft_strncat(*str, temp, 5);
		i++;
	}
	return (0);
}
