CFLAGS = -std=c99 -Wall -Werror -pedantic -c

.PHONY: clean unit

lib.a: libtask.o
	ar rc $@ $^
	ranlib $@
app.exe: main.o
	gcc $^ -L. -ltask -o $@
unit: unit_tests.exe
	./$^
unit_tests.exe: check_main.o
	gcc -o $@ $^ -lcheck

check_main.o: ./unit_tests/check_main.c libtask.h
	gcc $(CFLAGS) $<
main.o: main.c libtask.h
	gcc $(CFLAGS) $<
libtask.o: libtask.c libtask.h
	gcc $(CFLAGS) $<

clean:
	rm -f *.a *.o *.exe