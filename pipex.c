/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:47:50 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/08/03 14:38:37 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function initialises the data structure. */

void	init_data(t_data *data, char *argv[], char *envp[])
{
	data->fd1 = open(argv[1], O_RDONLY);
	data->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->fd1 < 0 || data->fd2 < 0)
		error_mng("Open error", 1, data);
	data->cmd1 = ft_split(argv[2], ' ', data);
	data->path_cmd1 = find_path(data->cmd1, envp, data);
	data->cmd2 = ft_split(argv[3], ' ', data);
	data->path_cmd2 = find_path(data->cmd2, envp, data);
}

/* This is child one which executes the first command. */

void	child_one(t_data *data, char *envp[])
{
	int	exec;

	if (dup2(data->fd1, STDIN_FILENO) < 0)
		error_mng("Dup error", 1, data);
	if (dup2(data->pipe[1], STDOUT_FILENO) < 0)
		error_mng("Dup error", 1, data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	exec = execve(access_path(data->path_cmd1, data), data->cmd1, envp);
	if (exec < 0)
		error_mng("Command", 1, data);
}

/* This is child two which executes the second command. */

void	child_two(t_data *data, char *envp[])
{
	int	exec;

	if (dup2(data->pipe[0], STDIN_FILENO) < 0)
		error_mng("Dup error", 1, data);
	if (dup2(data->fd2, STDOUT_FILENO) < 0)
		error_mng("Dup error", 1, data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	exec = execve(access_path(data->path_cmd2, data), data->cmd2, envp);
	if (exec < 0)
		error_mng("Command", 1, data);
}

/* This is the parent which waits on both children. */

void	parent(t_data *data, char *envp[], int *status)
{
	int	p;

	p = pipe(data->pipe);
	if (pipe(data->pipe))
		error_mng("Pipe error", 1, data);
	data->pid1 = fork();
	if (data->pid1 < 0)
		error_mng("Fork error", 1, data);
	else if (data->pid1 == 0)
		child_one(data, envp);
	else
	{
		data->pid2 = fork();
		if (data->pid2 < 0)
			error_mng("Fork error", 1, data);
		else if (data->pid2 == 0)
			child_two(data, envp);
		else
		{
			close(data->pipe[0]);
			close(data->pipe[1]);
			waitpid(data->pid1, status, 0);
			waitpid(data->pid2, status, 0);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		status;

	if (argc == 5)
	{
		init_data(&data, argv, envp);
		parent(&data, envp, &status);
		free_struct(&data);
	}
	else
	{
		write(2, "Invalid number of arguments\n", 29);
		exit(EXIT_FAILURE);
	}
	return ((status >> 8) & 0xff);
}
