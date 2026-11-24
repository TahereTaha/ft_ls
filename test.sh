#!/usr/bin/env bash
export LC_ALL=C

function run_diff ()
{

	ls $@ | cat \
		1> ls_stdout_for_\("$*"\).test.out \
		2> ls_stderr_for_\("$*"\).test.out;

	./ft_ls $@ \
		1> ft_ls_stdout_for_\("$*"\).test.out \
		2> ft_ls_stderr_for_\("$*"\).test.out;

	diff \
		ls_stdout_for_\("$*"\).test.out \
		ft_ls_stdout_for_\("$*"\).test.out \
		> diff_stdout_for_\("$*"\).test.out ;

	diff \
		ls_stderr_for_\("$*"\).test.out \
		ft_ls_stderr_for_\("$*"\).test.out \
		> diff_stderr_for_\("$*"\).test.out ;

	if [ -s diff_stdout_for_\("$*"\).test.out ]; then
		return 1;
	fi
	if [ -s diff_stderr_for_\("$*"\).test.out ]; then
		return 1;
	fi
	return 0;
}

function test_ls ()
{
	if run_diff $@; then
		echo success on ls with \"$@\"
	else
		echo error on ls with \"$@\"
	fi
}

test_ls
test_ls -r -rrrrr -t
test_ls
test_ls src
test_ls .
test_ls Makefile src test.sh
test_ls -t
test_ls -tr -r
test_ls Makefile src test.sh -rt
test_ls Makefile src test.sh -tr
test_ls Makefile src test.sh -t

test_ls src -r
test_ls src -rR

