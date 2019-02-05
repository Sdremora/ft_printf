/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_s_part1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:05:49 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:51:29 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Добавляет в начало строки пробелы, если заданная ширина больше
**	текущей длины строки.
*/

static void		pf_check_width_s(t_escape *escape)
{
	int		len;
	char	*temp;

	len = escape->width - escape->str_len;
	if (len < 0 || g_status)
		return ;
	temp = ft_strnew(len);
	if (temp == NULL)
		g_status = E_NO_MEM;
	else
	{
		ft_str_chrset(temp, ' ', 0, len);
		escape->prefix = temp;
		escape->prefix_len = len;
	}
}

static void		pf_check_minus_s(t_escape *escape)
{
	if (escape->prefix == NULL || g_status < 0)
		return ;
	escape->postfix = escape->prefix;
	escape->postfix_len = escape->prefix_len;
	escape->prefix = NULL;
	escape->prefix_len = 0;
}

static void		pf_check_zero_s(t_escape *escape)
{
	int	i;
	int offset;

	if (escape->prefix == NULL || g_status)
		return ;
	i = 0;
	offset = 0;
	ft_str_chrset(escape->prefix, '0', 0, escape->prefix_len);
}

static char		*pf_take_str(t_escape *escape, va_list *ap)
{
	char	*result;
	int		flag;

	if (escape->specifier == 'S')
		escape->len_sp = LSP_L;
	if (escape->len_sp == LSP_L)
	{
		result = NULL;
		flag = ft_wchar_str_to_utf8(va_arg(*ap, wchar_t *), &result);
		if (flag == -1)
			g_status = E_CONVERT_UTF8;
	}
	else
	{
		result = va_arg(*ap, char *);
		if (result == NULL)
			result = "(null)";
		result = ft_strdup(result);
	}
	return (result);
}

void			pf_format_s(t_escape *escape, va_list *ap)
{
	escape->str = pf_take_str(escape, ap);
	if (escape->str == NULL)
	{
		g_status = E_NO_MEM;
		return ;
	}
	escape->str_len = ft_strlen(escape->str);
	pf_check_precision(escape);
	pf_check_width_s(escape);
	if (escape->flags[F_MINUS] != 0)
		pf_check_minus_s(escape);
	if (escape->flags[F_ZERO] != 0)
		pf_check_zero_s(escape);
}
