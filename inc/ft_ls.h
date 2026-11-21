#ifndef FT_LS_H
# define FT_LS_H

#include <aio.h>

//
//	flags.
//

# define DEBUG 1

//
//	ft_ls.
//

struct ls_args {
	unsigned int	option_bitf;
	char		**pathv;
};

//	the option_bitf is a bit field representing the presence of each binary flag.
# define LS_ARGS_OPT_FMT_LONG	1 << 0
# define LS_ARGS_OPT_RECURSE	1 << 1
# define LS_ARGS_OPT_ALL	1 << 2
# define LS_ARGS_OPT_ORD_REV	1 << 3
# define LS_ARGS_OPT_ORD_TM	1 << 4

//	in case of error this doesn't return and prints the error msg and exits.
void	parse_args(int ac, char **av, struct ls_args *ctx);

void	debug_print_ls_args(struct ls_args *ctx);

//
//	utils. to be moved to the libft eventualy.
//

//
//	debug functions.
//

//
//	test functions.
//


void	test(char *path);

#endif
