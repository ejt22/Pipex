/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:09:42 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/08/03 14:38:40 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function frees an array of strings. */

void	free_strs(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* This function frees the data structure. */

void	free_struct(t_data *data)
{
	if (data->cmd1)
		free_strs(data->cmd1);
	if (data->cmd2)
		free_strs(data->cmd2);
	if (data->path_cmd1)
		free_strs(data->path_cmd1);
	if (data->path_cmd2)
		free_strs(data->path_cmd2);
	close(data->fd1);
	close(data->fd2);
}

/* This function manages errors. */

void	error_mng(char *type, int is_perror, t_data *data)
{
	if (data)
		free_struct(data);
	if (type && is_perror)
		perror(type);
	else if (type)
		write(STDERR_FILENO, type, ft_strlen(type));
	exit(EXIT_FAILURE);
}
