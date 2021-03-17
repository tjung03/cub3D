/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:39:04 by tjung             #+#    #+#             */
/*   Updated: 2021/03/17 17:57:50 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096

# endif
# include "../utils_bonus/utils_bonus.h"

int			get_nl(int fd, char **line, char **strg, char *nlpt);
int			get_next_line(int fd, char **line);

#endif
