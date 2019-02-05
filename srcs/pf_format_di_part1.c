/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_di_part1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:42:38 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:31:53 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long		pf_take_num_di(t_escape *escape, va_list *ap)
{
	long long	num;
	t_len_sp	esp_len;

	esp_len = escape->len_sp;
	if (escape->specifier == 'D')
		esp_len = LSP_L;
	if (esp_len == LSP_L)
		num = va_arg(*ap, long int);
	else if (esp_len == LSP_LL || esp_len == LSP_Z || esp_len == LSP_T)
		num = va_arg(*ap, long long int);
	else if (esp_len == LSP_J)
		num = va_arg(*ap, intmax_t);
	else if (esp_len == LSP_H)
		num = (short int)va_arg(*ap, int);
	else if (esp_len == LSP_HH)
		num = (signed char)va_arg(*ap, int);
	else
		num = va_arg(*ap, int);
	return (num);
}

/*
**	Костыль для случая
**	printf("%.d", 0) -> в таком случае ноль затирается оО
*/

static void		dirty_hack_precision_di(t_escape *escape)
{
	if (escape->precision == 0 && escape->str[0] == '0')
	{
		free(escape->str);
		escape->str = ft_strnew(0);
		escape->str_len = 0;
	}
}

/*
**	%.3d для 16 выдаст 016
**	%.3d для -16 выдаст -016
*/

static void		pf_check_precision_di(t_escape *escape)
{
	int		len;
	char	*temp;

	len = escape->str_len;
	dirty_hack_precision_di(escape);
	if (escape->precision <= len)
		return ;
	temp = ft_strnew(escape->precision);
	if (temp == NULL)
		g_status = E_NO_MEM;
	else
	{
		ft_str_chrset(temp, '0', 0, escape->precision - len);
		ft_strncat(temp, escape->str, len);
		free(escape->str);
		escape->str = temp;
		escape->str_len = escape->precision;
	}
}

/*
**	Добавляет в начало строки пробелы, если заданная ширина больше
**	текущей длины строки.
*/

static void		pf_check_width_di(t_escape *escape)
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

void			pf_format_di(t_escape *escape, va_list *ap)
{
	long long	num;
	int			sign;

	num = pf_take_num_di(escape, ap);
	sign = (num < 0) ? -1 : 1;
	escape->str = ft_itoa_unsize_base(num * sign, 10);
	if (sign == -1)
	{
		escape->prefix = ft_strdup("-");
		escape->prefix_len = 1;
		if (escape->prefix == NULL)
			g_status = E_NO_MEM;
	}
	if (escape->str == NULL || g_status < 0)
		g_status = E_NO_MEM;
	else
	{
		escape->str_len = ft_strlen(escape->str);
		pf_check_precision_di(escape);
		pf_check_width_di(escape);
		pf_switch_flags_di(escape, sign);
	}
}
