#include "libft_ext.h"

#include "ft_ls.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (42);
	ft_printf("hola mundo esto es ft_ls\n");
	test(av[1]);
	return (0);
}

