
#include "ft_ls.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "libft_ext.h"
#include "utils.h"

static void	print_permisions(mode_t mode)
{
	//	printing the file type
	if (S_ISLNK(mode))
		ft_printf("l");
	else if (S_ISREG(mode))
		ft_printf("-");
	else if (S_ISDIR(mode))
		ft_printf("d");
	else if (S_ISCHR(mode))
		ft_printf("c");
	else if (S_ISBLK(mode))
		ft_printf("b");
	else if (S_ISFIFO(mode))
		ft_printf("p");
	else if (S_ISSOCK(mode))
		ft_printf("s");
	else
		ft_printf("x");

	//	printing the permisions.
	
	//	owner permisions.
	if (mode & S_IRUSR)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWUSR)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXUSR)
		ft_printf("x");
	else if (mode & S_ISUID)
		ft_printf("S");
	else
		ft_printf("-");
	
	//	owner permisions.
	if (mode & S_IRGRP)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWGRP)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXGRP)
		ft_printf("x");
	else if (mode & S_ISGID)
		ft_printf("S");
	else
		ft_printf("-");
	
	//	owner permisions.
	if (mode & S_IROTH)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWOTH)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXOTH)
		ft_printf("x ");
	else if (mode & S_ISVTX)
		ft_printf("T ");
	else
		ft_printf("- ");
}

static char	*get_fmt_str(size_t slot_size, char *type, char *ord)
{
	char	*size_str = ft_itoa(slot_size);
	if (!size_str)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	char	*tmp = ft_strjoin(ord, size_str);
	if (!tmp)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	free(size_str);
	char	*fmt_str = ft_strjoin(tmp, type);
	if (!fmt_str)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	free(tmp);
	return (fmt_str);
}

static void	print_num(size_t num, size_t slot_size)
{
	char	*fmt_str = get_fmt_str(slot_size, "i ", "%");
	ft_printf(fmt_str, num);
	free(fmt_str);
}

static void	print_user(uid_t uid, size_t slot_size)
{
	char	*fmt_str = get_fmt_str(slot_size, "s ", "%-");
	struct passwd	*user_info = getpwuid(uid);
	ft_printf(fmt_str, user_info->pw_name);
	free(fmt_str);
}

static void	print_group(gid_t gid, size_t slot_size)
{
	char	*fmt_str = get_fmt_str(slot_size, "s ", "%-");
	struct group	*group_info = getgrgid(gid);
	ft_printf(fmt_str, group_info->gr_name);
	free(fmt_str);
}

void	print_file(struct file_info *file, unsigned int options_bitf)
{
	if (options_bitf & LS_ARGS_OPT_FMT_LONG)
	{
		print_permisions(file->mode);
		print_num(file->nlink, file->nlink_num_size);
		print_user(file->uid, file->user_name_size);
		print_group(file->gid, file->group_name_size);
		print_num(file->size, file->size_num_size);
	}
	ft_printf("%s\n", file->name);
}
