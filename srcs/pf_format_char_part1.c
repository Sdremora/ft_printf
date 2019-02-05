/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_сhar_part1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:05:49 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 18:02:28 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

/*
**	из va_lista char не достать va_arg(*ap, char), он достается как int
*/

static char		*pf_take_char(t_escape *escape, va_list *ap)
{
	char		temp[5];
	t_len_sp	esp_len;
	int			flag;

	ft_str_chrset(temp, '\0', 0, 5);
	if (escape->specifier == 'C')
		escape->len_sp = LSP_L;
	esp_len = escape->len_sp;
	if (esp_len == LSP_L)
	{
		flag = ft_wchar_to_utf8(va_arg(*ap, wint_t), temp);
		if (flag == -1)
		{
			g_status = E_CONVERT_UTF8;
			return (NULL);
		}
	}
	else
		temp[0] = (char)va_arg(*ap, int);
	return (ft_strdup(temp));
}

void			pf_format_c_char(t_escape *escape, char c)
{
	escape->str = ft_strnew(1);
	if (escape->str == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->str[0] = c;
		escape->str_len = 1;
		format_char(escape);
	}
}

void			pf_format_c_ap(t_escape *escape, va_list *ap)
{
	escape->str = pf_take_char(escape, ap);
	if (escape->str == NULL || g_status)
	{
		if (!g_status)
			g_status = E_NO_MEM;
	}
	else
	{
		format_char(escape);
	}
}
