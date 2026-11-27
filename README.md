*his project has been created as part of the 42 curriculum by tatahere*

# Description

this project consists of a minimal implementation of the ls command, with a reduced set of options being -l, -R, -a, -r and -t, there is no managment of collums in the absence of -l.

# Instructions
# Resources
# Todo list
- [x]	reserch the requirements of this ft_ls.
- [x]	update my libft.
	- [x]	add a gitignore file.
	- [x]	remove btree and tree.
	- [x]	add printf.
- [x]	add my libft as a submodule.
- [x]	add a gitignore file.
- [x]	build a makefile.
- [x]	get aquainted with the function needed to get all the info from the files and folders.
	- [x]	list all the contents of a folder.
	- [x]	get important info.
		- [x]	type.
		- [x]	permisions.
		- [x]	hard link count.
		- [x]	user.
		- [x]	group.
		- [x]	size.
		- [x]	time.
		- [x]	name.
		- [x]	link.
- [x]	parse the args.
- [x]	print correctly all the paths on the terminal.
	- [x]	print the info expecting no errors.
	- [x]	add correct notification of errors.
- [x]	handle correctly the -a.
- [x]	separate the print file and print folder.
- [x]	handle correctly the -r and -t.
- [x]	add some kind of testing.
- [x]	handle correctly the -l.
- [x]	handle correctly the -R.
- [x]	find errors and fix them.
- [ ]	write a nice documentation.

bugs:
- [x]	important bug. add a version of printf that prints to the stderr for error mesages.
- [x]	important bug. ft_ls print a extra new line at the start with `./ft_ls dir1 dir2`
- [x]	important bug. fix all the failed testcases.
- [x]	the special permision on the group the s is uppercase not lower.
- [x]	inacesible files give only a generic error.
- [x]	error for unexistent flags doesn't exit and runs the ls command.
- [x]	return correct error status after errors.

