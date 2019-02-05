/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_float_part2_precision.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:25:51 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:48:22 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	add_zero(t_escape *escape, int count)
{
	char	*temp;

	temp = ft_strnew(escape->str_len + count);
	if (temp == NULL)
	{
		g_status = E_NO_MEM;
		return ;
	}
	ft_strncat(temp, escape->str, escape->str_len);
	while (count-- > 0)
		ft_strncat(temp, "0", 1);
	free(escape->str);
	escape->str = temp;
	escape->str_len = ft_strlen(escape->str);
}

static void	increment_char(t_escape *escape, int index)
{
	char	cur_chr;
	char	*temp;

	cur_chr = escape->str[index];
	if (cur_chr == '9')
	{
		escape->str[index] = '0';
		if (index == 0)
		{
			temp = ft_strnew(escape->str_len + 1);
			temp[0] = '1';
			ft_strncat(temp, escape->str, escape->str_len);
			(escape->str_len)++;
			free(escape->str);
			escape->str = temp;
		}
		else
			increment_char(escape, index - 1);
	}
	else if (cur_chr == '.')
		increment_char(escape, index - 1);
	else
		(escape->str[index])++;
}

static void	make_round(t_escape *escape, int point_i, int dif)
{
	int		i;
	char	prev_chr;

	i = point_i + escape->precision + 1;
	prev_chr = escape->str[i - 1];
	if (prev_chr == '.')
		prev_chr = escape->str[i - 2];
	if (dif > 1 && escape->str[i] >= '5')
		increment_char(escape, i - 1);
	if (dif == 1 && escape->str[i] > '5')
		increment_char(escape, i - 1);
	if (dif == 1 && escape->str[i] == '5' && ((prev_chr - '0') % 2 != 0))
		increment_char(escape, i - 1);
	i = ft_str_indexof(escape->str, '.') + escape->precision + 1;
	if (escape->precision == 0)
		escape->str[i - 1] = '\0';
	else
		escape->str[i] = '\0';
	escape->str_len = ft_strlen(escape->str);
}

void		pf_check_precision_f(t_escape *escape)
{
	int		precision;
	int		point_i;
	int		dif;

	if (g_status < 0 || !ft_isdigit(escape->str[0]))
		return ;
	if (escape->precision < 0)
		escape->precision = 6;
	precision = escape->precision;
	point_i = ft_str_indexof(escape->str, '.');
	dif = escape->str_len - 1 - point_i - precision;
	if (dif < 0)
		add_zero(escape, -dif);
	else if (dif > 0)
		make_round(escape, point_i, dif);
}
