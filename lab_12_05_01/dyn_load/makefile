CFLAGS = -std=c99 -Wall -Werror -pedantic -c
LIBFLAGS = $(CFLAGS) -D ARR_EXPORTS -c

.PHONY: clean unit

app.exe: main.o
	gcc $^ -o $@
lib.dll: lib_task.o
	gcc -shared $^ -Wl,--subsystem,windows -o $@
unit: unit_tests.exe
	./$^
unit_tests.exe: check_main.o
	gcc -o $@ $^ -lcheck

check_main.o: ./unit_tests/check_main.c lib_task.h
	gcc $(CFLAGS) $<
main.o: main.c lib_task.h
	gcc $(CFLAGS) $<
lib_task.o: lib_task.c lib_task.h
	gcc $(LIBFLAGS) $< -o $@

clean:
	rm -f *.o *.exe