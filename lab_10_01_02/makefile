CFLAGS = -std=c99 -Wall -Werror -pedantic -ggdb -c
I = ./inc/
O = ./out/
S = ./src/

.PHONY: clean unit

# unit: unit_tests.exe
# 	./$^
# unit_tests.exe: $(O)check_main.o $(O)inout.o $(O)list.o
# 	gcc -o $@ $^ -lcheck
# $(O)check_main.o: ./unit_tests/check_main.c $(I)structure.h $(I)error_codes.h $(I)list.h $(I)inout.h
# 	gcc $(CFLAGS) $< -o $@
app.exe: $(O)main.o $(O)inout.o $(O)list.o
	gcc -o $@ $^

$(O)main.o: $(S)main.c $(I)inout.h $(I)list.h
	gcc $(CFLAGS) $< -o $@
$(O)inout.o: $(S)inout.c $(I)inout.h $(I)list.h
	gcc $(CFLAGS) $< -o $@
$(O)list.o: $(S)list.c $(I)list.h
	gcc $(CFLAGS) $< -o $@

clean:
	rm -f $(O)*.o *.exe