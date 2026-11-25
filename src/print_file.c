
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

void	print_file(struct file_info *file, unsigned int options_bitf)
{
	(void)options_bitf;
	if (!(options_bitf & LS_ARGS_OPT_ALL))
	{
		ft_printf("%s\n", file->name);
		return ;
	}
	
}
