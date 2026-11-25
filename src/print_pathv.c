
#include "ft_ls.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft_ext.h"

static void	
fill_file_buff(struct file_info *file_buff, struct file_info **filev, struct ls_args *ctx)
{
	struct stat	statbuf;

	int	i = 0;
	int	y = 0;
	while (i < ctx->pathc)
	{
		filev[y] = &file_buff[y];
		file_buff[y].name = ctx->pathv[i];
		if (stat(file_buff[y].name, &statbuf) == -1)
		{
			if (errno == ENOENT)
				ft_printfe("ls: cannot access '%s': "
					"No such file or directory\n", file_buff[y].name);
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
			y++;
		}
		i++;
	}
	filev[y] = NULL;
	ctx->pathc = y;
}

//	return 0 the first is smaller or equal.
//	return 1 if the first is biger.
static int
file_cmp(struct file_info *file1, struct file_info *file2, unsigned int option_bitf)
{
	if (S_ISDIR(file1->mode) && !S_ISDIR(file2->mode))
		return (1);
	if (!S_ISDIR(file1->mode) && S_ISDIR(file2->mode))
		return (0);
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

static void	sort_filev(int filec, struct file_info **filev, unsigned int option_bitf)
{
	int	i = 0;

	while (i < (filec - 1))
	{
		int	smallest = i;
		int	current = i + 1;
		while (current < filec)
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

static void	debug_print_filev(struct file_info **filev)
{
	if (!DEBUG)
		return ;
	ft_printf("print filev:\n");
	int	i = 0;
	while (filev[i])
	{
		ft_printf("\t%s\n", filev[i]->name);
		i++;
	}
}

static void	print_filev(struct file_info **filev, unsigned int option_bitf)
{
	int	i = 0;
	while (filev[i])
	{
		if (S_ISDIR(filev[i]->mode))
			print_dir(filev[i], option_bitf);
		else
			print_file(filev[i], option_bitf);
		if (filev[i + 1] && S_ISDIR(filev[i + 1]->mode))
			ft_printf("\n");
		i++;
	}
}

void	print_pathv(struct ls_args *ctx)
{
	//	setting up the filev.
	struct file_info	*file_buff;
	struct file_info	**filev;

	file_buff = malloc(sizeof(struct file_info) * (ctx->pathc + 1));
	if (!file_buff)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	filev = malloc(sizeof(struct file_info *) * (ctx->pathc + 1));
	if (!file_buff)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	
	fill_file_buff(file_buff, filev, ctx);
	
	sort_filev(ctx->pathc, filev, ctx->option_bitf);

	if (ctx->option_bitf & LS_ARGS_OPT_FMT_LONG)
		calc_slot_size(filev);
	
	debug_print_filev(filev);
	print_filev(filev, ctx->option_bitf);
	free(file_buff);
	free(filev);
}
