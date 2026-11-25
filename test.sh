#!/usr/bin/env bash
export LC_ALL=C

mkdir -p test_diff

function run_diff ()
{

	ls $@ | cat \
		1> test_diff/ls_stdout_for_\("$*"\).test.out \
		2> test_diff/ls_stderr_for_\("$*"\).test.out;

	./ft_ls $@ \
		1> test_diff/ft_ls_stdout_for_\("$*"\).test.out \
		2> test_diff/ft_ls_stderr_for_\("$*"\).test.out;

	diff \
		test_diff/ls_stdout_for_\("$*"\).test.out \
		test_diff/ft_ls_stdout_for_\("$*"\).test.out \
		> test_diff/diff_stdout_for_\("$*"\).test.out ;

	diff \
		test_diff/ls_stderr_for_\("$*"\).test.out \
		test_diff/ft_ls_stderr_for_\("$*"\).test.out \
		> test_diff/diff_stderr_for_\("$*"\).test.out ;

	if [ -s test_diff/diff_stdout_for_\("$*"\).test.out ]; then
		return 1;
	fi
	if [ -s test_diff/diff_stderr_for_\("$*"\).test.out ]; then
		return 1;
	fi
	return 0;
}

function test_ls ()
{
	if run_diff $@; then
		echo $'\033[32;1msuccess on:\t\033[0m'ls $@
	else
		echo $'\033[31;1merror on:\t\033[0m'ls $@
	fi
}

test_ls
test_ls -r -rrrrr -t
test_ls src
test_ls .
test_ls Makefile src test.sh
test_ls -t
test_ls -tr -r
test_ls Makefile src test.sh -rt
test_ls Makefile src test.sh -tr
test_ls Makefile src test.sh -t
test_ls src -r
test_ls src inc submodules
test_ls src -rR

