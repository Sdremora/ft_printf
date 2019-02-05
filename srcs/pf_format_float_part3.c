/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_float_part3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:25:51 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:49:15 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	flag_f_plus(t_escape *escape, int sign)
{
	if (sign == -1)
		return ;
	escape->prefix = ft_strdup("+");
	if (escape->prefix == NULL)
		g_status = E_NO_MEM;
	else
	{
		escape->prefix_len = 1;
	}
}

static int	flag_f_zero(t_escape *escape)
{
	int	n;

	if (escape->prefix_len == 0 || g_status || \
		escape->flags[F_MINUS] != 0 || !ft_isdigit(escape->str[0]))
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

static int	flag_f_minus(t_escape *escape)
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

static void	flag_f_whitespace(t_escape *escape)
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

void		pf_switch_flags_f(t_escape *escape, int sign)
{
	char	*str;

	if (g_status)
		return ;
	str = escape->flags;
	if (str[F_PLUS] != 0)
		flag_f_plus(escape, sign);
	if (str[F_ZERO] != 0)
		flag_f_zero(escape);
	if (str[F_MINUS] != 0)
		flag_f_minus(escape);
	if (str[F_WHITESPACE] != 0)
		flag_f_whitespace(escape);
}
