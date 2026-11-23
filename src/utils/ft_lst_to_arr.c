#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "libft_ext.h"

static void	do_nothing(void *val)
{
	(void)val;
}

void	**ft_lst_to_arr(t_list *lst)
{
	size_t	list_size = ft_lstsize(lst);
	void	**vec = malloc(sizeof(void *) * (list_size + 1));
	if (!vec)
	{
		ft_printfe("ls: %s\n", strerror(errno));
		exit(1);
	}
	vec[list_size] = NULL;
	if (list_size == 0)
		return (vec);
	t_list	*node = lst;
	int	i = 0;
	while (node)
	{
		vec[i] = node->content;
		node = node->next;
		i++;
	}
	ft_lstclear(&lst, do_nothing);
	return (vec);
}
