#include "libft_ext.h"

#include "ft_ls.h"

int	main(int ac, char **av)
{
	int	err = 0;
	struct ls_args	args_ctx;
	parse_args(ac, av, &args_ctx);

	err = print_pathv(&args_ctx);

//	// test code.	
//	ft_printf("hola mundo esto es ft_ls\n");
//	test(av[1]);
	if (err)
		return (2);
	return (0);
}

