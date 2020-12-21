CFLAGS = -std=c99 -Wall -pedantic -ggdb -c
S = ./src/
O = ./out/
I = ./inc/

.PHONY: clean unit

unit: unit_tests.exe
	./$^
unit_tests.exe: $(O)check_main.o $(O)my_snprintf.o
	gcc -o $@ $^ -lcheck
$(O)check_main.o: ./unit_tests/check_main.c $(I)my_snprintf.h
	gcc $(CFLAGS) $< -o $@
$(O)my_snprintf.o: $(S)my_snprintf.c $(I)my_snprintf.h
	gcc $(CFLAGS) $< -o $@

clean:
	rm -f $(O)*.o *.exe