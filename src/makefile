TARGET = 3d_Viewer
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
FUNCTIONS = $(wildcard functions/*.c)
OBJECTS = $(patsubst %.c, %.o, $(FUNCTIONS))
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
	OPEN_CMD = xdg-open
else
	CHECKFLAGS = -lcheck -lm
	OPEN_CMD = open
endif

all: clean install

uninstall: clean

install: lib
	cd frontend/3d_viewer && qmake && make

main:
	gcc -Wall -Werror -Wextra -c functions/*.c
	gcc -Wall -Werror -Wextra main.c -o main.out *.o

lib:
	gcc -Wall -Werror -Wextra -c  $(FUNCTIONS)
	ar -rcs lib3d_viewer.a *.o

tests: clean
	$(CC) $(CFLAGS) s21_tests.c $(FUNCTIONS) $(CHECKFLAGS) -o s21_tests
	./s21_tests

dvi:
	@$(OPEN_CMD) ../README.html

dist: install
	mkdir -p ../dist
	cp -R frontend/3d_viewer/3d_viewer.app ../dist
	cp ../README_RUS.md ../dist && cp ../README.md ../dist
	cd ../dist && tar cvzf 3d_viewer_v1.0.tgz *
	cd ../dist && rm -rf 3d_viewer.app README.md README_RUS.md

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) s21_tests.c $(FUNCTIONS) $(CHECKFLAGS) -o gcovreport
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o ./report gcovreport.info
	$(OPEN_CMD) ./report/index.html
	rm -rf *.a *.info *.gcda *.gcno gcovreport

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf frontend/build*
	rm -rf frontend/3d_viewer/3d_viewer.pro.user
	rm -rf frontend/3d_viewer/.qmake.stash
	rm -rf frontend/3d_viewer/Makefile
	rm -rf frontend/3d_viewer/3d_viewer.app
	rm -rf frontend/3d_viewer/*.o
	rm -rf frontend/3d_viewer/moc_*
	rm -rf frontend/3d_viewer/ui_*.h
	rm -rf src.pro
	rm -rf s21_tests report
	rm -rf ../dist