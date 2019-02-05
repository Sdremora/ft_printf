/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_oux_part1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:42:38 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:50:09 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	pf_take_num_oux(t_escape *escape, va_list *ap)
{
	size_t		num;
	t_len_sp	esp_len;

	esp_len = escape->len_sp;
	if (escape->specifier == 'O' || escape->specifier == 'U')
		esp_len = LSP_L;
	if (esp_len == LSP_L)
		num = va_arg(*ap, unsigned long int);
	else if (esp_len == LSP_LL)
		num = va_arg(*ap, unsigned long long int);
	else if (esp_len == LSP_Z || esp_len == LSP_T)
		num = va_arg(*ap, size_t);
	else if (esp_len == LSP_J)
		num = va_arg(*ap, uintmax_t);
	else if (esp_len == LSP_H)
		num = (unsigned short int)va_arg(*ap, unsigned int);
	else if (esp_len == LSP_HH)
		num = (unsigned char)va_arg(*ap, unsigned int);
	else
		num = va_arg(*ap, unsigned int);
	return (num);
}

/*
**	Костыль для случая
**	printf("%.x", 0) -> в таком случае ноль затирается оО
*/

static void		dirty_hack_precision_oux(t_escape *escape)
{
	free(escape->str);
	escape->str = ft_strnew(0);
	escape->str_len = 0;
}

/*
**	для ("%.5x", 16) выведет 00010
*/

static void		pf_check_precision_oux(t_escape *escape)
{
	int		len;
	int		offset;
	char	*temp;

	len = escape->str_len;
	if (escape->precision == 0 && escape->str_len == 1 \
		&& escape->str[0] == '0')
		dirty_hack_precision_oux(escape);
	if (escape->precision <= len)
		return ;
	temp = ft_strnew(escape->precision);
	if (temp == NULL)
		g_status = E_NO_MEM;
	else
	{
		offset = escape->precision - len;
		ft_str_chrset(temp, '0', 0, offset);
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

static void		pf_check_width_oux(t_escape *escape)
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

void			pf_format_oux(t_escape *escape, va_list *ap, char sp)
{
	size_t		num;

	num = pf_take_num_oux(escape, ap);
	if (sp == 'u' || sp == 'U')
		escape->str = ft_itoa_unsize_base(num, 10);
	else if (sp == 'o' || sp == 'O')
		escape->str = ft_itoa_unsize_base(num, 8);
	else
	{
		escape->str = ft_itoa_unsize_base(num, 16);
		if (sp == 'X')
			ft_str_toupper(escape->str);
	}
	if (escape->str == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->str_len = ft_strlen(escape->str);
		pf_check_precision_oux(escape);
		pf_check_width_oux(escape);
		pf_switch_flags_oux(escape);
	}
}
