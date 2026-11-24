
#include "utils.h"

#include <stdlib.h>

int	arr_len(void **arr)
{
	int	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

