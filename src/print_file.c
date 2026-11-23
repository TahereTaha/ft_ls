
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

static int	file_name_cmp(char *name1, char *name2)
{
	int	val = ft_strncmp(name1, name2, -1);
	if (val <= 0)
		return (0);
	return (1);
}

static char	**get_dir_file_names(char *path, unsigned int options_bitf)
{
	DIR	*dir = opendir(path);
	if (!dir)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
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
	ft_lstsort(name_list, (t_sort_cmp)file_name_cmp);
	closedir(dir);
	char	**ret = (char **)ft_lst_to_arr(name_list);
	if (!ret)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	return (ret);
}

static void	print_dir(struct file_info *file, unsigned int option_bitf)
{
	if (!(option_bitf & LS_ARGS_ONE_DIR))
		ft_printf("\n%s:\n", file->name);
	char	**names = get_dir_file_names(file->name, option_bitf);
	int	i = 0;
	while (names[i])
	{
		ft_printf("%s\n", names[i]);
		i++;
	}
	free_arr((void **)names, free);
}

void	print_file(struct file_info *file, unsigned int options_bitf)
{
	if (S_ISDIR(file->mode))
	{
		print_dir(file, options_bitf);
		return ;
	}
	ft_printf("%s\n", file->name);
}
