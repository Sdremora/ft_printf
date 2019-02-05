/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_text_property.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 12:03:50 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 18:08:22 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_text_property(t_escape *escp, size_t start, \
							char *src_dell, char *src_put)
{
	char	*temp;
	size_t	offset;
	size_t	len_dst;
	size_t	len_src;
	size_t	len_del;

	len_dst = ft_strlen(escp->str_simple);
	len_src = ft_strlen(src_put);
	len_del = ft_strlen(src_dell);
	temp = ft_strnew(len_dst - len_del + len_src);
	if (temp == NULL)
	{
		g_status = E_NO_MEM;
		return ;
	}
	ft_strncat(temp, escp->str_simple, start);
	ft_strncat(temp, src_put, len_src);
	offset = start + len_del;
	ft_strncat(temp, escp->str_simple + offset, len_dst - offset);
	free(escp->str_simple);
	escp->str_simple = temp;
}

int			pf_found_text_colors(t_escape *escp, int i)
{
	int		n;
	char	*str;

	str = escp->str_simple;
	if ((n = ft_str_indexof_str(str + i, "{def}")) >= 0)
		put_text_property(escp, n + i, "{def}", BC_DEFAULT);
	else if ((n = ft_str_indexof_str(str + i, "{red}")) >= 0)
		put_text_property(escp, n + i, "{red}", BC_RED);
	else if ((n = ft_str_indexof_str(str + i, "{green}")) >= 0)
		put_text_property(escp, n + i, "{green}", BC_GREEN);
	else if ((n = ft_str_indexof_str(str + i, "{yellow}")) >= 0)
		put_text_property(escp, n + i, "{yellow}", BC_YELLOW);
	else if ((n = ft_str_indexof_str(str + i, "{blue}")) >= 0)
		put_text_property(escp, n + i, "{blue}", BC_BLUE);
	else if ((n = ft_str_indexof_str(str + i, "{magenta}")) >= 0)
		put_text_property(escp, n + i, "{magenta}", BC_MAGENTA);
	else if ((n = ft_str_indexof_str(str + i, "{cyan}")) >= 0)
		put_text_property(escp, n + i, "{cyan}", BC_CYAN);
	else if ((n = ft_str_indexof_str(str + i, "{gray}")) >= 0)
		put_text_property(escp, n + i, "{gray}", BC_GRAY);
	else if ((n = ft_str_indexof_str(str + i, "{black}")) >= 0)
		put_text_property(escp, n + i, "{black}", BC_BLACK);
	return (n);
}

int			pf_found_bg_colors(t_escape *escp, int i)
{
	int		n;
	char	*str;

	str = escp->str_simple;
	if ((n = ft_str_indexof_str(str + i, "{BG_DEF}")) >= 0)
		put_text_property(escp, n + i, "{BG_DEF}", BC_BG_DEFAULT);
	else if ((n = ft_str_indexof_str(str + i, "{BG_RED}")) >= 0)
		put_text_property(escp, n + i, "{BG_RED}", BC_BG_RED);
	else if ((n = ft_str_indexof_str(str + i, "{BG_GREEN}")) >= 0)
		put_text_property(escp, n + i, "{BG_GREEN}", BC_BG_GREEN);
	else if ((n = ft_str_indexof_str(str + i, "{BG_BROWN}")) >= 0)
		put_text_property(escp, n + i, "{BG_BROWN}", BC_BG_BROWN);
	else if ((n = ft_str_indexof_str(str + i, "{BG_BLUE}")) >= 0)
		put_text_property(escp, n + i, "{BG_BLUE}", BC_BG_BLUE);
	else if ((n = ft_str_indexof_str(str + i, "{BG_MAGENTA}")) >= 0)
		put_text_property(escp, n + i, "{BG_MAGENTA}", BC_BG_MAGENTA);
	else if ((n = ft_str_indexof_str(str + i, "{BG_CYAN}")) >= 0)
		put_text_property(escp, n + i, "{BG_CYAN}", BC_BG_CYAN);
	else if ((n = ft_str_indexof_str(str + i, "{BG_GRAY}")) >= 0)
		put_text_property(escp, n + i, "{BG_GRAY}", BC_BG_GRAY);
	return (n);
}

int			pf_found_property(t_escape *escp, int i)
{
	int		n;
	char	*str;

	str = escp->str_simple;
	if ((n = ft_str_indexof_str(str + i, "{BOLD}")) >= 0)
		put_text_property(escp, n + i, "{BOLD}", BC_BOLD);
	else if ((n = ft_str_indexof_str(str + i, "{N_BOLD}")) >= 0)
		put_text_property(escp, n + i, "{N_BOLD}", BC_NBOLD);
	else if ((n = ft_str_indexof_str(str + i, "{UNDERLINE}")) >= 0)
		put_text_property(escp, n + i, "{UNDERLINE}", BC_UNDERLINE);
	else if ((n = ft_str_indexof_str(str + i, "{N_UNDERLINE}")) >= 0)
		put_text_property(escp, n + i, "{N_UNDERLINE}", BC_NUNDERLINE);
	else if ((n = ft_str_indexof_str(str + i, "{BLINK}")) >= 0)
		put_text_property(escp, n + i, "{BLINK}", BC_BLINK);
	else if ((n = ft_str_indexof_str(str + i, "{N_BLINK}")) >= 0)
		put_text_property(escp, n + i, "{N_BLINK}", BC_NBLINK);
	else if ((n = ft_str_indexof_str(str + i, "{INVERSE}")) >= 0)
		put_text_property(escp, n + i, "{INVERSE}", BC_INVERSE);
	else if ((n = ft_str_indexof_str(str + i, "{N_INVERSE}")) >= 0)
		put_text_property(escp, n + i, "{N_INVERSE}", BC_NINVERSE);
	else if ((n = ft_str_indexof_str(str + i, "{DEF}")) >= 0)
		put_text_property(escp, n + i, "{DEF}", BC_DEFAULT);
	return (n);
}
