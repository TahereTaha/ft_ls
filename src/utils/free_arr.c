
#include "utils.h"

#include <stdlib.h>

void	free_arr(void **arr, void (*f_free)(void *))
{
	int	i = 0;
	while (arr[i])
	{
		f_free(arr[i]);
		i++;
	}
	free(arr);
}

