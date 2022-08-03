/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:34:13 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/08/03 14:44:32 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function finds all the possible paths for a command. */

char	**find_path(char *cmd[], char *envp[], t_data *data)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	path = ft_split(envp[i] + 5, ':', data);
	i = 0;
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin(path[i], "/", data);
		path[i] = ft_strjoin(path[i], cmd[0], data);
		i++;
	}
	return (path);
}

/* This function finds the path for a command. */

char	*access_path(char *path_cmd[], t_data *data)
{
	int	i;

	i = 0;
	while (path_cmd[i])
	{
		if (access(path_cmd[i], F_OK | X_OK) == 0)
			return (path_cmd[i]);
		i++;
	}
	error_mng("Command not found\n", 0, data);
	return (NULL);
}
