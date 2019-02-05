/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_s_part2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:05:49 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:51:38 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size_symbol(unsigned char byte)
{
	if (byte <= 0x7F)
		return (1);
	if (byte <= 0xDF)
		return (2);
	if (byte <= 0xEF)
		return (3);
	return (4);
}

void		pf_check_precision(t_escape *escape)
{
	int	precision;
	int	i;
	int	n;

	precision = escape->precision;
	if (precision < 0 || precision >= escape->str_len || g_status)
		return ;
	if (escape->len_sp == LSP_L)
	{
		i = 0;
		while (i <= precision)
		{
			n = i;
			i += get_size_symbol(escape->str[i]);
		}
		precision = n;
		escape->precision = n;
	}
	escape->str[precision] = '\0';
	escape->str_len = precision;
}
