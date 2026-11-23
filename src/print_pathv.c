
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
			y++;
		}
		i++;
	}
	ctx->pathc = y;
}

//	return 0 the first is smaller or equal.
//	return 1 if the first is biger.
static int	file_cmp(struct file_info *file1, struct file_info *file2)
{
	if (S_ISDIR(file1->mode) && !S_ISDIR(file2->mode))
		return (1);
	if (!S_ISDIR(file1->mode) && S_ISDIR(file2->mode))
		return (0);
	if (ft_strncmp(file1->name, file2->name, -1) > 0)
		return (1);
	return (0);
}

static void	order_filev(int filec, struct file_info **filev)
{
	int	i = 0;

	while (i < (filec - 1))
	{
		int	smallest = i;
		int	current = i + 1;
		while (current < filec)
		{
			if (file_cmp(filev[smallest], filev[current]))
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
		print_file(filev[i], option_bitf);
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
	
	order_filev(ctx->pathc, filev);
	
	debug_print_filev(filev);
	print_filev(filev, ctx->option_bitf);
}
