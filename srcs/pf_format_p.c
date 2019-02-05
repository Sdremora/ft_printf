/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:08:59 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:51:00 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_minus(t_escape *escape)
{
	int len;

	if (escape->prefix == NULL || g_status < 0)
		return ;
	len = escape->prefix_len - 2;
	escape->postfix = escape->prefix;
	escape->postfix_len = len;
	ft_str_chrset(escape->postfix, '\0', len, 2);
	escape->prefix = ft_strdup("0x");
	if (escape->prefix == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->prefix_len = 2;
	}
}

static void		check_width(t_escape *escape)
{
	int		len;
	char	*temp;

	len = escape->width - escape->str_len - 2;
	if (len < 0 || g_status)
		return ;
	temp = ft_strnew(len + 2);
	if (temp == NULL)
		g_status = E_NO_MEM;
	else
	{
		ft_str_chrset(temp, ' ', 0, len);
		ft_strncat(temp, "0x", 2);
		free(escape->prefix);
		escape->prefix_len = len + 2;
		escape->prefix = temp;
	}
}

static void		check_zero(t_escape *escape)
{
	int len;

	len = escape->prefix_len;
	if (escape->flags[F_MINUS] || len <= 2 || g_status < 0)
		return ;
	escape->prefix[0] = '0';
	escape->prefix[1] = 'x';
	ft_str_chrset(escape->prefix, '0', 2, len - 2);
}

static void		check_precision(t_escape *escape)
{
	char	*temp;
	int		len;

	if (escape->precision < 0 || g_status)
		return ;
	if (escape->str[0] == '0' && escape->precision == 0)
	{
		escape->str[0] = '\0';
		escape->str_len = 0;
	}
	if (escape->precision > escape->str_len)
	{
		len = escape->precision;
		temp = ft_strnew(len);
		ft_str_chrset(temp, '0', 0, len - escape->str_len);
		ft_strncat(temp, escape->str, escape->str_len);
		free(escape->str);
		escape->str = temp;
		escape->str_len = escape->precision;
	}
}

void			pf_format_p(t_escape *escape, va_list *ap)
{
	size_t		num;

	num = va_arg(*ap, size_t);
	escape->str = ft_itoa_unsize_base(num, 16);
	if (escape->str == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->str_len = ft_strlen(escape->str);
		escape->prefix = ft_strdup("0x");
		if (escape->prefix == NULL)
			g_status = E_NO_MEM;
		else
		{
			escape->prefix_len = 2;
			check_precision(escape);
			check_width(escape);
			if (escape->flags[F_MINUS] != 0)
				check_minus(escape);
			if (escape->flags[F_ZERO] != 0)
				check_zero(escape);
		}
	}
}
