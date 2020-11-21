CFLAGS = -std=c99 -Wall -Werror -pedantic -ggdb -c
I = ./inc/
O = ./out/
S = ./src/
.PHONY: clean unit
app.exe: $(O)main.o $(O)find.o $(O)inout.o $(O)sort.o
	gcc -o $@ $^
unit: unit_tests.exe
	./$^
unit_tests.exe: $(O)check_main.o $(O)sort.o
	gcc -o $@ $^ -lcheck
$(O)main.o: $(S)main.c $(I)structure.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
$(O)find.o: $(S)find.c $(I)find.h $(I)structure.h
	gcc $(CFLAGS) $< -o $@
$(O)inout.o: $(S)inout.c $(I)inout.h $(I)error_codes.h $(I)structure.h
	gcc $(CFLAGS) $< -o $@
$(O)sort.o: $(S)sort.c $(I)structure.h $(I)sort.h $(I)structure.h
	gcc $(CFLAGS) $< -o $@
$(O)check_main.o: ./unit_tests/check_main.c $(I)structure.h $(S)sort.h
	gcc $(CFLAGS) $< -o $@
clean:
	rm -f $(O)*.o *.exe