#!/usr/bin/env bash
export LC_ALL=C

rm -rf test_diff
mkdir -p test_diff

function run_diff ()
{
	if ls test_diff/diff_stdout_test"$1".test.out 1> /dev/null 2> /dev/null; then
		echo $'\033[31;1mTWO TEST CASES WITH THE SAME ID\033[0m'ls
		exit 1
	fi

	test_id=$1

	shift

	ls $@ | cat \
		1> test_diff/ls_stdout_test"$test_id".test.out \
		2> test_diff/ls_stderr_test"$test_id".test.out;

	./ft_ls $@ \
		1> test_diff/ft_ls_stdout_test"$test_id".test.out \
		2> test_diff/ft_ls_stderr_test"$test_id".test.out;

	diff \
		test_diff/ls_stdout_test"$test_id".test.out \
		test_diff/ft_ls_stdout_test"$test_id".test.out \
		> test_diff/diff_stdout_test"$test_id".test.out ;

	diff \
		test_diff/ls_stderr_test"$test_id".test.out \
		test_diff/ft_ls_stderr_test"$test_id".test.out \
		> test_diff/diff_stderr_test"$test_id".test.out ;

	if [ -s test_diff/diff_stdout_test"$test_id".test.out ]; then
		return 1;
	fi
	if [ -s test_diff/diff_stderr_test"$test_id".test.out ]; then
		return 1;
	fi
	return 0;
}

function test_ls ()
{
	if run_diff $@; then
		echo -n $'\033[32;1msuccess on:\t\033[0m' test case $1$'\t'; shift; echo with: ls $@
	else
		echo -n $'\033[31;1merror on:\t\033[0m' test case $1$'\t'; shift; echo with: ls $@
	fi
}

test_ls 1
test_ls 2	-r -rrrrr -t
test_ls 3	src
test_ls 4	.
test_ls 5	Makefile src test.sh
test_ls 6	-t
test_ls 7	-tr -r
test_ls 8	Makefile src test.sh -rt
test_ls 9	Makefile src test.sh -tr
test_ls 10	Makefile src test.sh -t
test_ls 11	src -r
test_ls 12	src inc submodules
test_ls 13	-l
test_ls 14	-l /bin
test_ls 15	src inc -l submodules
test_ls 16	src -rR

