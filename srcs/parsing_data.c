/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:55:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:23 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_str_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char	**parsing_paths(t_pipex *pipex)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = find_str_path(pipex->envp);
	if (!tmp1)
		end_program(ERROR_NO_PATHS_IN_ENVP, pipex, 0);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		end_program(ERROR_PARSING_PATHS, pipex, 0);
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		end_program(ERROR_PARSING_PATHS, pipex, 0);
	}
	free (tmp2);
	return (paths);
}

static char	*search_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			end_program(ERROR_SEARCH_PATH_CMD, pipex, 0);
		filename = ft_strjoin(tmp, cmd);
		if (!filename)
			end_program(ERROR_SEARCH_PATH_CMD, pipex, 0);
		free(tmp);
		if (!access(filename, X_OK))
			return (filename);
		i++;
		free(filename);
	}
	return (NULL);
}

void	parsing_data(t_pipex *pipex, char **argv, char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2)
		end_program(ERROR_SPLIT_CMD, pipex, 0);
	pipex->paths = parsing_paths(pipex);
	pipex->path1 = search_path(pipex, pipex->cmd1[0]);
	pipex->path2 = search_path(pipex, pipex->cmd2[0]);
	if (!pipex->path1 || !pipex->path2)
		end_program(ERROR_NO_PATH_CMD, pipex, errno);
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile < 0)
		end_program(ERROR_OPEN_FILE_READ, pipex, errno);
	pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		end_program(ERROR_OPEN_FILE_WRITE, pipex, errno);
	}
}
