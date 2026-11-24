#ifndef FT_LS_H
# define FT_LS_H

#include <aio.h>
#include <sys/types.h>
#include <sys/stat.h>

//
//	flags.
//


# define DEBUG 0


//
//	ft_ls.
//


struct ls_args {
	unsigned int	option_bitf;
	int		pathc;
	char		**pathv;
};

//	the option_bitf is a bit field representing the presence of each binary flag.
# define LS_ARGS_OPT_FMT_LONG	1 << 0
# define LS_ARGS_OPT_RECURSE	1 << 1
# define LS_ARGS_OPT_ALL	1 << 2
# define LS_ARGS_OPT_ORD_REV	1 << 3
# define LS_ARGS_OPT_ORD_TM	1 << 4
# define LS_ARGS_ONE_DIR	1 << 5

//	in case of error this doesn't return and prints the error msg and exits.
void	parse_args(int ac, char **av, struct ls_args *ctx);

void	print_pathv(struct ls_args *ctx);

struct	file_info {
	mode_t		mode;
	struct timespec	last_mod;
	char		*name;
};


void	print_file(struct file_info *file, unsigned int options);

void	print_dir(struct file_info *file, unsigned int options);

//
//	utils. to be moved to the libft eventualy.
//

//
//	test functions.
//


void	test(char *path);

#endif
