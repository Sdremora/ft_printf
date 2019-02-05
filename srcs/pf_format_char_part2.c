/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_char_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:42:41 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:28:04 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_zero(t_escape *escape)
{
	int	i;
	int offset;

	if (escape->prefix == NULL || g_status)
		return ;
	i = 0;
	offset = 0;
	ft_str_chrset(escape->prefix, '0', 0, escape->prefix_len);
}

static void		check_minus(t_escape *escape)
{
	if (escape->prefix == NULL || g_status < 0)
		return ;
	escape->postfix = escape->prefix;
	escape->postfix_len = escape->prefix_len;
	escape->prefix = NULL;
	escape->prefix_len = 0;
}

static void		check_width(t_escape *escape)
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

/*
**	Если символ = '\0' он всеравно должен вывестись.
**	Поэтому минимальная длина равна единице.
*/

void			format_char(t_escape *escape)
{
	escape->str_len = ft_strlen(escape->str);
	if (escape->str_len == 0)
		escape->str_len = 1;
	check_width(escape);
	if (escape->flags[F_MINUS] != 0)
		check_minus(escape);
	if (escape->flags[F_ZERO] != 0)
		check_zero(escape);
}
