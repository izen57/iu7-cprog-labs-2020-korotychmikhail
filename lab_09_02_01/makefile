CFLAGS = -std=c99 -Wall -Werror -pedantic -ggdb -c
I = ./inc/
O = ./out/
S = ./src/
app.exe: $(O)main.o $(O)find.o $(O)inout.o $(O)sort.o
	gcc -o $@ $^
$(O)main.o: $(S)main.c $(I)functions.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
$(O)find.o: $(S)find.c $(I)functions.h
	gcc $(CFLAGS) $< -o $@
$(O)inout.o: $(S)inout.c $(I)functions.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
$(O)sort.o: $(S)sort.c $(I)functions.h
	gcc $(CFLAGS) $< -o $@
clean:
	rm -f $(O)*.o *.exe