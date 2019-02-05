/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 09:33:56 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/04 16:37:09 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H
/*
**			Цвет текста:
**	{black}		чёрный цвет знаков
**	{red}		красный цвет знаков
**	{green}		зелёный цвет знаков
**	{yellow}	желтый цвет знаков
**	{blue}		синий цвет знаков
**	{magenta}	фиолетовый цвет знаков
**	{cyan}		цвет морской волны знаков
**	{gray}		серый цвет знаков
**	{def}		возврат к дефолтным значениям
*/

# define BC_BLACK	"\033[0;30m"
# define BC_RED		"\033[0;31m"
# define BC_GREEN	"\033[0;32m"
# define BC_YELLOW	"\033[0;33m"
# define BC_BLUE	"\033[0;34m"
# define BC_MAGENTA	"\033[0;35m"
# define BC_CYAN	"\033[0;36m"
# define BC_GRAY	"\033[0;37m"
# define BC_DEFAULT	"\033[0m"

/*
**			Дополнительные свойства для текта:
**	{BOLD}			жирный шрифт (интенсивный цвет)
**	{NBOLD}			установить нормальную интенсивность
**	{UNDERLINE}		подчеркивание
**	{NUNDERLINE}	отменить подчеркивание
**	{BLINK}			мигающий
**	{NBLINK}		отменить мигание
**	{INVERSE}		реверсия (знаки приобретают цвет фона, а фон -- цвет знаков)
**	{NINVERSE}		отменить реверсию
**	{DEF}			возврат к дефолтным значениям
*/

# define BC_BOLD		"\033[1m"
# define BC_NBOLD		"\033[22m"
# define BC_UNDERLINE	"\033[4m"
# define BC_NUNDERLINE	"\033[4m"
# define BC_BLINK		"\033[5m"
# define BC_NBLINK		"\033[5m"
# define BC_INVERSE		"\033[7m"
# define BC_NINVERSE	"\033[7m"

/*
**			Цвет фона
**	Должен стоять либо один либо после цвета текста.
**	{BG_BLACK}		чёрный
**	{BG_RED}		красный
**	{BG_GREEN}		зелёный
**	{BG_BROWN}		коричневый
**	{BG_BLUE}		синий
**	{BG_MAGENTA}	фиолетовый
**	{BG_CYAN}		цвет морской волны знаков
**	{BG_GRAY}		серый
**	{BG_DEF}		возврат к дефолтным значениям
*/

# define BC_BG_BLACK	"\033[40m"
# define BC_BG_RED		"\033[41m"
# define BC_BG_GREEN	"\033[42m"
# define BC_BG_BROWN	"\033[43m"
# define BC_BG_BLUE		"\033[44m"
# define BC_BG_MAGENTA	"\033[45m"
# define BC_BG_CYAN		"\033[46m"
# define BC_BG_GRAY		"\033[47m"
# define BC_BG_DEFAULT	"\033[49m"

#endif
