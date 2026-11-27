
#include "ft_ls.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "libft_ext.h"
#include "utils.h"


static int
file_cmp(struct file_info *file1, struct file_info *file2, unsigned int option_bitf)
{
	int	dif = 0;

	if (option_bitf & LS_ARGS_OPT_ORD_TM)
	{
		if (file1->last_mod.tv_sec == file2->last_mod.tv_sec)
			dif = file2->last_mod.tv_nsec - file1->last_mod.tv_nsec;
		else
			dif = file2->last_mod.tv_sec - file1->last_mod.tv_sec;
	}
	if (dif == 0)
		dif = ft_strncmp(file1->name, file2->name, -1);
	if (option_bitf & LS_ARGS_OPT_ORD_REV)
		return (dif < 0);
	return (dif > 0);
}


static char	**get_dir_file_names(char *path, unsigned int options_bitf)
{
	DIR	*dir = opendir(path);
	if (!dir)
	{
		if (errno == EACCES)
		{
			ft_printfe("ls: cannot open directory '%s': "
				"Permission denied\n", path);
			return (NULL);
		}
		else
		{
			ft_printfe("ls: %s\n", strerror(errno));
			exit(1);
		}
	}
	t_list	*name_list = NULL;

	struct dirent	*dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_name[0] != '.' || options_bitf & LS_ARGS_OPT_ALL)
		{
			char	*name_cpy = ft_strdup(dirent->d_name);
			if (!name_cpy)
			{
				ft_printfe("ls: %s\n", strerror(errno));
				exit(1);
			}
			t_list	*node= ft_lstnew(name_cpy);
			if (!node)
			{
				ft_printfe("ls: %s\n", strerror(errno));
				exit(1);
			}
			ft_lstadd_front(&name_list, node);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	char	**ret = (char **)ft_lst_to_arr(name_list);
	if (!ret)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	return (ret);
}


static void	
fill_file_buff(struct file_info *file_buff, \
		struct file_info **filev, \
		char **files, \
		char **paths, \
		unsigned int option_bitf)
{
	struct stat	statbuf;

	int	i = 0;
	int	y = 0;
	while (files[i])
	{
		filev[y] = &file_buff[y];
		file_buff[y].name = files[i];
		file_buff[y].path = paths[i];
		int ret_val;
		(void)option_bitf;
//		if (option_bitf & LS_ARGS_OPT_FMT_LONG)
			ret_val = lstat(paths[i], &statbuf);
//		else
//			ret_val = stat(paths[i], &statbuf);
		if (ret_val == -1)
		{
			if (errno == ENOENT)
				ft_printfe("ls: cannot access '%s': "
					"No such file or directory\n", file_buff[y].name);
			if (errno == EACCES)
				ft_printfe("ls: cannot open directory '%s': "
					"Permission denied\n", file_buff[y].name);
			else
				ft_printfe("ls: %s\n", strerror(errno));
		}
		else
		{
			file_buff[y].mode = statbuf.st_mode;
			file_buff[y].nlink = statbuf.st_nlink;
			file_buff[y].uid = statbuf.st_uid;
			file_buff[y].gid = statbuf.st_gid;
			file_buff[y].size = statbuf.st_size;
			file_buff[y].last_mod = statbuf.st_mtim;
			file_buff[y].blocks = statbuf.st_blocks;
			y++;
		}
		i++;
	}
	filev[y] = NULL;
}


static void	print_filev(struct file_info **filev, unsigned int option_bitf)
{
	int	i = 0;
	while (filev[i])
	{
		print_file(filev[i], option_bitf);
		i++;
	}
}

static char	**add_path(char *path, char **files)
{
	char	*new_path;
	if (path[ft_strlen(path) - 1] != '/')
	{
		new_path = ft_strjoin(path, "/");
		if (!new_path)
		{
			ft_printfe("ls: %s\n", strerror(errno));
			exit(1);
		}
	}
	else
		new_path = path;
	char	**new_pathv = malloc(sizeof(char *) * (arr_len((void **)files) + 1));
	if (!new_pathv)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	new_pathv[arr_len((void **)files)] = NULL;
	int	i = 0;
	while (files[i])
	{
		new_pathv[i] = ft_strjoin(new_path, files[i]);
		if (!new_pathv[i])
		{
			ft_printfe("ls: %s\n", strerror(errno));
			exit(1);
		}
		i++;
	}
	if (path[ft_strlen(path) - 1] != '/')
		free(new_path);
	return (new_pathv);
}

static void	sort_filev(struct file_info **filev, unsigned int option_bitf)
{
	if (!filev[0] || !filev[1])
		return ;
	int	i = 0;
	while (filev[i + 1])
	{
		int	smallest = i;
		int	current = i + 1;
		while (filev[current])
		{
			if (file_cmp(filev[smallest], filev[current], option_bitf))
				smallest = current;
			current++;
		}
		struct file_info *tmp;
		tmp = filev[i];
		filev[i] = filev[smallest];
		filev[smallest] = tmp;
		i++;
	}
}

static void	print_total_block_size(struct file_info **filev)
{
	size_t	total = 0;
	int	i = 0;
	while (filev[i])
	{
		total += filev[i]->blocks;
		i++;
	}
	//	I feel wrong about this because the standard says to use 512 blocks 
	//	but the coreutils uses 1k
	total = total >> 1;
	ft_printf("total %u\n", total);
}

static void	print_subdir(struct file_info **filev, unsigned int option_bitf)
{
	int	i = 0;
	while (filev[i])
	{
		if (S_ISDIR(filev[i]->mode) && 
			ft_strncmp(".", filev[i]->name, -1) != 0 &&
			ft_strncmp("..", filev[i]->name, -1) != 0)
		{
			ft_printf("\n");
			print_dir(filev[i], option_bitf);
		}
		i++;
	}
}

void	print_dir(struct file_info *file, unsigned int option_bitf)
{
	char	**names = get_dir_file_names(file->path, option_bitf);
	if (!names)
	{
		return ;
	}
	char	**paths = add_path(file->path, names);
	
	if (!(option_bitf & LS_ARGS_ONE_DIR))
		ft_printf("%s:\n", file->path);

	struct file_info	*file_buff;
	struct file_info	**filev;

	file_buff = malloc(sizeof(struct file_info) * (arr_len((void **)names) + 1));
	if (!file_buff)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	filev = malloc(sizeof(struct file_info *) * (arr_len((void **)names) + 1));
	if (!file_buff)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}

	fill_file_buff(file_buff, filev, names, paths, option_bitf);
	sort_filev(filev, option_bitf);
	
	if (option_bitf & LS_ARGS_OPT_FMT_LONG)
	{
		calc_slot_size(filev);
		print_total_block_size(filev);
	}
	
	print_filev(filev, option_bitf);
	if (option_bitf & LS_ARGS_OPT_RECURSE)
		print_subdir(filev, option_bitf);

	free_arr((void **)names, free);
	free_arr((void **)paths, free);
	free(file_buff);
	free(filev);
}

