
#include "ft_ls.h"

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#include "libft_ext.h"

static size_t	get_num_size(size_t num)
{
	if (num == 0)
		return (1);
	size_t	size = 0;
	while (num)
	{
		size++;
		num = num / 10;
	}
	return (size);
}

void	calc_slot_size(struct file_info **filev)
{
	size_t	bigest_nlink = 0;
	size_t	bigest_user = 0;
	size_t	bigest_group = 0;
	size_t	bigest_size = 0;

	int	i = 0;
	while (filev[i])
	{
		size_t	current_nlink;
		size_t	current_user;
		size_t	current_group;
		size_t	current_size;

		current_nlink = get_num_size(filev[i]->nlink);
		
		struct passwd	*user_info = getpwuid(filev[i]->uid);
		current_user = ft_strlen(user_info->pw_name);
		
		struct group	*group_info = getgrgid(filev[i]->gid);
		current_group = ft_strlen(group_info->gr_name);
		
		current_size = get_num_size(filev[i]->size);

		if (current_nlink > bigest_nlink)
			bigest_nlink = current_nlink;
		if (current_user > bigest_user)
			bigest_user = current_user;
		if (current_group > bigest_group)
			bigest_group = current_group;
		if (current_size > bigest_size)
			bigest_size = current_size;
		i++;
	}
	i = 0;
	while (filev[i])
	{
		filev[i]->nlink_num_size = bigest_nlink;
		filev[i]->user_name_size = bigest_user;
		filev[i]->group_name_size = bigest_group;
		filev[i]->size_num_size = bigest_size;
		i++;
	}
}
