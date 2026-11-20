#include "ft_ls.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "dirent.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft_ext.h"
#include <pwd.h>
#include <grp.h>

#define DEBUG 0

enum file_type {
	FILE_TYPE_NONE,
	FILE_TYPE_REG,
	FILE_TYPE_DIR,
	FILE_TYPE_CHRDEV,
	FILE_TYPE_BLKDEV,
	FILE_TYPE_FIFO,
	FILE_TYPE_SYMLINK,
	FILE_TYPE_SOCK,
};

enum	file_type	get_file_type(unsigned int val)
{
	if (S_ISREG(val))
		return (FILE_TYPE_REG);
	if (S_ISDIR(val))
		return (FILE_TYPE_DIR);
	if (S_ISCHR(val))
		return (FILE_TYPE_CHRDEV);
	if (S_ISBLK(val))
		return (FILE_TYPE_BLKDEV);
	if (S_ISFIFO(val))
		return (FILE_TYPE_FIFO);
	if (S_ISLNK(val))
		return (FILE_TYPE_SYMLINK);
	if (S_ISSOCK(val))
		return (FILE_TYPE_SOCK);
	return (FILE_TYPE_NONE);
}

char	get_file_type_char(enum file_type type)
{
	if (type == FILE_TYPE_REG)
		return ('-');
	if (type == FILE_TYPE_DIR)
		return ('d');
	if (type == FILE_TYPE_CHRDEV)
		return ('c');
	if (type == FILE_TYPE_BLKDEV)
		return ('b');
	if (type == FILE_TYPE_FIFO)
		return ('p');
	if (type == FILE_TYPE_SYMLINK)
		return ('l');
	if (type == FILE_TYPE_SOCK)
		return ('s');
	return ('x');
}

unsigned int	get_mode_field(unsigned int val)
{
	return (((1 << 12) - 1) & val);
}

char	*get_mode_str(unsigned int val)
{
	static char	str[10];
	str[9] = '\0';

	str[0] = '-';
	str[1] = '-';
	str[2] = '-';
	str[3] = '-';
	str[4] = '-';
	str[5] = '-';
	str[6] = '-';
	str[7] = '-';
	str[8] = '-';

	if (val & S_IRUSR)
		str[0] = 'r';
	if (val & S_IWUSR)
		str[1] = 'w';
	if (val & S_IXUSR)
		str[2] = 'x';

	if (val & S_IRGRP)
		str[3] = 'r';
	if (val & S_IWGRP)
		str[4] = 'w';
	if (val & S_IXGRP)
		str[5] = 'x';

	if (val & S_IROTH)
		str[6] = 'r';
	if (val & S_IWOTH)
		str[7] = 'w';
	if (val & S_IXOTH)
		str[8] = 'x';

	if (val & S_ISUID)
		str[2] = 'S';
	if (val & S_ISGID)
		str[5] = 'S';
	if (val & S_ISVTX)
		str[8] = 'T';
	return (str);
}

void	test(char *path)
{
	DIR	*dir;
	dir = opendir(path);

	struct dirent *ent;
	ent = readdir(dir);
	while (ent)
	{
		char	*file_path;
		if (path[ft_strlen(path) - 1] != '/')
		{
			file_path = ft_strjoin(path, "/");
			file_path = ft_strjoin(file_path, ent->d_name);
		}
		else
			file_path = ft_strjoin(path, ent->d_name);
		struct stat statbuff;
		if (DEBUG)
			printf("ino: %10lx, len: %4u, type: %4u, name: %s \n", 
				ent->d_ino, 
				ent->d_reclen, 
				ent->d_type,
				ent->d_name);
		stat(file_path, &statbuff);
		if (DEBUG)
			printf("mode: %10x, nlink: %4lu, user %10x, group %10x, size: %10ld\n",
				statbuff.st_mode,
				statbuff.st_nlink,
				statbuff.st_uid,
				statbuff.st_gid,
				statbuff.st_size);
		enum file_type	type = get_file_type(statbuff.st_mode);
		char	type_char = get_file_type_char(type);
		unsigned int mode = get_mode_field(statbuff.st_mode);
		char	*mode_str = get_mode_str(mode);
		struct passwd	*user_info = getpwuid(statbuff.st_uid);
		struct group	*group_info = getgrgid(statbuff.st_gid);
		printf("type: %c, "
			"permisions: %s, "
			"hl count: %3lu, "
			"user: %15s, "
			"group: %15s, "
			"size: %10lu, "
			"time: x, "
			"name: %s\n", 
			type_char,
			mode_str,
			statbuff.st_nlink,
			user_info->pw_name,
			group_info->gr_name,
			statbuff.st_size,
			ent->d_name);
		ent = readdir(dir);
	}
}

