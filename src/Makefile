CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
CHECK = -I/opt/homebrew/include -L/opt/homebrew/lib

all: clean s21_matrix.a

test: s21_matrix.a
		$(CC) $(CFLAGS) --coverage tests/*.c *.c -o test -lcheck -lm $(CHECK)
		./test

s21_matrix.a:
		$(CC) $(CFLAGS) *.c -c
		ar rc s21_matrix.a *.o 
		ranlib s21_matrix.a 

gcov_report:
		lcov -t "s21_matrix_test" -o fizzbuzz.info -c -d .
		genhtml -o report fizzbuzz.info 
		open -a "Google Chrome" report/src/index.html

clean: 
		@-rm -rf *.o && rm -rf *.gcno test.dSYM/
		@-rm -rf *.a && rm -rf *.gcda
		@-rm -rf *.info && rm -rf *.gcov
		@-rm -rf ./test && rm -rf ./gcov_report
		@-rm -rf ./report/
		@-rm -rf s21_test main
		@-rm -rf a.out 