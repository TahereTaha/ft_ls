
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "libft_ext.h"

void	**arr_map(void **arr, void *(*f)(void *))
{
	void	**new_arr = malloc(sizeof(void *) * (arr_len(arr) + 1));
	if (!new_arr)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	int	i = 0;
	while (arr[i])
	{
		new_arr[i] = f(arr[i]);
		i++;
	}
	return (new_arr);
}

