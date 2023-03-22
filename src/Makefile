CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra
TESTFLAGS = -lcheck -coverage -lpthread -pthread

all: clean s21_matrix.a


rebuild: clean all

s21_matrix.a:
	$(CC) $(CFLAGS) -c s21*.c
	ar -rv s21_matrix.a s21*.o s21_matrix.h
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) $(TESTFLAGS) test.c -L. s21_matrix.a -o test
	./test

gcov_report:
	$(CC) $(CFLAGS) $(TESTFLAGS) -c s21_*.c
	ar -rv s21_matrix.a s21*.o s21_matrix.h
	ranlib s21_matrix.a
	$(CC) $(CFLAGS) $(TESTFLAGS) test.c -L. s21_matrix.a -o test
	./test
	gcov s21_*.gcno > report.html && cat report.html
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	make clean


style:
	cppcheck *.h *.c
	clang-format -n -style=Google *.c *.h

clean:
	rm -rf *.o *.gcno *.a *.gcda *.gcov *.info