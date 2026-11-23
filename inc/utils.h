
#ifndef UTILS_H
# define UTILS_H

# include "ft_list.h"

//	the cmp funciton will return 0 if the contents are in assending order or equal 
//	and return 1 otherwise
void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *));

typedef int (*t_sort_cmp)(void *, void *);

void	**ft_lst_to_arr(t_list *lst);

void	free_arr(void **arr, void (*f_free)(void *));

#endif

