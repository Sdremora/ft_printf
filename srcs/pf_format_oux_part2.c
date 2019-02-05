/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_oux_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:44:19 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:50:50 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Переносит пробелы перед числом после него.
*/

static int	flag_oux_minus(t_escape *escape)
{
	if (escape->prefix == NULL || g_status < 0)
		return (0);
	escape->postfix = escape->prefix;
	escape->postfix_len = escape->prefix_len;
	escape->prefix = NULL;
	escape->prefix_len = 0;
	return (0);
}

/*
**	Заменяет пробелы перед числом на нули.
**	Если была введена точность, то оставляет все как есть.
**	Если стоит флаг минус - аналогично.
**	__+16 -> +016 / __-16 -> -016 / __16 -> 0016
*/

static int	flag_oux_zero(t_escape *escape)
{
	int	i;
	int offset;

	if (escape->precision >= 0 || escape->prefix == NULL || g_status)
		return (0);
	i = 0;
	offset = 0;
	while (escape->prefix[i])
	{
		if (escape->prefix[i] != ' ')
		{
			ft_str_swap(escape->prefix, i, offset);
			offset++;
		}
		else
			escape->prefix[i] = '0';
		i++;
	}
	return (0);
}

/*
**	This is dark magic.
*/

static int	flag_hash_check(t_escape *escape)
{
	char	sp;
	int		len;
	char	*str;

	sp = escape->specifier;
	len = escape->str_len;
	str = escape->str;
	if (sp == 'u')
		return (FALSE);
	if ((sp == 'x' || sp == 'X') && (len == 0 || (len == 1 && str[0] == '0')))
		return (FALSE);
	if ((sp == 'o' || sp == 'O') && escape->str[0] == '0')
		return (FALSE);
	return (TRUE);
}

/*
**	"#05x" -> 0x001 / "#5x" -> __0x1 / "#-5x" -> 0x1__
**	"#05X" -> 0X001 / "#5X" -> __0X1 / "#-5X" -> 0X1__
**	если в строке записан лишь ноль, то ноль там и останется.
*/

static int	flag_x_hash(t_escape *escape)
{
	char	*str_to_add;
	int		len;

	if (!flag_hash_check(escape))
		return (0);
	if (escape->specifier == 'x')
		str_to_add = "0x";
	else if (escape->specifier == 'X')
		str_to_add = "0X";
	else
		str_to_add = "0";
	len = ft_strlen(str_to_add);
	if (escape->prefix_len < len)
	{
		free(escape->prefix);
		escape->prefix = ft_strdup(str_to_add);
		if (escape->prefix == NULL)
			return (set_status(E_NO_MEM));
		escape->prefix_len = len;
		escape->postfix_len -= len;
	}
	if (escape->prefix_len >= len)
		ft_strncpy(escape->prefix + escape->prefix_len - len, \
					str_to_add, len);
	return (0);
}

void		pf_switch_flags_oux(t_escape *escape)
{
	char	*str;

	if (g_status)
		return ;
	str = escape->flags;
	if (str[F_MINUS] != 0)
		flag_oux_minus(escape);
	if (str[F_HASH] != 0)
		flag_x_hash(escape);
	if (str[F_ZERO] != 0)
		flag_oux_zero(escape);
}
