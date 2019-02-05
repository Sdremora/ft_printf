/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_di_part2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:44:19 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:32:09 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Переносит пробелы перед числом после него.
**	Если не введена ширина -> нет пробелов -> нет смысла работы.
*/

static int	flag_di_minus(t_escape *escape)
{
	int		len;
	char	chr;

	if (escape->prefix_len == 0 || g_status)
		return (0);
	len = escape->prefix_len;
	if (escape->prefix[len - 1] == ' ')
	{
		escape->postfix = escape->prefix;
		escape->postfix_len = escape->prefix_len;
		escape->prefix = NULL;
		escape->prefix_len = 0;
	}
	else
	{
		chr = escape->prefix[len - 1];
		escape->postfix = escape->prefix;
		escape->postfix[len - 1] = '\0';
		escape->postfix_len = escape->prefix_len - 1;
		escape->prefix = ft_strnew(1);
		escape->prefix[0] = chr;
		escape->prefix_len = 1;
	}
	return (0);
}

/*
**	Заменяет пробелы перед числом на нули.
**	Если была введена точность, то оставляет все как есть.
**	Если стоит флаг минус, аналогично - не работаем.
**	Если не введена ширина -> нет пробелов -> нет смысла работы.
**	__+16 -> +016 / __-16 -> -016 / __16 -> 0016
*/

static int	flag_di_zero(t_escape *escape)
{
	int	n;

	if (escape->precision >= 0 || escape->prefix_len == 0 || g_status || \
		escape->flags[F_MINUS] != 0)
		return (0);
	n = 0;
	while (escape->prefix[n] == ' ')
	{
		escape->prefix[n] = '0';
		n++;
	}
	if (escape->prefix[n] == '+' || escape->prefix[n] == '-')
		ft_str_swap(escape->prefix, 0, n);
	return (0);
}

/*
**	Добавляет знак к числу. Соотвественно, если число отрицательно
**	то ничего делать уже не нужно.
**	0016 -> +0016 / 16 -> +16 / __16 -> _+16
*/

static void	flag_di_plus(t_escape *escape, int sign)
{
	if (sign == -1)
		return ;
	if (escape->prefix_len > 0)
		escape->prefix[escape->prefix_len - 1] = '+';
	else
	{
		escape->prefix = ft_strdup("+");
		if (escape->prefix == NULL)
			g_status = E_NO_MEM;
		else
		{
			escape->prefix_len = 1;
		}
	}
}

/*
**	Оставляет место в виде пробела для возможного знака +-
**	Если знак уже стоит, или стоит пробел -> работать не будем.
**	16 -> _16 \ 0016 -> _016 (при условие что эти нули были раньше пробелами)
**	16__ -> _16_
*/

static void	flag_di_whitespace(t_escape *escape)
{
	if (escape->prefix == NULL)
	{
		escape->prefix = ft_strdup(" ");
		escape->prefix_len = 1;
		if (escape->prefix == NULL)
			g_status = E_NO_MEM;
		if (escape->postfix_len > 0)
		{
			escape->postfix_len--;
			escape->postfix[escape->postfix_len] = '\0';
		}
	}
	else if (escape->prefix[0] == '0')
		escape->prefix[0] = ' ';
}

void		pf_switch_flags_di(t_escape *escape, int sign)
{
	char	*str;

	if (g_status)
		return ;
	str = escape->flags;
	if (str[F_PLUS] != 0)
		flag_di_plus(escape, sign);
	if (str[F_ZERO] != 0)
		flag_di_zero(escape);
	if (str[F_MINUS] != 0)
		flag_di_minus(escape);
	if (str[F_WHITESPACE] != 0)
		flag_di_whitespace(escape);
}
