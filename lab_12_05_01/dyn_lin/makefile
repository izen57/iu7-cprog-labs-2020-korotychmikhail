CFLAGS = -std=c99 -Wall -Werror -pedantic -c
LIBFLAGS = $(CFLAGS) -D ARR_EXPORTS -c

.PHONY: clean unit

libtask.dll: libtask.o
	gcc -shared $^ -Wl,--subsystem,windows -o $@
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
	gcc $(LIBFLAGS) $< -o $@

clean:
	rm -f *.o *.dll *.exe