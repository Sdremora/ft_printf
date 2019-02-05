/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_float_part1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:25:51 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:32:18 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		convert_double_to_str(t_escape *escape, va_list *ap, int *sign)
{
	double		num_d;
	long double	num_ld;

	if (escape->len_sp == LSP_UL)
	{
		num_ld = va_arg(*ap, long double);
		*sign = (num_ld < 0) ? -1 : 1;
		escape->str = pf_double_to_str("L", num_ld);
	}
	else
	{
		num_d = va_arg(*ap, double);
		*sign = (num_d < 0) ? -1 : 1;
		escape->str = pf_double_to_str("l", num_d);
	}
	if (escape->str == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->str_len = ft_strlen(escape->str);
	}
}

static void		cut_last_zero(t_escape *escape)
{
	int i;

	i = escape->str_len - 1;
	while (escape->str[i] == '0')
		i--;
	if (escape->str[i] == '.')
	{
		escape->str[i + 1] = '0';
		escape->str[i + 2] = '\0';
	}
	else
		escape->str[i + 1] = '\0';
	escape->str_len = ft_strlen(escape->str);
}

static void		pf_check_width_f(t_escape *escape)
{
	int		len;
	int		offset;
	char	*temp;

	len = escape->str_len + escape->prefix_len;
	if (escape->width <= len || g_status)
		return ;
	temp = ft_strnew(escape->width - escape->str_len);
	if (temp == NULL)
		g_status = E_NO_MEM;
	else
	{
		offset = escape->width - len;
		ft_str_chrset(temp, ' ', 0, offset);
		if (escape->prefix_len > 0)
			ft_strncat(temp, escape->prefix, len);
		free(escape->prefix);
		escape->prefix = temp;
		escape->prefix_len = escape->width - escape->str_len;
	}
}

void			pf_format_f(t_escape *escape, va_list *ap)
{
	int			sign;

	convert_double_to_str(escape, ap, &sign);
	if (g_status < 0)
		return ;
	cut_last_zero(escape);
	if (sign == -1)
	{
		escape->prefix = ft_strdup("-");
		escape->prefix_len = 1;
		if (escape->prefix == NULL)
			g_status = E_NO_MEM;
	}
	if (escape->specifier == 'F')
		ft_str_toupper(escape->str);
	pf_check_precision_f(escape);
	pf_check_width_f(escape);
	pf_switch_flags_f(escape, sign);
}
