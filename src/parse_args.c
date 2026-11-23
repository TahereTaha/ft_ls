
#include "ft_ls.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libft_ext.h"


static void	parse_arg_options(char *options, struct ls_args *ctx)
{
	int	i = 1;
	while (options[i])
	{
		if (options[i] == 'l')
			ctx->option_bitf |= LS_ARGS_OPT_FMT_LONG;
		else if (options[i] == 'R')
			ctx->option_bitf |= LS_ARGS_OPT_RECURSE;
		else if (options[i] == 'a')
			ctx->option_bitf |= LS_ARGS_OPT_ALL;
		else if (options[i] == 'r')
			ctx->option_bitf |= LS_ARGS_OPT_ORD_REV;
		else if (options[i] == 't')
			ctx->option_bitf |= LS_ARGS_OPT_ORD_TM;
		else
		{
			ft_printf("ls: invalid option -- '%c'\n", options[i]);
			ft_printf("Try 'ls --help' for more information.");
		}
		i++;
	}
}

static void	debug_print_ls_args(struct ls_args *ctx)
{
	if (!DEBUG)
		return ;
	ft_printf("ls_args:\n");
	
	//	printing options.
	
	ft_printf("\toptions: ");
	
	if (ctx->option_bitf)
		ft_printf("-");
	else
		ft_printf("none");
	
	if (ctx->option_bitf & LS_ARGS_OPT_FMT_LONG)
		ft_printf("l");
	if (ctx->option_bitf & LS_ARGS_OPT_RECURSE)
		ft_printf("R");
	if (ctx->option_bitf & LS_ARGS_OPT_ALL)
		ft_printf("a");
	if (ctx->option_bitf & LS_ARGS_OPT_ORD_REV)
		ft_printf("r");
	if (ctx->option_bitf & LS_ARGS_OPT_ORD_TM)
		ft_printf("t");
	
	ft_printf("\n");

	//	printing the pathv
	
	ft_printf("\tpaths:\n");
	
	int	i = 0;
	while (ctx->pathv[i])
	{
		ft_printf("\t\t%s\n", ctx->pathv[i]);
		i++;
	}
}

void	parse_args(int ac, char **av, struct ls_args *ctx)
{
	int	pathc = 0;

	ctx->option_bitf = 0;
	ctx->pathv = av;

	int	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && ft_strlen(av[i]) > 1)
			parse_arg_options(av[i], ctx);
		else
		{
			ctx->pathv[pathc] = av[i];
			pathc++;
		}
		i++;
	}


	if (pathc == 0)
	{
		ft_strlcpy(ctx->pathv[0], ".", 2);
		ctx->pathv[1] = NULL;
		pathc++;
	}
	else
		ctx->pathv[pathc] = NULL;
	ctx->pathc = pathc;

	if (ctx->pathc == 1)
	{
		struct stat	statbuf;
		if (stat(ctx->pathv[0], &statbuf))
		{
			ft_printf("ls: %s\n", strerror(errno));
			exit(1);
		}
		if (S_ISDIR(statbuf.st_mode))
			ctx->option_bitf |= LS_ARGS_ONE_DIR;
	}

	debug_print_ls_args(ctx);
}

