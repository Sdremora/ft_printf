/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_indexof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:01:26 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 16:54:56 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Поиск символа в строке.
**	Если символ найден -> возвращает его индекс
**	Если строка кончилась и индекс не найден -> вернет -1
**	Если искать '\0', то отработает как strlen
*/

int		ft_str_indexof(const char *str, int c)
{
	char	chr;
	int		index;

	chr = (unsigned char)c;
	index = 0;
	while (1)
	{
		if (str[index] == chr)
			return (index);
		if (str[index] == '\0')
			return (-1);
		index++;
	}
}

/*
**	Поиск символа в строке.
**	Поиск идет до конца строки, но не дальше индекса n(включая его)
**	Если символ найден -> возвращает его индекс
**	Если строка кончилась и индекс не найден -> вернет -1
**	Если искать '\0', то отработает как strlen
*/

int		ft_str_n_indexof(const char *str, int len, int c)
{
	char	chr;
	int		index;

	chr = (unsigned char)c;
	index = 0;
	while (index < len)
	{
		if (str[index] == chr)
			return (index);
		if (str[index] == '\0')
			return (-1);
		index++;
	}
	return (-1);
}

/*
**	Поиск символа в строке начиная с её конца.
**	Если символ найден -> возвращает его индекс
**	Если строка кончилась и индекс не найден -> вернет -1
**	'\0' - не найдет.
*/

int		ft_str_last_indexof(const char *str, int c)
{
	char	chr;
	int		index;

	chr = (unsigned char)c;
	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		if (str[index] == chr)
			return (index);
		index--;
	}
	return (-1);
}

/*
**	Поиск символа в строке начиная с её конца.
**	Поиск идет до начала строки, но итераций будет не больше n
**	Если символ найден -> возвращает его индекс
**	Если строка кончилась и индекс не найден -> вернет -1
**	'\0' - не найдет.
*/

int		ft_str_last_n_indexof(const char *str, int n, int c)
{
	char	chr;
	int		index;

	chr = (unsigned char)c;
	index = ft_strlen(str) - 1;
	while (index >= 0 && n > 0)
	{
		if (str[index] == chr)
			return (index);
		index--;
		n--;
	}
	return (-1);
}
