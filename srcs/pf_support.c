/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_support.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:04:17 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 18:11:24 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Для сокращения строк при проверках и обновлениях статуса ошибок
*/

int			set_status(int status)
{
	g_status = status;
	return (ERROR);
}

int			escape_initial(t_escape *escape)
{
	ft_bzero(escape->flags, F_DEF + 1);
	escape->width = 0;
	escape->precision = -1;
	escape->len_sp = LSP_DEF;
	escape->specifier = '\0';
	escape->str_len = 0;
	escape->prefix_len = 0;
	escape->postfix_len = 0;
	escape->str_simple = NULL;
	escape->str = NULL;
	escape->str_utf8 = NULL;
	escape->prefix = NULL;
	escape->postfix = NULL;
	escape->error_char = '\0';
	return (0);
}

void		ft_str_chrset(char *line, int c, int start, int len)
{
	char	chr;
	int		i;

	chr = (char)c;
	i = 0;
	line = line + start;
	while (i < len)
	{
		line[i] = chr;
		i++;
	}
}

void		ft_str_swap(char *str, int pos1, int pos2)
{
	char	temp;

	if (pos1 != pos2)
	{
		temp = str[pos1];
		str[pos1] = str[pos2];
		str[pos2] = temp;
	}
}

void		ft_str_toupper(char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
	{
		if (str[n] >= 'a' && str[n] <= 'z')
			str[n] = (str[n] - 32);
		n++;
	}
}
